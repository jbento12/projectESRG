/********************************************************************************
** Form generated from reading UI file 'secondwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDWINDOW_H
#define UI_SECONDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondWindow
{
public:
    QLabel *label_pic;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QCheckBox *checkBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QCalendarWidget *calendarWidget;
    QLCDNumber *lcdNumber;

    void setupUi(QDialog *SecondWindow)
    {
        if (SecondWindow->objectName().isEmpty())
            SecondWindow->setObjectName(QString::fromUtf8("SecondWindow"));
        SecondWindow->resize(1600, 1000);
        label_pic = new QLabel(SecondWindow);
        label_pic->setObjectName(QString::fromUtf8("label_pic"));
        label_pic->setGeometry(QRect(50, 300, 931, 601));
        horizontalLayoutWidget = new QWidget(SecondWindow);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(100, 30, 588, 181));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonBox = new QDialogButtonBox(horizontalLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        checkBox = new QCheckBox(horizontalLayoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        calendarWidget = new QCalendarWidget(SecondWindow);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(940, 20, 640, 203));
        lcdNumber = new QLCDNumber(SecondWindow);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(1390, 380, 131, 91));

        retranslateUi(SecondWindow);

        QMetaObject::connectSlotsByName(SecondWindow);
    } // setupUi

    void retranslateUi(QDialog *SecondWindow)
    {
        SecondWindow->setWindowTitle(QCoreApplication::translate("SecondWindow", "Dialog", nullptr));
        label_pic->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("SecondWindow", "ora_boas", nullptr));
        checkBox->setText(QCoreApplication::translate("SecondWindow", "CheckBox", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SecondWindow", "leave", nullptr));
        pushButton->setText(QCoreApplication::translate("SecondWindow", "take pic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondWindow: public Ui_SecondWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDWINDOW_H
