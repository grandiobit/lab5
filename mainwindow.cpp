#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

qreal mapFunction(const Task tsk)
{
    qreal semiResult = 0;
    for (int i = tsk.beginIndex; i <= tsk.endIndex; i++)
    {
        if (tsk.data->at(i)*2 >= 200)
        {
            semiResult += tsk.data->at(i);
        }
    }
    return semiResult;
}

void reduction(qreal & sum, const qreal semiSum)
{
    sum += semiSum;
}



void MainWindow::on_pushButton_clicked()
{
    // создать массив с заданным размером (с проверкой)
    // заполнить его рандомными числами
    // распараллелить программу, выделить каждому потоку собственный кусок массива, начать вычисление
    // сложить полученные с разных отрезков данные

    QString arrayLengthString = ui->lineEdit_2->text();
    QString bValueString = ui->lineEdit->text();
    QString threadsNumberString = ui->lineEdit_3->text();

    int nElem = arrayLengthString.toInt();
    int b = bValueString.toInt();
    int numThread = threadsNumberString.toInt();

    if (nElem > 0 && numThread > 0 && b >= 100 && b <= 100000) // налагаемые ограничения на вводимые данные
    {
        QTime time;
        time.start();

        int elemPerThread = nElem / numThread;

        // srand(time(0));
        QList<qreal> array;
        for (int i = 0; i < nElem - 1; i++)
        {
            // C[i] = rand() % 100000 + 100;
            array.append(qrand());
        }

        // qDebug("%d\n", C[0]); // проверка

        QList<Task> tasks;
        for (int i = 0; i <= numThread - 1; i++)
        {
            Task tsk;
            tsk.beginIndex = i * elemPerThread;
            tsk.endIndex = (i + 1) * elemPerThread - 1;
            tsk.data = &array;
            tasks.append(tsk);
        }

        QFuture<qreal> future = QtConcurrent::mappedReduced(tasks, mapFunction, reduction);
        future.waitForFinished();
        qreal result = future.result();

        ui->label_7->text() = result;
        ui->label_6->text() = time.elapsed();

    }
    else
    {
        QMessageBox box(this);
        box.setText("100 <= b <= 100000, threads > 0, arrayLength > 0");
        box.exec();
    }
}

void MainWindow::on_lineEdit_2_customContextMenuRequested(const QPoint &pos)
{

}
