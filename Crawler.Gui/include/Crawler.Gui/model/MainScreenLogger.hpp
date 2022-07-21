#ifndef MAINSCREENLOGGER_HPP
#define MAINSCREENLOGGER_HPP

#include <Crawler.Logger/LoggerReceiver.h>
#include "LoggerModel.hpp"

namespace searcher::model {

class MainScreenLogger: public logger::LoggerReceiver
{
public:
    MainScreenLogger();

    void onLogItemReceived(const logger::LoggerItem& loggerItem) override;
    void onLogClear() override;
    ~MainScreenLogger() = default;

    LoggerModel* GetLoggerModel();

private:
    LoggerModel m_Logger;
};

}

#endif // MAINSCREENLOGGER_HPP
