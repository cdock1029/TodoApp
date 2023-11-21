#include "itemspanel.h"
#include "ui_itemspanel.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSqlError>
#include <QSqlField>

constexpr int DIALOG_WIDTH = 300;

using namespace Qt::StringLiterals;

ItemsPanel::ItemsPanel(QWidget* parent)
    : QFrame(parent)
    , ui(new Ui::ItemsPanel)
{
    ui->setupUi(this);
    ui->newItemButton->setHidden(true);
    m_itemsModel->setTable("todo_items");
    m_itemsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    // m_itemsModel->setFilter(u"list_id = -1"_s);
    m_itemsModel->select();

    ui->tableView->setModel(m_itemsModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(m_itemsModel->fieldIndex(u"id"_s));
    ui->tableView->hideColumn(m_itemsModel->fieldIndex(u"list_id"_s));
    ui->tableView->hideColumn(m_itemsModel->fieldIndex(u"completed"_s));

    connect(ui->newItemButton, &QToolButton::clicked, this, &ItemsPanel::showNewItemDialog);

    connect(this, &ItemsPanel::recordChanged, this, [this](const QSqlRecord& record) {
        if (record.isEmpty()) {
            ui->listLabel->setText(u""_s);
            ui->newItemButton->setHidden(true);
            m_itemsModel->setFilter(QString {});
            return;
        }
        auto idField = record.field(u"id"_s);
        auto nameField = record.field(u"name"_s);
        ui->listLabel->setText(nameField.value().toString());
        m_itemsModel->setFilter(u"list_id = %1"_s.arg(idField.value().toInt()));
        if (ui->newItemButton->isHidden()) {
            ui->newItemButton->setHidden(false);
        }
    });
}

ItemsPanel::~ItemsPanel()
{
    delete ui;
}

void ItemsPanel::showNewItemDialog()
{
    auto* dialog = new QDialog { this };
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setMinimumWidth(DIALOG_WIDTH);
    dialog->setWindowTitle(u"New Todo"_s);
    auto* layout = new QVBoxLayout { dialog };
    auto* label = new QLabel { u"Name"_s };
    auto* lineEdit = new QLineEdit { dialog };
    auto* buttonBox = new QDialogButtonBox { QDialogButtonBox::Save | QDialogButtonBox::Cancel, dialog };

    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
    connect(dialog, &QDialog::accepted, this, [=, this]() {
        auto record = m_itemsModel->record();
        record.setValue(u"list_id"_s, m_listRecord.field(u"id"_s).value().toInt());
        record.setValue(u"name"_s, lineEdit->text());
        // 3
        record.remove(m_itemsModel->fieldIndex(u"completed"_s));

        if (!m_itemsModel->insertRecord(-1, record)) {
            qDebug() << "Error inserting item: " << m_itemsModel->lastError();
        }
        m_itemsModel->select();
    });

    dialog->open();
}
