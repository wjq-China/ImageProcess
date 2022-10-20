#ifndef FILTERMENU_H
#define FILTERMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <opencv2/core/mat.hpp>
#include "gauss_dialog.h"
class FilterMenu : public QMenu
{
    Q_OBJECT
public:
    QAction *knn_filter_=nullptr;
    QAction *mean_filter_ = nullptr;
    QAction *median_filter_ = nullptr;
    QAction *gauss_filter_ = nullptr;
    GaussDialog *gauss_dialog_ = nullptr;

public:
    FilterMenu(const QString &title,QWidget *parent = 0);
    cv::Mat filter_mat_;
    static cv::Mat image;

public slots:
    void MeanFilter();
    void MedianFilter();
    void KnnFilter();
    void GaussFilter();
signals:
    void ChangeRightImage(cv::Mat);
};

#endif // FILTERMENU_H
