#include "modalwindow.h"
#include "ui_modalwindow.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include "json.h"
#include "crypto.h"


ModalWindow::ModalWindow(QString key, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModalWindow)
{
    ui->setupUi(this);
    this->key = key;
}
ModalWindow::~ModalWindow()
{

    delete ui;
}



void ModalWindow::on_buttonBox_accepted()
{
    QJsonObject textObject; // Создаю объект текста
    textObject["site"] = ui->site->text();
    textObject["login"] = ui->login->text();
    textObject["pass"] = ui->pass->text();
    json f(this->key);
    f.writetojson(f.encodeobj(textObject));
    listcreds *lc = new listcreds(this->key);
    lc->load();
    this->close();


}


void ModalWindow::on_buttonBox_rejected()
{
    this->close();

}


