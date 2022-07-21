#ifndef MAINSCREENCONTROLLER_HPP
#define MAINSCREENCONTROLLER_HPP

#include "model/MainScreenLogger.hpp"
#include "model/WebCrawlerSettings.hpp"

#include <Crawler.Core/DependencyManager.h>
#include <Crawler.Core/WebCrawlerService.h>
#include <Crawler.Logger/LoggerService.h>

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>

#include <queue>

namespace searcher::controller {

class MainScreenController: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString MAIN_SCREEN_NAME READ MainScreenName CONSTANT);
public:
    explicit MainScreenController(const core::DependencyManager& dependencyManager);

signals:
    void progressChanged(double progress);
    void screenStateChanged(bool state);
    void done();

public slots:
    void start(const QString& urlString);
    void pause();
    void resume();
    void stop();

    void clearLog();

    void setUrls(const QString& urls);
    void setThreads(const QString& threads);
    void setText(const QString& text);

private:
    const QString& MainScreenName() const;
    double Progress() const;
    void registerProperties();

    void search();
    std::queue<QUrl> m_QueueUrls;

    bool m_ScreenState;

    bool m_Stopped;
    bool m_Paused;

    double m_Progress;

    size_t m_Urls;
    size_t m_UrlsScanned;
    size_t m_UrlsRequested;

    size_t m_ActiveThreads;
    size_t m_Threads;

    QString m_Text;

private:
    QQmlApplicationEngine m_Engine;

    const core::DependencyManager& m_DependencyManager;

    std::shared_ptr<model::MainScreenLogger> m_MainScreenLogger;
    gui::WebCrawlerSettings m_Settings;

    std::shared_ptr<logger::LoggerService> m_LoggerService;
    std::shared_ptr<core::WebCrawlerService> m_WebCrawlerService;

};

}

#endif // MAINSCREENCONTROLLER_HPP
