#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "JQHttpServer.h"
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void initSqlModel();
    void refreshSqlData();
public:
    //数据库关联表格
    QSqlTableModel mShowDataModel;

public:
    JQHttpServer::TcpServerManage* pserver;
};

#endif // MAINWINDOW_H
