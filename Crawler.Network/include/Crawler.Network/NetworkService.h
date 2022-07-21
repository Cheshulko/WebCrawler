#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <Crawler.Network/API.h>

#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QString>
#include <QUrl>

#include <optional>

namespace network {

struct ResponseResult
{
    enum class Status
    {
        Ok, Timeout, Fail
    };

    Status status;
    std::optional<QString> content;
};

class NETWORK_API NetworkService
{
public:
    NetworkService();

    ResponseResult LoadHtmlContent(const QUrl& url) const;
};

}

#endif // NETWORKSERVICE_H
