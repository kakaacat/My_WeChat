/********************************************************************************
** Form generated from reading UI file 'TalkWindowShell.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TALKWINDOWSHELL_H
#define UI_TALKWINDOWSHELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TalkWindowClass
{
public:

    void setupUi(QWidget *TalkWindowClass)
    {
        if (TalkWindowClass->objectName().isEmpty())
            TalkWindowClass->setObjectName(QString::fromUtf8("TalkWindowClass"));
        TalkWindowClass->resize(1043, 732);

        retranslateUi(TalkWindowClass);

        QMetaObject::connectSlotsByName(TalkWindowClass);
    } // setupUi

    void retranslateUi(QWidget *TalkWindowClass)
    {
        TalkWindowClass->setWindowTitle(QCoreApplication::translate("TalkWindowClass", "TalkWindowShell", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TalkWindowClass: public Ui_TalkWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TALKWINDOWSHELL_H
