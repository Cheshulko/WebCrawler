#include "Crawler.Core/WebCrawlerService.h"
#include "Crawler.Core/data/WebCrawledRequestData.h"

#include <Crawler.Utility/RegularExpressionMatcher.h>
#include <Crawler.Network/NetworkService.h>
#include <Crawler.Logger/LoggerService.h>

#include <QDebug>
#include <QString>
#include <QObject>
#include <QUrl>

#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>

#include <QMetaObject>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

#include <memory>
#include <vector>
#include <string>
#include <iterator>

namespace core {

class WebCrawlerTask : public QRunnable
{
public:
    WebCrawlerTask(std::weak_ptr<WebCrawlerResultReceiver> receiver, std::weak_ptr<network::NetworkService> networkService,
                   const data::WebCrawledRequestData& data)
        : m_Receiver(receiver)
        , m_NetworkService(networkService)
        , m_Data(data)
    {
        qDebug() << "[" << m_Data.url << "] Start";
    }
    ~WebCrawlerTask() {
        qDebug() << "[" << m_Data.url << "] Done";
    }

private:
    void run() override
    {
        if (auto networkService = m_NetworkService.lock(); networkService != nullptr) {
            const auto& [status, resultOpt] = networkService->LoadHtmlContent(m_Data.url);

            data::WebCrawledResultData webCrawledData;

            switch (status) {
                case network::ResponseResult::Status::Ok: {
                    assert(resultOpt.has_value());

                    std::vector<std::string> foundUrls;

                    utility::RegularExpressionMatcher::GetInstance().Match(
                        utility::RegularExpressionMatcher::Url,
                        resultOpt.value(),
                        [&foundUrls](const QString& match) {
                            foundUrls.push_back(match.toStdString());
                        }
                    );

                    size_t cnt = m_Data.text.size() == 0 ? 0 :
                            utility::RegularExpressionMatcher::GetInstance().CountMatch(
                        QRegularExpression { m_Data.text },
                        resultOpt.value()
                    );

                    webCrawledData = { data::WebCrawledResulStatus::Ok, m_Data, foundUrls, cnt };
                    break;
                }
                case network::ResponseResult::Status::Fail: {
                    webCrawledData = { data::WebCrawledResulStatus::Fail, m_Data, std::nullopt, std::nullopt, };
                    break;
                }
                case network::ResponseResult::Status::Timeout: {
                    webCrawledData = { data::WebCrawledResulStatus::Timeout, m_Data, std::nullopt, std::nullopt, };
                    break;
                }
            }

            if (auto receiver = m_Receiver.lock(); receiver != nullptr) {
                QMetaObject::invokeMethod(
                    receiver.get(),
                    "onResultReceived",
                    Qt::QueuedConnection,
                    Q_ARG(core::data::WebCrawledResultData, webCrawledData)
                );
            }

        } else {
            // TODO error handling
        }
    }

    std::weak_ptr<WebCrawlerResultReceiver> m_Receiver;
    std::weak_ptr<network::NetworkService> m_NetworkService;

    data::WebCrawledRequestData m_Data;
};

WebCrawlerService::WebCrawlerService(std::weak_ptr<network::NetworkService> networkService)
    : m_NetworkService(networkService)
{
    m_ThreadPool = std::make_unique<QThreadPool>();
    m_ThreadPool->setMaxThreadCount(0);
}

WebCrawlerService::~WebCrawlerService()
{
    stop();
}

void WebCrawlerService::onResultReceived(const core::data::WebCrawledResultData& webCrawledData)
{
    const auto& requestData = webCrawledData.RequestData();

    m_Data[requestData.url.toString()] = webCrawledData;
    m_Callbacks.at(requestData.url.toString())(webCrawledData);
}

void WebCrawlerService::setCrawlingThreadsCnt(size_t cnt)
{
    m_ThreadPool->setMaxThreadCount(cnt);
}

void WebCrawlerService::search(const data::WebCrawledRequestData& data, CrawledCallback&& callback)
{
    const auto& urlString = data.url.toString();
    if (auto it = m_Data.find(urlString); it != m_Data.cend() && it->second.Status() == data::WebCrawledResulStatus::Ok) {
        auto callbackIt = m_Callbacks.find(urlString);

        if (callbackIt != m_Callbacks.cend()) {
            m_Callbacks.at(urlString)({ it->second.Status(), data, it->second.Urls().value(), it->second.TextFoundCnt().value() });
        }
    } else {
        m_Callbacks[urlString] = callback;
        m_ThreadPool->start(new WebCrawlerTask(shared_from_this(), m_NetworkService, data));
    }
}

void WebCrawlerService::pause()
{
    m_ThreadPool->waitForDone();
}

void WebCrawlerService::stop()
{
    m_ThreadPool->clear();
    m_ThreadPool->waitForDone();
}

void WebCrawlerService::clearCache()
{
    m_Data.clear();
    m_Callbacks.clear();
}

}
