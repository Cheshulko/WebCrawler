#ifndef WEBCRAWLERSERVICE_H
#define WEBCRAWLERSERVICE_H

#include "WebCrawlerResultReceiver.h"

#include <QObject>
#include <QUrl>
#include <QThreadPool>

#include <memory>
#include <unordered_map>
#include <functional>

namespace network {

class NetworkService;

}

namespace logger {

class LoggerService;

}

namespace core {

class WebCrawlerService: public core::WebCrawlerResultReceiver, public std::enable_shared_from_this<WebCrawlerService>
{
public:
    using CrawledCallback = std::function<void(const data::WebCrawledResultData&)>;

public:
    explicit WebCrawlerService(std::weak_ptr<network::NetworkService> networkService);
    virtual ~WebCrawlerService();

    virtual void onResultReceived(const core::data::WebCrawledResultData& webCrawledData) override;

    void setCrawlingThreadsCnt(size_t cnt);
    void search(const data::WebCrawledRequestData& data, CrawledCallback&& callback);
    void pause();
    void stop();

    void clearCache();

private:
    std::unordered_map<QString, CrawledCallback> m_Callbacks;
    std::unordered_map<QString, data::WebCrawledResultData> m_Data;

    std::unique_ptr<QThreadPool> m_ThreadPool;

    std::weak_ptr<network::NetworkService> m_NetworkService;
    std::weak_ptr<logger::LoggerService> m_LoggerService;
};

}

#endif // WEBCRAWLERSERVICE_H
