#ifndef CONTRAST_DIALOG_H
#define CONTRAST_DIALOG_H

#include <QDialog>
#include "common_def.h"
namespace Ui {
class ContrastDialog;
}

class ContrastDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastDialog(QWidget *parent = nullptr);
    ~ContrastDialog();
    CONTRASTBALUE_S contrast_value_;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ContrastDialog *ui;
};

#endif // CONTRAST_DIALOG_H
