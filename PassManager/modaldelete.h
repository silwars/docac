#ifndef MODALDELETE_H
#define MODALDELETE_H

#include <QDialog>

namespace Ui {
class ModalDelete;
}

class ModalDelete : public QDialog
{
    Q_OBJECT

public:
    explicit ModalDelete(QString key, int row, QWidget *parent = nullptr);
    ~ModalDelete();
    int row;
    QString key;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ModalDelete *ui;
};

#endif // MODALDELETE_H
