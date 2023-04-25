#include "modaldelete.h"
#include "ui_modaldelete.h"
#include "json.h"
#include "listcreds.h"

ModalDelete::ModalDelete(QString key,int row,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModalDelete)
{
    ui->setupUi(this);
    this->row = row;
    this->key = key;
}

ModalDelete::~ModalDelete()
{
    delete ui;
}

void ModalDelete::on_buttonBox_accepted()
{
    json f(this->key);
    f.deletefromjson(this->row);
}

