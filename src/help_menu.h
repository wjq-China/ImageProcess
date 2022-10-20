#ifndef HELPMENU_H
#define HELPMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <ui_aboutus.h>

class HelpMenu : public QMenu
{
    Q_OBJECT
public:
    HelpMenu(const QString &title,QWidget *parent = 0);
    QAction *help_ = nullptr;
    QAction *about_us_ = nullptr;
    QDialog *aboutUsDialog;
public slots:
    void OpenHelpPdf();
    void AboutUs();
};

#endif // HELPMENU_H
