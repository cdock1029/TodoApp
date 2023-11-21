#pragma once

#include <QStyledItemDelegate>

class CheckBoxDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit CheckBoxDelegate(QObject* parent = nullptr)
        : QStyledItemDelegate(parent)
    {
    }

    // QAbstractItemDelegate interface
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
