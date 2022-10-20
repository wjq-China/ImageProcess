#ifndef ENHANCEMENU_H
#define ENHANCEMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <opencv2/core/mat.hpp>
#include "contrast_dialog.h"
#include "common_def.h"
#include "hist_bar.h"
class EnhanceMenu : public QMenu
{
    Q_OBJECT
public:
    QAction *rgb2Gray_=nullptr;
    QAction *contrast_spread_ = nullptr;
    QAction *histogram_ = nullptr;
    QAction *histogram_equalisation_ = nullptr;
    ContrastDialog *contrast_dialog_ = nullptr;
    HistBar * hist_bar_ = nullptr;

public:
    EnhanceMenu(const QString &title,QWidget *parent = 0);
    static cv::Mat image;
    cv::Mat enhance_image_;
    int flag=1;

signals:
    void ChangeRightImage(cv::Mat mat);
    void HistStatistics(QVector<double>);

public slots:
    void Rgb2Gray();
    void ContrastSpread();
    void HistBarStastics();
    void HistogramEqualisation();

};

#endif // ENHANCEMENU_H
