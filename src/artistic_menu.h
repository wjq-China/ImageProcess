#ifndef ARTISTICMENU_H
#define ARTISTICMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <opencv2/opencv.hpp>
#include "gauss_dialog.h"
class ArtisticMenu : public QMenu
{
    Q_OBJECT
public:
    ArtisticMenu(const QString &title,QWidget *parent = 0);
    QAction *white_balance_ = nullptr;
    QAction *color_offset_ = nullptr;
    QAction *rotate_ = nullptr;
    static cv::Mat image;
    GaussDialog * angle_dialog = nullptr;
    cv::Mat artistic_image_;

public slots:
    void RotationImage();
    void ColorOffset();
    void WhiteBalance();
signals:
    void ChangeRightImage(cv::Mat mat);
};

#endif // ARTISTICMENU_H
