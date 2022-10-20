#include "file_menu.h"
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
FileMenu::FileMenu(const QString &title,QWidget *parent):
        QMenu(title,parent)
{
    open_Image_ = new QAction(tr("打开"),this);
    open_Image_->setIcon(QIcon(":/new/prefix1/Resource/open.png"));
    this->addAction(open_Image_);
    connect(open_Image_,SIGNAL(triggered()),this,SLOT(ImreadImage()));

    exit_ = new QAction(tr("exit"),this);
    exit_->setIcon(QIcon(":/new/prefix1/Resource/exit.png"));
    this->addAction(exit_);


}

void FileMenu::ImreadImage()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("open image file"),
                   "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

       if(fileName.isEmpty())
       {
           //QMessageBox mesg;
           //mesg.warning(this,"警告","打开图片失败!");
           return;
       }


      //需要有一个对图像的判断，判断是否读入的图像是否为空


    //qDebug()<<fileName;
    cv::Mat image = cv::imread(fileName.toStdString());
//    cv::imshow("output",image);
//    cv::waitKey(0);
    //qDebug()<<image.rows;
    image_Mat_ = image;
    file_name_ = fileName;

}
