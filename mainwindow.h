#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct Task
{
    int beginIndex;
    int endIndex;
    QList<qreal> *data;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_2_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
