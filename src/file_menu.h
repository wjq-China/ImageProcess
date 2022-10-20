#ifndef FILEMENU_H
#define FILEMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <opencv2/core/mat.hpp>
class FileMenu : public QMenu
{
    Q_OBJECT
public:
    QAction *open_Image_ = nullptr;
    QAction *exit_ = nullptr;


public:
    FileMenu(const QString &title,QWidget *parent = 0);

    cv::Mat image_Mat_;
    QString file_name_;

private slots:
    void ImreadImage();
};

#endif // FILEMENU_H
