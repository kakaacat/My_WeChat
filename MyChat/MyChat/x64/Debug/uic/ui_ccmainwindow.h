/********************************************************************************
** Form generated from reading UI file 'ccmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCMAINWINDOW_H
#define UI_CCMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CCMainWindowClass
{
public:

    void setupUi(QWidget *CCMainWindowClass)
    {
        if (CCMainWindowClass->objectName().isEmpty())
            CCMainWindowClass->setObjectName(QString::fromUtf8("CCMainWindowClass"));
        CCMainWindowClass->resize(600, 400);

        retranslateUi(CCMainWindowClass);

        QMetaObject::connectSlotsByName(CCMainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *CCMainWindowClass)
    {
        CCMainWindowClass->setWindowTitle(QCoreApplication::translate("CCMainWindowClass", "CCMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CCMainWindowClass: public Ui_CCMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCMAINWINDOW_H
