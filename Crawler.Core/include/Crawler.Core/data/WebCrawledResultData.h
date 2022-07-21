#ifndef WEBCRAWLEDDATA_H
#define WEBCRAWLEDDATA_H

#include "WebCrawledRequestData.h"

#include <QMetaType>
#include <QUrl>
#include <vector>
#include <string>

namespace core::data {

enum class WebCrawledResulStatus
{
    Ok, Timeout, Fail
};

class WebCrawledResultData
{
public:
    WebCrawledResultData() = default;
    WebCrawledResultData(const WebCrawledResultData &other) = default;
    ~WebCrawledResultData() = default;

    WebCrawledResultData(WebCrawledResulStatus status,
                         const WebCrawledRequestData& requestData,
                         const std::optional<std::vector<std::string>>& urls,
                         std::optional<size_t> textFoundCnt);

    WebCrawledResulStatus Status() const;
    const WebCrawledRequestData& RequestData() const;
    const std::optional<std::vector<std::string>>& Urls() const;
    std::optional<size_t> TextFoundCnt() const;

private:
    WebCrawledResulStatus m_Status;
    WebCrawledRequestData m_RequestData;

    std::optional<std::vector<std::string>> m_Urls;
    std::optional<size_t> m_TextFoundCnt;
};

};

Q_DECLARE_METATYPE(core::data::WebCrawledResulStatus);
Q_DECLARE_METATYPE(core::data::WebCrawledRequestData);
Q_DECLARE_METATYPE(core::data::WebCrawledResultData);

#endif // WEBCRAWLEDDATA_H
