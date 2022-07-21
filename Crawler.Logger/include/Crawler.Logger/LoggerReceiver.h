#ifndef LOGGERRECEIVER_H
#define LOGGERRECEIVER_H

#include "LoggerItem.h"

namespace logger {

class LOGGER_API LoggerReceiver
{
public:
    virtual void onLogItemReceived(const LoggerItem& loggerItem) = 0;
    virtual void onLogClear() = 0;
    virtual ~LoggerReceiver() { /* None */ }
};

}
#endif // LOGGERRECEIVER_H
