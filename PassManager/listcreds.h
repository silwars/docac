#ifndef LISTCREDS_H
#define LISTCREDS_H

#include <QDialog>
#include <QJsonObject>
#include <QString>

#include "crypto.h"
#include <QTableWidget>
namespace Ui {
class listcreds;
}

class listcreds : public QDialog
{
    Q_OBJECT

public:
    explicit listcreds(QString key, QWidget *parent = nullptr);
    ~listcreds();
    QJsonObject Jdoc;
    QString key;
    void load();
signals:
    void firstWindow();

public slots:
private slots:
    void on_pushButton_3_clicked();
    void on_but_clicked();
    void on_pushButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);



    void on_tableWidget_cellClicked(int row, int column);

private:
    QTableWidget *m_tableWidget;
    Ui::listcreds *ui;
};

#endif // LISTCREDS_H
