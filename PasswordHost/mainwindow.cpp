#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    pserver->setHttpAcceptedCallback( []( const QPointer< JQHttpServer::Session > &session )
    {
        // 回调发生在新的线程内，不是主线程，请注意线程安全
        // 若阻塞了此回调，那么新的连接将不会得到处理（默认情况下有2个线程可以阻塞2次，第3个连接将不会被处理）

        if(session->requestMethod()=="POST"){
            QJsonDocument jsonDocument = QJsonDocument::fromJson(session->requestBody());
            QJsonObject jo = jsonDocument.object();
            QJsonArray array=jo["password"].toArray();
            for(auto i=0;i<array.size();++i){
                QJsonObject obj=array[i].toObject();
                //密码都在这些对象里面了，写入数据库
            }

            session->replyJsonObject( { { { "message", "ok" } } } );
        } else if (session->requestMethod()=="GET"){
            //读取数据库并发送至客户端
        }

    } );

    pserver->listen( QHostAddress::Any, 8000 );
}
