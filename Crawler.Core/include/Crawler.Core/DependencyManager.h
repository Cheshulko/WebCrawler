#ifndef DEPENDENCYMANAGER_H
#define DEPENDENCYMANAGER_H

#include "WebCrawlerService.h"

#include <Crawler.Core/API.h>

#include <memory>

namespace network {

class NetworkService;

}

namespace logger {

class LoggerService;

}

namespace core {

class DependencyManager
{
public:
    explicit CORE_API DependencyManager();

    std::shared_ptr<network::NetworkService> GetNetworkService() const;
    std::shared_ptr<logger::LoggerService> GetLoggerService() const;

    std::shared_ptr<core::WebCrawlerService> GetWebCrawlerService() const;

private:
    std::shared_ptr<network::NetworkService> m_NetworkService;
    std::shared_ptr<logger::LoggerService> m_LoggerService;

    std::shared_ptr<core::WebCrawlerService> m_WebCrawlerService;
};

}

#endif // DEPENDENCYMANAGER_H
