#include "gauss_dialog.h"
#include "ui_gaussdialog.h"

GaussDialog::GaussDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussDialog)
{
    ui->setupUi(this);
}

GaussDialog::~GaussDialog()
{
    delete ui;
}

void GaussDialog::GetGaussValue()
{

}

void GaussDialog::HideGaussLabel()
{
    ui->gauss_label->setVisible(false);
}

void GaussDialog::HideRotationLabel()
{
    ui->rotation_label->setVisible(false);
}

void GaussDialog::on_buttonBox_accepted()
{
    k = ui->gauss_Edit->text().toInt();
}
