#include "model/LoggerModel.hpp"

#include <QObject>

LoggerModel::LoggerModel(QObject *parent):
    QAbstractListModel(parent)
{}

int LoggerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_data.size();
}

QVariant LoggerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case ColorRole:
        return m_color.at(index.row());
    case TextRole:
        return m_data.at(index.row());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LoggerModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[ColorRole] = "color";
    roles[TextRole] = "text";

    return roles;
}

void LoggerModel::add(const QString& data, const QString& color)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(data);
    m_color.append(color);
    endInsertRows();

    QModelIndex i = index(0);
    emit dataChanged(i, i);
}

void LoggerModel::clear()
{
    const auto size = m_data.size();
    beginResetModel();
    removeRows(0, size);
    m_data.clear();
    m_color.clear();
    endResetModel();
}
