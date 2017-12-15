#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QHostInfo>
#include "DbManager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString localHost = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHost);
    info.addresses();

    QString ipAddr="";

    //如果存在多条ip地址ipv4和ipv6：
   foreach(QHostAddress address,info.addresses())
   {
       if(address.protocol()==QAbstractSocket::IPv4Protocol){//只取ipv4协议的地址
           qDebug()<<address.toString();
           ipAddr += address.toString()+"\n";
       }
   }
   ui->textEdit->setText(ipAddr);
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
            //手机向pc端提交其自己的数据库
            QJsonDocument jsonDocument = QJsonDocument::fromJson(session->requestBody());
            QJsonObject jo = jsonDocument.object();
            QJsonArray array=jo["password"].toArray();
            for(auto i=0;i<array.size();++i){
                QJsonObject obj=array[i].toObject();
                //密码都在这些对象里面了，写入数据库
                QSqlDatabase db = DbManager::getInstance()->getConfigDb(NULL);

                QSqlQuery query(db);

                //先查询有没有重复项，有就不写入了
                QString ssql = QString("select * from password where username='%1' and platform='%2' and password='%3';")
                        .arg(obj["username"].toString())
                        .arg(obj["platform"].toString())
                        .arg(obj["password"].toString());

                qDebug()<<ssql;

                query.exec(ssql);
                if(query.next()){
                    continue;
                }

                ssql = QString("insert into password VALUES('%1','%2','%3');")
                        .arg(obj["username"].toString())
                        .arg(obj["platform"].toString())
                        .arg(obj["password"].toString());
                query.exec(ssql);
            }
            QJsonObject answer;
            answer["message"]="ok";
            answer["method"]="POST";

            session->replyJsonObject(answer);
        } else if (session->requestMethod()=="GET"){
            //读取数据库并发送至客户端
            QSqlDatabase db = DbManager::getInstance()->getConfigDb(NULL);
            QSqlQuery query(db);
            QString ssql = QString("select distinct * from password");
            query.exec(ssql);
            QJsonObject answer;
            QJsonArray array;
            while(query.next()){
                QJsonObject item;
                item["username"] = query.value(0).toString();
                item["platform"] = query.value(1).toString();
                item["password"] = query.value(2).toString();
                array.push_back(item);
            }
            answer["password"]=array;
            answer["message"]="ok";
            answer["method"]="GET";
            session->replyJsonObject(answer);
        }

    } );

    pserver->listen( QHostAddress::Any, 8000 );

    ui->pushButton->setEnabled(false);
}
