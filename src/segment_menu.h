#ifndef SEGMENTMENU_H
#define SEGMENTMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <opencv2/core/mat.hpp>
#include "threshold_dialog.h"
class SegmentMenu : public QMenu
{
    Q_OBJECT
public:
    QAction *binary_ = nullptr;
    QAction *ostu_ = nullptr;
    ThresholdDialog *threshold_dialog_ = nullptr;
public:
    SegmentMenu(const QString &title,QWidget *parent = 0);
    static cv::Mat image;
    cv::Mat segment_image_;

    //cv::Mat  Rgb2Gray(cv::Mat image);

public slots:
    void InputBinarisation();
    cv::Mat Binarisation(int);
    void OstuBinarization();
signals:
    void ChangeRightImage(cv::Mat mat);
};

#endif // SEGMENTMENU_H
