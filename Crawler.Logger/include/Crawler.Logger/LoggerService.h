#ifndef LOGGERSERVICE_H
#define LOGGERSERVICE_H

#include "LoggerReceiver.h"

#include <vector>
#include <memory>

namespace logger {

class LoggerService
{
public:
    LoggerService();

    void DoLogItem(const LoggerItem& logItem);
    void ClearLog();
    bool AddLoggerReceiver(std::weak_ptr<LoggerReceiver> loggerReceiver);

private:
    std::vector<std::weak_ptr<LoggerReceiver>> m_Receivers;

};

}

#endif // LOGGERSERVICE_H
