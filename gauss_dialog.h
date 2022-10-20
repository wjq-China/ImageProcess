#ifndef GAUSS_DIALOG_H
#define GAUSS_DIALOG_H

#include <QDialog>

namespace Ui {
class GaussDialog;
}

class GaussDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GaussDialog(QWidget *parent = nullptr);
    ~GaussDialog();
    void GetGaussValue();
    int k;
    void HideGaussLabel();
    void HideRotationLabel();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::GaussDialog *ui;
};

#endif // GAUSS_DIALOG_H
