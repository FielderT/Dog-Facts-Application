#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mNetManager = new QNetworkAccessManager(this);
    connect(mNetManager, &QNetworkAccessManager::finished, this, &MainWindow::handleNetFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUrl(const QString &url)
{
    mNetManager->get(QNetworkRequest(QUrl("https://dog-facts-api.herokuapp.com/api/v1/resources/dogs?number=" + url)));
}

void MainWindow::handleNetFinished(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        ui->label->setText(data);
    }
    else
        qDebug("Network Error");
}


void MainWindow::on_pushButtonGetUrl_clicked()
{
    openUrl(ui->lineEditUrl->text());
}

