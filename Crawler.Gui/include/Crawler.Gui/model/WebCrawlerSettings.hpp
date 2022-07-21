#ifndef WEBCRAWLERSETTINGS_HPP
#define WEBCRAWLERSETTINGS_HPP

#include <QObject>
#include <QDebug>

namespace gui {

class WebCrawlerSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString threads READ threads WRITE setThreads NOTIFY threadsChanged)
    Q_PROPERTY(QString urls READ urls WRITE setUrls NOTIFY urlsChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit WebCrawlerSettings(QObject *parent = nullptr)
        : QObject(parent)
        , m_Threads("1")
        , m_Urls("1")
        , m_Text("")
    {
    }

    QString threads() const{
        return m_Threads;
    }

    void setThreads(const QString &threads){
        m_Threads = threads;
        emit threadsChanged(m_Threads);
    }

    QString urls() const{
        return m_Urls;
    }

    void setUrls(const QString &urls)
    {
        m_Urls = urls;
        emit urlsChanged(m_Urls);
    }

    QString text() const{
        return m_Text;
    }

    void setText(const QString &text)
    {
        m_Text = text;
        emit textChanged(m_Text);
    }

signals:
    void threadsChanged(QString threads);
    void urlsChanged(QString urls);
    void textChanged(QString text);

private:
    QString m_Threads;
    QString m_Urls;
    QString m_Text;
};

}

#endif // WEBCRAWLERSETTINGS_HPP
