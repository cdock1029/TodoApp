#include "listspanel.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QPushButton>

constexpr int DIALOG_WIDTH = 300;

ListsPanel::ListsPanel(QWidget* parent)
    : QFrame(parent)
    , ui(new Ui::ListsPanel)
{
    ui->setupUi(this);

    m_listsModel->setTable(u"todo_lists"_s);
    m_listsModel->select();

    ui->listView->setModel(m_listsModel);
    ui->listView->setModelColumn(1);

    connect(ui->newListButton, &QPushButton::clicked, this, &ListsPanel::showNewListDialog);

    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
        [=, this](const QModelIndex& current, const QModelIndex&) {
            qInfo() << "selectionModel currentRowchanged";
            auto record = m_listsModel->record(current.row());
            emit listSelected(record);
        });

    connect(ui->listView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
        [this](const QItemSelection& selected, const QItemSelection& /*deselected*/) {
            if (selected.isEmpty()) {
                qInfo() << "selected is empty";
                emit listSelected(QSqlRecord {});
            }
        });
}

ListsPanel::~ListsPanel()
{
    delete ui;
}

void ListsPanel::showNewListDialog()
{
    auto* dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setMinimumWidth(DIALOG_WIDTH);
    dialog->setWindowTitle(u"Create New List"_s);
    auto* layout = new QVBoxLayout(dialog);
    auto* label = new QLabel(u"New list name:"_s, dialog);
    auto* lineEdit = new QLineEdit(dialog);
    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, dialog);

    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
    connect(dialog, &QDialog::accepted, this, [=, this]() {
        auto name = lineEdit->text();
        auto record = m_listsModel->record();
        record.setValue(u"name"_s, name);
        m_listsModel->insertRecord(-1, record);
        m_listsModel->select();
    });
    dialog->open();
}
