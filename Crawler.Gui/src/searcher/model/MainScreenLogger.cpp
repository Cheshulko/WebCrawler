#include "model/MainScreenLogger.hpp"

#include <QDebug>

namespace searcher::model {

MainScreenLogger::MainScreenLogger()
{}

void MainScreenLogger::onLogItemReceived(const logger::LoggerItem &loggerItem)
{
    QString color;

    switch (loggerItem.getType()) {
        case logger::LoggerItem::Type::Fail: color = "red"; break;
        case logger::LoggerItem::Type::Found: color = "green"; break;
        case logger::LoggerItem::Type::NoOccurrences: color = "black"; break;
    }

    m_Logger.add(loggerItem.toString(), color);
}

void MainScreenLogger::onLogClear()
{
    m_Logger.clear();
}

LoggerModel* MainScreenLogger::GetLoggerModel()
{
    return &m_Logger;
}

}
