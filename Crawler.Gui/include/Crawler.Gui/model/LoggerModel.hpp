#ifndef BLAMODEL_H
#define BLAMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QStringList>

class LoggerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ColorRole = Qt::UserRole + 1,
        TextRole
    };

    LoggerModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void add(const QString& data, const QString& color);
    void clear();

private:
    QStringList m_data;
    QStringList m_color;
};

#endif // BLAMODEL_H
