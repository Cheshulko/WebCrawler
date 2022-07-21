#ifndef WEBCRAWLERRESULTRECEIVER_H
#define WEBCRAWLERRESULTRECEIVER_H

#include "data/WebCrawledResultData.h"

#include <QObject>
#include <QString>
#include <QVector>

namespace core {

class WebCrawlerResultReceiver: public QObject
{
    Q_OBJECT
public slots:
    virtual void onResultReceived(const core::data::WebCrawledResultData& webCrawledData) = 0;

public:
    virtual ~WebCrawlerResultReceiver() { /* None */ }
};

}

#endif // WEBCRAWLERRESULTRECEIVER_H
