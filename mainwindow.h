#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "file_menu.h"
#include "enhance_menu.h"
#include "filter_menu.h"
#include "segment_menu.h"
#include "help_menu.h"
#include "sharpen_menu.h"
#include "artistic_menu.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    FileMenu *file_menu_ = nullptr;
    EnhanceMenu *enhance_menu_ = nullptr;
    FilterMenu *filter_menu_ = nullptr;
    SegmentMenu *segment_menu_ = nullptr;
    HelpMenu *help_menu_ = nullptr;
    SharpenMenu *sharpen_menu_ = nullptr;
    ArtisticMenu *artistic_menu_ = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    cv::Mat left_image_;
    cv::Mat right_image_;

    //QImage mat2qim2(cv::Mat mat);
    QImage Mat2QImage(const cv::Mat& mat);
    void SetMenuMat();


public slots:
    void ShowLeftImage();
    void ShowRightImage(cv::Mat mat);
    void ClearMat();
    void SaveMat();
    void RecoveryMat();
public slots:
    void openPdf();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
