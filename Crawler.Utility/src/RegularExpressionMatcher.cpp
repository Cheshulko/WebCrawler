#include "Crawler.Utility/RegularExpressionMatcher.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

namespace utility {

const QRegularExpression RegularExpressionMatcher::Url = QRegularExpression{ "(http|ftp|https)://([\\w_-]+(?:(?:\\.[\\w_-]+)+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?" };

RegularExpressionMatcher& RegularExpressionMatcher::GetInstance()
{
    static RegularExpressionMatcher instance;
    return instance;
}

void RegularExpressionMatcher::Match(QRegularExpression re, const QString& text, std::function<void (const QString &)> outputFunc)
{
    QRegularExpressionMatchIterator i = re.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        outputFunc(match.captured(0));
    }
}

size_t RegularExpressionMatcher::CountMatch(QRegularExpression re, const QString& text)
{
    return text.count(re);
}

}


