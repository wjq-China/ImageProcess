#ifndef THRESHOLD_DIALOG_H
#define THRESHOLD_DIALOG_H

#include <QDialog>

namespace Ui {
class ThresholdDialog;
}

class ThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdDialog(QWidget *parent = nullptr);
    ~ThresholdDialog();
   // int GetThreshValue();
    int thresh_value_;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ThresholdDialog *ui;
};

#endif // THRESHOLD_DIALOG_H
