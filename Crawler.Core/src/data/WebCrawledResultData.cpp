#include "Crawler.Core/data/WebCrawledResultData.h"

namespace core::data {

WebCrawledResultData::WebCrawledResultData(
        WebCrawledResulStatus status,
        const WebCrawledRequestData& requestData,
        const std::optional<std::vector<std::string>>& urls,
        std::optional<size_t> textFoundCnt)

    : m_Status(status)
    , m_RequestData(requestData)
    , m_Urls(urls)
    , m_TextFoundCnt(textFoundCnt)
{}

WebCrawledResulStatus WebCrawledResultData::Status() const
{
    return m_Status;
}

const WebCrawledRequestData& WebCrawledResultData::RequestData() const
{
    return m_RequestData;
}

const std::optional<std::vector<std::string>>& WebCrawledResultData::Urls() const
{
    return m_Urls;
}

std::optional<size_t> WebCrawledResultData::TextFoundCnt() const
{
    return m_TextFoundCnt;
}

}
