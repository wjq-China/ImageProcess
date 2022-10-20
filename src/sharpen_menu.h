#ifndef SHARPENMENU_H
#define SHARPENMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include<opencv2/opencv.hpp>
class SharpenMenu : public QMenu
{
    Q_OBJECT
public:
    QAction *sobel_ = nullptr;
    QAction *laplacian_ = nullptr;
    QAction *wallis_ = nullptr;
public:
    SharpenMenu(const QString &title,QWidget *parent = 0);
    cv::Mat sharpen_mat_;
    static cv::Mat image;

public slots:
    void SobelSharpen();
    void LaplacianSharpen();
    void WallisSharpen();

signals:
    void ChangeRightImage(cv::Mat mat);
};

#endif // SHARPENMENU_H
