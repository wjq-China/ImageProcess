#include "help_menu.h"
#include <QDesktopServices>
#include <QUrl>
//#include <QDialog>
HelpMenu::HelpMenu(const QString &title,QWidget *parent):
                    QMenu(title,parent)
{
    help_ = new QAction("help",this);
    help_->setIcon(QIcon(":/new/prefix1/Resource/help.png"));
    this->addAction(help_);
    connect(help_,SIGNAL(triggered()),this,SLOT(OpenHelpPdf()));

    about_us_ = new QAction("关于我们",this);
    this->addAction(about_us_);
    //需要一个widget，可使用代码进行添加
    connect(about_us_,SIGNAL(triggered()),this,SLOT(AboutUs()));

}

void HelpMenu::OpenHelpPdf()
{
    //QString qtManulFile="‪C:/Users/16858/Desktop/1.pdf";
    QString qtManulFile = "C:/Users/16858/Desktop/1.pdf";
    QDesktopServices::openUrl(QUrl::fromLocalFile(qtManulFile));
}

void HelpMenu::AboutUs()
{
    aboutUsDialog = new QDialog;

    QLabel *textLable = new QLabel(aboutUsDialog);

    textLable->setText(tr("It's not a project, it's not a project,it's nothing."
                          " This software is just for own entertainment. "
                          "Team members include: jiaqi wang,changchun zhang,qiwei huan,xue wang,tengfei niu,jie mo."));
    textLable->adjustSize();
    textLable->setGeometry((QRect(0, 0, 250, 30*4)));
    textLable->setWordWrap(true);
    textLable->setAlignment(Qt::AlignTop);
    aboutUsDialog->setWindowTitle("关于我们");
    aboutUsDialog->show();


}
