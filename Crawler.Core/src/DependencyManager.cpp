#include "Crawler.Core/DependencyManager.h"

#include <Crawler.Network/NetworkService.h>
#include <Crawler.Logger/LoggerService.h>

namespace core {

DependencyManager::DependencyManager()
{
    m_NetworkService = std::make_shared<network::NetworkService>();
    m_LoggerService = std::make_shared<logger::LoggerService>();
    m_WebCrawlerService = std::make_shared<core::WebCrawlerService>(m_NetworkService);
}

std::shared_ptr<core::WebCrawlerService> DependencyManager::GetWebCrawlerService() const
{
    return m_WebCrawlerService;
}

std::shared_ptr<logger::LoggerService> DependencyManager::GetLoggerService() const
{
    return m_LoggerService;
}

std::shared_ptr<network::NetworkService> DependencyManager::GetNetworkService() const
{
    return m_NetworkService;
}

}
