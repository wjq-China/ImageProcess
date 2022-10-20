#ifndef HIST_BAR_H
#define HIST_BAR_H

#include <QWidget>

namespace Ui {
class HistBar;
}

class HistBar : public QWidget
{
    Q_OBJECT

public:
    explicit HistBar(QWidget *parent = nullptr);
    ~HistBar();
    QVector<double>hist_;

public slots:
    void PlotBar(QVector<double>);
private:
    Ui::HistBar *ui;
};

#endif // HIST_BAR_H
