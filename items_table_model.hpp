#pragma once

#include <QSqlTableModel>

class ItemsTableModel : public QSqlTableModel {
    Q_OBJECT

public:
    explicit ItemsTableModel(QObject* parent = nullptr)
        : QSqlTableModel(parent)
    {
    }

    // QAbstractItemModel interface
    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid()) {
            return QVariant {};
        }

        if (role == Qt::CheckStateRole) {
            auto value = index.sibling(index.row(), 3).data().toBool();
            return value ? Qt::Checked : Qt::Unchecked;
        }

        return QSqlTableModel::data(index, role);
    }

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        return QSqlTableModel::flags(index) | Qt::ItemIsUserCheckable;
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role) override
    {
        if (role == Qt::CheckStateRole) {
            return QSqlTableModel::setData(index.sibling(index.row(), 3), value == Qt::Checked, Qt::EditRole);
        }
        return QSqlTableModel::setData(index, value, role);
    }
};
