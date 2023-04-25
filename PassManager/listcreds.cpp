#include "listcreds.h"
#include "ui_listcreds.h"
#include "modalwindow.h"
#include <QClipboard>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QString>
#include "json.h"
#include "crypto.h"
#include "modaldelete.h"
#include <QMessageBox>>


listcreds::listcreds(QString key, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listcreds)
{

    ui->setupUi(this);
    this->key = key;
    load();

}

listcreds::~listcreds()
{
    delete ui;
}

void listcreds::on_pushButton_3_clicked()
{
    ModalWindow window(this->key);
    window.setModal(true);
    window.exec();
}


void listcreds::load()
{
    json f(this->key);
    ui->tableWidget->setRowCount(0);
    for (int var = 0; var < f.Json.count(); var++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount()-1, new QTableWidgetItem(f.Json[var].toObject().value("site").toString()));

        QTableWidgetItem *login = new QTableWidgetItem;
        login->setData(Qt::UserRole, f.Json[var].toObject().value("login").toString());
        login->setText("*****");
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, login);

        QTableWidgetItem *pass = new QTableWidgetItem;
        pass->setText("********");
        pass->setData(Qt::UserRole, f.Json[var].toObject().value("pass").toString());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, pass);
    }
}



void listcreds::on_but_clicked()
{
    load();
}

void listcreds::on_tableWidget_cellDoubleClicked(int row, int column)
{
    // Получаем выбранную строку таблицы
    QTableWidgetItem *item = ui->tableWidget->verticalHeaderItem(row);

    // Показываем всплывающее окно для подтверждения удаления
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удалить строку", "Вы уверены, что хотите удалить строку \"" + item->text() + "\"?", QMessageBox::Yes|QMessageBox::No);

    // Если пользователь подтверждает удаление, то удаляем строку из таблицы и из файла
    if (reply == QMessageBox::Yes) {
        // Удаляем выбранную строку из таблицы
        ui->tableWidget->removeRow(row);
        // Удаляем строку из файла
        json f(this->key);
        f.deletefromjson(row);
    }
}


void listcreds::on_pushButton_clicked()
{
    for (int var = 0; var < ui->tableWidget->rowCount(); ++var) {
        ui->tableWidget->setRowHidden(var,false);
        if(ui->tableWidget->verticalHeaderItem(var)->text().contains(ui->lineEdit->text(), Qt::CaseInsensitive)==0)
        {
            ui->tableWidget->setRowHidden(var,true);
        }

    }
}


void listcreds::on_tableWidget_cellClicked(int row, int column)
{
    QByteArray etext = ui->tableWidget->item(row,column)->data(Qt::UserRole).toByteArray();
    QString text = crypto::decrypt(etext, this->key,this->key);
    QApplication::clipboard()->setText(text);
}

