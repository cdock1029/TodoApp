#pragma once

#include "ui_listspanel.h"
#include <QFrame>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlTableModel>

using namespace Qt::StringLiterals;

namespace Ui {
class ListsPanel;
}

class ListsPanel : public QFrame // NOLINT(*-special-member-functions)
{
    Q_OBJECT

    Ui::ListsPanel* ui;
    QSqlTableModel* m_listsModel { new QSqlTableModel { this } };

public:
    explicit ListsPanel(QWidget* parent = nullptr);
    ~ListsPanel() override;

    [[nodiscard]] int currentListId() const
    {
        auto current = ui->listView->currentIndex();
        auto record = m_listsModel->record(current.row());
        auto field = record.field(u"id"_s);
        return field.value().toInt();
    }

signals:
    void listSelected(const QSqlRecord&);

public slots: // NOLINT(readability-redundant-access-specifiers)
    void showNewListDialog();
};
