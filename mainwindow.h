#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void iniciar();
    void compute();
    void valuar();
private:
    Ui::MainWindow *ui;
    QVector<double> varx;
    QVector<double> vary;
    QVector<double> time;
    QVector<double> bateria;
};
#endif // MAINWINDOW_H
