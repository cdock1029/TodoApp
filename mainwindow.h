#include <QMainWindow>
#include <QSplitter>

#pragma once

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

inline constexpr int GOLDEN_SMALL = static_cast<int>(10000 - 10000 / 1.618);
inline constexpr int GOLDEN_LARGE = static_cast<int>(10000 / 1.618);

class MainWindow : public QMainWindow { // NOLINT(*-special-member-functions)
    Q_OBJECT

    Ui::MainWindow* m_ui;
    QSplitter* m_splitter = new QSplitter { Qt::Horizontal, this };

public:
    explicit MainWindow(QFrame* parent = nullptr);
    ~MainWindow() override;

private:
    void quit();
};
