#include "checkboxdelegate.h"

#include <QCheckBox>

QWidget* CheckBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{

    auto* editor = new QCheckBox(parent);
    // editor->setChecked(index.data().toBool());
    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    auto* cb = dynamic_cast<QCheckBox*>(editor);
    auto val = index.model()->data(index, Qt::EditRole).toBool();
    cb->setChecked(val);
}

void CheckBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    auto* cb = dynamic_cast<QCheckBox*>(editor);
    auto value = cb->isChecked();

    model->setData(index, value, Qt::EditRole);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
    editor->setGeometry(option.rect);
}
