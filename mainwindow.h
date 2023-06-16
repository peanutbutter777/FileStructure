#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_sbi_btn_clicked();

    void on_sbn_btn_clicked();


    void on_rbn_btn_clicked();

    void on_g_btn_clicked();

    void on_r_btn_clicked();

    void on_rbi_btn_clicked();

    void on_mbn_btn_clicked();

    void on_g_btn_2_clicked();

    void on_r_btn_2_clicked();

    void on_mid_btn_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
