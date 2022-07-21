#ifndef LOGGERITEM_H
#define LOGGERITEM_H

#include <Crawler.Logger/API.h>

#include <QString>

#include <sstream>
#include <string>

namespace logger {

class LOGGER_API LoggerItem
{
public:
    enum class Type
    {
        Fail, Found, NoOccurrences
    };
public:
    LoggerItem(Type type): m_Type(type) {}
    virtual QString toString() const = 0;
    virtual Type getType() const { return m_Type; };
    virtual ~LoggerItem() { /* None */ }

private:
    Type m_Type;
};

class FailLoggerItem: public LoggerItem
{
public:
    FailLoggerItem(size_t id, const std::string& url, const std::string& errorMsg)
        : LoggerItem(LoggerItem::Type::Fail)
        , m_Id(id)
        , m_Url(url)
        , m_ErrorMsg(errorMsg)
    {}

    QString toString() const override {
        std::stringstream ss;
        ss << "Url # " << m_Id << " ";
        ss << "[" << m_Url << "] ";
        ss << "\n\tError: " << m_ErrorMsg;

        return QString::fromStdString(ss.str());
    }
     ~FailLoggerItem() = default;

private:
    size_t m_Id;
    std::string m_Url;
    std::string m_ErrorMsg;
};

class ResultLoggerItem: public LoggerItem
{
public:
    ResultLoggerItem(LoggerItem::Type type, size_t id, const std::string& url, size_t urls, size_t occurrences)
        : LoggerItem(type)
        , m_Id(id)
        , m_Url(url)
        , m_Urls(urls)
        , m_Occurrences(occurrences)
    {}

    QString toString() const override {
        std::stringstream ss;
        ss << "Url # " << m_Id << " ";
        ss << "[" << m_Url << "] ";
        ss << "\n\tFound urls: " << m_Urls;
        ss << "\n\tFound text occurrences: " << m_Occurrences;

        return QString::fromStdString(ss.str());
    }
     ~ResultLoggerItem() = default;

private:
    size_t m_Id;
    std::string m_Url;
    size_t m_Urls;
    size_t m_Occurrences;
};

}

#endif // LOGGERITEM_H
