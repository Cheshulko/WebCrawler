#include "Crawler.Network/NetworkService.h"

#include <QTimer>
#include <QDebug>

namespace network {

NetworkService::NetworkService()
{
}

ResponseResult NetworkService::LoadHtmlContent(const QUrl& url) const
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(url));

    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;
    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    QObject::connect(response, SIGNAL(finished()), &loop, SLOT(quit()));
    timer.start(3000);   // 3 secs. timeout
    loop.exec();

    ResponseResult result;

    if(timer.isActive()) {
        timer.stop();
        if(response->error() > 0) {
            result = { ResponseResult::Status::Fail, std::nullopt };
        }
        else {
          int v = response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

          if (v >= 200 && v < 300) {  // Success
              result = { ResponseResult::Status::Ok, response->readAll() };
          } else {
              qDebug() << 'g' << v;
              result = { ResponseResult::Status::Fail, std::nullopt };
          }
        }
    } else {
       // timeout
       QObject::disconnect(response, SIGNAL(finished()), &loop, SLOT(quit()));

       response->abort();
       result = { ResponseResult::Status::Timeout, std::nullopt };
    }

    return result;
}

}
