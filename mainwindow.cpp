#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QDebug>
#include<opencv2/opencv.hpp>

#include<QtCore>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint,true);  //设置可以使用最大按钮
    this->setWindowIcon(QIcon(":/new/prefix1/Resource/windowicon.png"));
    this->setWindowTitle(tr("图像处理"));

    file_menu_=new FileMenu("打开",this);
    ui->menubar->addMenu(file_menu_);
    connect(file_menu_->open_Image_,SIGNAL(triggered()),this,SLOT(ShowLeftImage()));
    connect(file_menu_->exit_,SIGNAL(triggered()),this,SLOT(close()));

    enhance_menu_ = new EnhanceMenu("图像增强",this);
    ui->menubar->addMenu(enhance_menu_);
    connect(enhance_menu_,SIGNAL(ChangeRightImage(cv::Mat)),this,SLOT(ShowRightImage(cv::Mat)));
    //connect(enhance_menu_->rgb2Gray_,SIGNAL(triggered()),this,SLOT(ShowRightImage()));

    filter_menu_ = new FilterMenu("图像滤波",this);
    ui->menubar->addMenu(filter_menu_);
    connect(filter_menu_,SIGNAL(ChangeRightImage(cv::Mat)),this,SLOT(ShowRightImage(cv::Mat)));

    segment_menu_ = new SegmentMenu("图像分割",this);
    ui->menubar->addMenu(segment_menu_);
    connect(segment_menu_,SIGNAL(ChangeRightImage(cv::Mat)),this,SLOT(ShowRightImage(cv::Mat)));
    //connect(ui->open_image,SIGNAL(triggered()),this,SLOT(openFile()));
    //connect(ui->help,SIGNAL(triggered()),this,SLOT(openPdf()));

    ui->toolBar->addAction(file_menu_->open_Image_);

    QAction *release_mat = new QAction("release");
    ui->toolBar->addAction(release_mat);
    release_mat->setIcon(QIcon(":/new/prefix1/Resource/release.png"));
    connect(release_mat,SIGNAL(triggered()),this,SLOT(ClearMat()));

    ui->toolBar->addSeparator();

    QAction *save_mat = new QAction("save");
    ui->toolBar->addAction(save_mat);
    save_mat->setIcon(QIcon(":/new/prefix1/Resource/save.png"));
    connect(save_mat,SIGNAL(triggered()),this,SLOT(SaveMat()));

    ui->toolBar->addSeparator();

    QAction *recovery_mat = new QAction("recovery");
    ui->toolBar->addAction(recovery_mat);
    recovery_mat->setIcon(QIcon(":/new/prefix1/Resource/recovery.png"));
    connect(recovery_mat,SIGNAL(triggered()),this,SLOT(RecoveryMat()));


    sharpen_menu_ = new SharpenMenu("图像锐化",this);
    ui->menubar->addMenu(sharpen_menu_);
    connect(sharpen_menu_,SIGNAL(ChangeRightImage(cv::Mat)),this,SLOT(ShowRightImage(cv::Mat)));

    artistic_menu_ = new ArtisticMenu("艺术效果",this);
    ui->menubar->addMenu(artistic_menu_);
    connect(artistic_menu_,SIGNAL(ChangeRightImage(cv::Mat)),this,SLOT(ShowRightImage(cv::Mat)));

    help_menu_ = new HelpMenu("帮助",this);
    ui->menubar->addMenu(help_menu_);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::Mat2QImage(const cv::Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        //qDebug()<<"111";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }

}

void MainWindow::ShowLeftImage()
{
    left_image_=file_menu_->image_Mat_;
    QImage qimage = Mat2QImage(left_image_);
    QGraphicsScene *scene = new QGraphicsScene;
    //向容器中添加文件路径为fileName（QString类型）的文件

    scene->addPixmap(QPixmap::fromImage(qimage));
    //借助graphicsView（QGraphicsView类）控件显示容器的内容
    ui->left_graphics_view_->setScene(scene);
    //开始显示
    ui->left_graphics_view_->show();
    SetMenuMat();
//    ui->graphicsView_2->setScene(scene);
//    ui->graphicsView_2->show();
    //qDebug()<<ui->menubar
}

void MainWindow::ShowRightImage(cv::Mat mat)
{
//    if(flag==1)
//    {
//        right_image_=enhance_menu_->enhance_image_;
//    }
    right_image_ = mat;
    //left_image_=file_menu_->image_Mat_;
    QImage qimage = Mat2QImage(right_image_);
    QGraphicsScene *scene = new QGraphicsScene;
    //向容器中添加文件路径为fileName（QString类型）的文件

    scene->addPixmap(QPixmap::fromImage(qimage));
    //借助graphicsView（QGraphicsView类）控件显示容器的内容
    ui->right_graphics_view_->setScene(scene);
    //开始显示
    ui->right_graphics_view_->show();
    //SetMenuMat();
//    ui->graphicsView_2->setScene(scene);
//    ui->graphicsView_2->show();

}

void MainWindow::SetMenuMat()
{
    EnhanceMenu::image = left_image_;
    SegmentMenu::image = left_image_;
    SharpenMenu::image = left_image_;
    FilterMenu::image = left_image_;
    ArtisticMenu::image = left_image_;

}

void MainWindow::ClearMat()
{
    //file_menu_->image_Mat_.release();
    //ShowLeftImage();
    right_image_.release();
    ShowRightImage(right_image_);

}

void MainWindow::SaveMat()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, tr("save image file"),
                   "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

       if(fileName.isEmpty())
       {
           QMessageBox mesg;
           mesg.warning(this,"警告","打开图片失败!");
           return;
       }

       cv::imwrite(fileName.toStdString(),right_image_);
}

void MainWindow::RecoveryMat()
{
    //qDebug()<<"success";
    ui->left_graphics_view_->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    ui->right_graphics_view_->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    QMatrix q;
    q.setMatrix(1,ui->left_graphics_view_->matrix().m12(),ui->left_graphics_view_->matrix().m21(),1,
                ui->left_graphics_view_->matrix().dx(),ui->left_graphics_view_->matrix().dy());
    ui->left_graphics_view_->setMatrix(q,false);
    ui->right_graphics_view_->setMatrix(q,false);
//    ShowLeftImage();
//    ShowRightImage(right_image_);
}
void MainWindow::openPdf()
{
    //QString qtManulFile="C:/Users/16858/Desktop/zh-google-styleguide-20220529.pdf";
    //QDesktopServices::openUrl(QUrl::fromLocalFile(qtManulFile));
}

