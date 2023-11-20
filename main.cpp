#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using namespace Qt::StringLiterals;

int main(int argc, char* argv[])
{
    const QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("todo_app.db");
    db.open();

    MainWindow w;
    w.show();
    return a.exec();
}
