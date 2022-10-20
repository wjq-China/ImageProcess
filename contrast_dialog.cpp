#include "contrast_dialog.h"
#include "ui_contrastdialog.h"
#include <QDebug>
ContrastDialog::ContrastDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastDialog)
{
    ui->setupUi(this);
}

ContrastDialog::~ContrastDialog()
{
    delete ui;
}

void ContrastDialog::on_buttonBox_accepted()
{
    contrast_value_.fa = ui->fa_Edit->text().toInt();
    contrast_value_.fb = ui->fb_Edit->text().toInt();
    contrast_value_.ga = ui->ga_Edit->text().toInt();
    contrast_value_.gb = ui->gb_Edit->text().toInt();
    qDebug()<<contrast_value_.fa;
}
