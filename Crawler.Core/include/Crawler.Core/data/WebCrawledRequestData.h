#ifndef WEBCRAWLEDREQUESTDATA_H
#define WEBCRAWLEDREQUESTDATA_H

#include <QUrl>
#include <QString>

namespace core::data {

struct WebCrawledRequestData
{
    size_t id;
    QUrl url;
    QString text;
};

}

#endif // WEBCRAWLEDREQUESTDATA_H
