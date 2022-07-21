#ifndef REGULAREXPRESSIONMATCHER_H
#define REGULAREXPRESSIONMATCHER_H

#include <Crawler.Utility/API.h>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

#include <functional>

namespace utility {

class RegularExpressionMatcher
{
public:
    static RegularExpressionMatcher& GetInstance();

    void UTILITY_API Match(QRegularExpression re, const QString& text, std::function<void(const QString&)> outputFunc);
    size_t CountMatch(QRegularExpression re, const QString& text);

    static const QRegularExpression Url;

public:
    RegularExpressionMatcher(RegularExpressionMatcher const&) = delete;
    void operator=(RegularExpressionMatcher const&) = delete;

private:
    RegularExpressionMatcher() = default;

};

}

#endif // REGULAREXPRESSIONMATCHER_H
