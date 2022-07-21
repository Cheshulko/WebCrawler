#include "Crawler.Logger/LoggerService.h"

namespace logger {

LoggerService::LoggerService()
{}

void LoggerService::DoLogItem(const LoggerItem& logItem)
{
    std::for_each(m_Receivers.begin(), m_Receivers.end(), [&logItem](std::weak_ptr<LoggerReceiver> receiverWeak) {
        if (auto receiver = receiverWeak.lock(); receiver != nullptr) {
            receiver->onLogItemReceived(logItem);
        }
    });
}

void LoggerService::ClearLog()
{
    std::for_each(m_Receivers.begin(), m_Receivers.end(), [](std::weak_ptr<LoggerReceiver> receiverWeak) {
        if (auto receiver = receiverWeak.lock(); receiver != nullptr) {
            receiver->onLogClear();
        }
    });
}

bool LoggerService::AddLoggerReceiver(std::weak_ptr<LoggerReceiver> loggerReceiver)
{
    m_Receivers.push_back(loggerReceiver);

    // TODO: Should check if already have such reciever and so on.
    return true;
}

}
