#ifndef MODALWINDOW_H
#define MODALWINDOW_H

#include <QDialog>
#include <QJsonObject>
#include <QString>

#include "listcreds.h"


namespace Ui {
class ModalWindow;
}

class ModalWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModalWindow(QString key, QWidget *parent = nullptr);
    ~ModalWindow();
    QString key;
private slots:
    void on_buttonBox_accepted();


    void on_buttonBox_rejected();
private:
    Ui::ModalWindow *ui;
};

#endif // MODALWINDOW_H
