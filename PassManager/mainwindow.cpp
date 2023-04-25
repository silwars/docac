#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listcreds.h"
#include "json.h"
#include "crypto.h"
#include "qaesencryption.h"
#include <QMessageBox>
#include "QCryptographicHash"
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(sWindow, &listcreds::firstWindow, this, &MainWindow::show);
}


MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::check_pin(QString pinCode)
{
    QFile file(json::kFileName);
    if (!file.exists()) {
        auto encodedPin = crypto::encrypt((pinCode + "\n").toUtf8(), pinCode, pinCode);

        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(encodedPin);
        file.close();

        QMessageBox::warning(this, "Pin", "A new PIN code has been created");
        qDebug()<< "encodedPin" << encodedPin;
    }
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QByteArray readedText = file.readAll();
    file.close();

    QString decodedText = crypto::decrypt(readedText, pinCode, pinCode);
    QString decodedKey = decodedText.split("\n")[0];
    return pinCode == decodedKey;
}

void MainWindow::on_pushButton_clicked()
{
    QString pinCode = ui->pincode->text();


    if(check_pin(pinCode))
    {
        sWindow = new listcreds(pinCode);
        sWindow->show();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"Авторизация","Неправильный пин-код");
    }
}
