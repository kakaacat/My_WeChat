#pragma once

#include "ui_ccmainwindow.h"
#include "basicwindow.h"

class CCMainWindow : public BasicWindow
{
    Q_OBJECT

public:
    CCMainWindow(QWidget *parent = nullptr);
    ~CCMainWindow();

public:
    void initControl();
    void setUserName(const QString& username);      //设置用户名
    void setLevelPixmap(int level);                 //设置等级
    void setHeadPixmap(const QString& headPath);    //设置头像
    void setStatusMenuIcon(const QString& statusPath); //设置状态
    //添加应用部件
    QWidget* addOtherAppExtension(const QString& appPath, const QString& appName);

private:
    Ui::CCMainWindowClass ui;
};
