#pragma once

#include <QFrame>
#include <QSqlRecord>
#include <QSqlTableModel>

namespace Ui {
class ItemsPanel;
}

class ItemsPanel : public QFrame { // NOLINT(*-special-member-functions)
    Q_OBJECT

    Ui::ItemsPanel* ui;
    QSqlTableModel* m_itemsModel { new QSqlTableModel { this } };
    QSqlRecord m_listRecord;

signals:
    void recordChanged(QSqlRecord);

public:
    explicit ItemsPanel(QWidget* parent = nullptr);
    ~ItemsPanel() override;

public slots: // NOLINT(readability-redundant-access-specifiers)
    void setRecord(const QSqlRecord& record)
    {
        m_listRecord = record;
        emit recordChanged(record);
    }

    void showNewItemDialog();
};
