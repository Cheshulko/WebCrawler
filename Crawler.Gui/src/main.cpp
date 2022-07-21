#include <QGuiApplication>
#include <QMetaType>

#include "model/WebCrawlerSettings.hpp"

#include "controller/MainScreenController.hpp"

#include <Crawler.Core/DependencyManager.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    const core::DependencyManager dependencyManager;

    qmlRegisterType<gui::WebCrawlerSettings>("WebCrawlerSettings", 1, 0, "Settings");
    qRegisterMetaType<core::data::WebCrawledResultData>("searcher::service::crawler::data::WebCrawledData");

    const searcher::controller::MainScreenController mainScreenController(dependencyManager);

    return app.exec();
}
