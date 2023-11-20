#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QFrame* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_splitter->addWidget(m_ui->listsPanel);
    m_splitter->addWidget(m_ui->itemsPanel);

    auto equalWidth = std::max(m_ui->listsPanel->minimumSizeHint().width(), m_ui->itemsPanel->minimumSizeHint().width());

    m_splitter->setSizes({ GOLDEN_SMALL * equalWidth, GOLDEN_LARGE * equalWidth });

    setCentralWidget(m_splitter);

    connect(m_ui->action_Quit, &QAction::triggered, this, &MainWindow::quit);
    connect(m_ui->listsPanel, &ListsPanel::listSelected, m_ui->itemsPanel, &ItemsPanel::setRecord);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::quit()
{
    close();
}
