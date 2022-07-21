#include "controller/MainScreenController.hpp"

#include <Crawler.Core/data/WebCrawledResultData.h>

#include <QQmlContext>
#include <QDebug>
#include <QUrl>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include <sstream>

namespace searcher::controller {

MainScreenController::MainScreenController(const core::DependencyManager &dependencyManager)
    : m_Stopped(false)
    , m_Paused(false)
    , m_Urls(0)
    , m_UrlsScanned(0)
    , m_UrlsRequested(0)
    , m_ActiveThreads(0)
    , m_DependencyManager(dependencyManager)
{
    m_MainScreenLogger = std::make_shared<model::MainScreenLogger>();

    registerProperties();

    m_LoggerService = dependencyManager.GetLoggerService();
    m_LoggerService->AddLoggerReceiver(m_MainScreenLogger);

    m_WebCrawlerService = dependencyManager.GetWebCrawlerService();

    QObject::connect(&m_Settings, SIGNAL(threadsChanged(QString)), this, SLOT(setThreads(QString)));
    QObject::connect(&m_Settings, SIGNAL(urlsChanged(QString)), this, SLOT(setUrls(QString)));
    QObject::connect(&m_Settings, SIGNAL(textChanged(QString)), this, SLOT(setText(QString)));

    m_Engine.load(QStringLiteral("qrc:/main.qml"));
}

const QString& MainScreenController::MainScreenName() const
{
    static const QString mainScreenName = "MainScreen";
    return mainScreenName;
}

double MainScreenController::Progress() const
{
    return m_Progress;
}

void MainScreenController::registerProperties()
{
    m_Engine.rootContext()->setContextProperty("MainScreen_controller", this);
    m_Engine.rootContext()->setContextProperty("myModel", m_MainScreenLogger->GetLoggerModel());
    m_Engine.rootContext()->setContextProperty("mySettings", &m_Settings);
}

void MainScreenController::start(const QString &urlString)
{
    while(!m_QueueUrls.empty()) m_QueueUrls.pop();

    qDebug() << "Start " << m_Threads << " - " << m_Urls << QThread::currentThread();
    m_QueueUrls.push(QUrl(urlString));
    m_Stopped = false;

    m_Urls = m_Settings.urls().toInt();
    m_UrlsScanned = 0;
    m_UrlsRequested = 0;

    m_Progress = 0.0;
    emit progressChanged(Progress());

    m_WebCrawlerService->setCrawlingThreadsCnt(m_Threads);

    search();
}

void MainScreenController::pause()
{
    qDebug() << "Pause " << QThread::currentThread();
    m_Paused = true;
    emit screenStateChanged(false);
    QFuture<void> future = QtConcurrent::run([this](){
        m_WebCrawlerService->pause();
        emit screenStateChanged(true);
    });
}

void MainScreenController::resume()
{
    qDebug() << "Resume " << QThread::currentThread();
    m_Paused = false;
    search();
}

void MainScreenController::stop()
{
    qDebug() << "Stop " << QThread::currentThread();
    m_Paused = false;
    m_Stopped = true;
    emit screenStateChanged(false);
    QFuture<void> future = QtConcurrent::run([this](){
        m_WebCrawlerService->stop();
        m_WebCrawlerService->clearCache();
        emit screenStateChanged(true);
    });
}

void MainScreenController::clearLog()
{
    m_LoggerService->ClearLog();
}

void MainScreenController::setUrls(const QString& urls)
{
    m_Urls = urls.toUInt();
}

void MainScreenController::setThreads(const QString& threads)
{
    m_Threads = threads.toUInt();
}

void MainScreenController::setText(const QString& text)
{
    m_Text = text;
}

void MainScreenController::search()
{
    using WebCrawledResultData = core::data::WebCrawledResultData;
    using WebCrawledResulStatus = core::data::WebCrawledResulStatus;

    if (m_UrlsScanned == m_Urls ||
            (m_QueueUrls.empty() && m_ActiveThreads == 0)) {

        m_WebCrawlerService->clearCache();
        emit done();
        return;
    }

    while (m_ActiveThreads < m_Threads && !m_QueueUrls.empty() && m_UrlsRequested < m_Urls
           && !m_Stopped && !m_Paused) {
        auto top = m_QueueUrls.front();
        m_QueueUrls.pop();

        ++m_UrlsRequested;
        ++m_ActiveThreads;

        m_WebCrawlerService->search({ m_UrlsRequested, QUrl(top), m_Text }, [this](const WebCrawledResultData& webCrawledData){

            switch (webCrawledData.Status()) {
                case WebCrawledResulStatus::Fail: {

                    m_LoggerService->DoLogItem(logger::FailLoggerItem {
                        webCrawledData.RequestData().id,
                        webCrawledData.RequestData().url.toString().toStdString(),
                        "Request FAILED "
                    });

                    break;
                }
                case WebCrawledResulStatus::Timeout: {

                    m_LoggerService->DoLogItem(logger::FailLoggerItem {
                        webCrawledData.RequestData().id,
                        webCrawledData.RequestData().url.toString().toStdString(),
                        "Request TIMEOUT "
                    });

                    break;
                }
                case WebCrawledResulStatus::Ok: {

                    const auto occurances = webCrawledData.TextFoundCnt().value();

                    m_LoggerService->DoLogItem(logger::ResultLoggerItem {
                        occurances > 0 ? logger::LoggerItem::Type::Found : logger::LoggerItem::Type::NoOccurrences,
                        webCrawledData.RequestData().id,
                        webCrawledData.RequestData().url.toString().toStdString(),
                        webCrawledData.Urls().value().size(),
                        occurances
                    });

                    for (const std::string& url: webCrawledData.Urls().value()) {
                        m_QueueUrls.push(QUrl(QString::fromStdString(url)));
                    }

                    break;
                }
            }

            ++m_UrlsScanned;
            --m_ActiveThreads;

            m_Progress = static_cast<double>((0. + m_UrlsScanned) / m_Urls);
            qDebug() << m_Progress;
            emit progressChanged(Progress());

            search();
        });
    }
}

}
