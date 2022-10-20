#include "threshold_dialog.h"
#include "ui_thresholddialog.h"

ThresholdDialog::ThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdDialog)
{
    ui->setupUi(this);
}

ThresholdDialog::~ThresholdDialog()
{
    delete ui;
}

//int ThresholdDialog::GetThreshValue()
//{
//    return 0;
//}

void ThresholdDialog::on_buttonBox_accepted()
{
    thresh_value_ = ui->thresh_Edit->text().toInt();
}
