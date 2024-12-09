/********************************************************************************
** Form generated from reading UI file 'dialogmodifier.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMODIFIER_H
#define UI_DIALOGMODIFIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialogmodifier
{
public:
    QLabel *label_26;
    QLineEdit *IDE;
    QLabel *label_27;
    QLineEdit *NOM;
    QLabel *label_25;
    QLineEdit *PRENOM;
    QLabel *prenom_2;
    QLineEdit *AGE;
    QLabel *label_31;
    QLineEdit *GENRE;
    QLabel *genre;
    QLineEdit *POSTE;
    QLabel *label_24;
    QLineEdit *STATUT;
    QLabel *lineEdit_stat;
    QLabel *label_29;
    QLineEdit *CIN;
    QLabel *label_22;
    QLineEdit *NUM;
    QLabel *label_21;
    QLineEdit *MAIL;
    QLabel *label_28;
    QLineEdit *DATE_EMB;
    QPushButton *MODIFIER;

    void setupUi(QDialog *Dialogmodifier)
    {
        if (Dialogmodifier->objectName().isEmpty())
            Dialogmodifier->setObjectName(QString::fromUtf8("Dialogmodifier"));
        Dialogmodifier->resize(1151, 601);
        label_26 = new QLabel(Dialogmodifier);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(400, 90, 351, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        label_26->setFont(font);
        label_26->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #99CC99 ; /* Couleur du texte en bleu clair */\n"
"}"));
        IDE = new QLineEdit(Dialogmodifier);
        IDE->setObjectName(QString::fromUtf8("IDE"));
        IDE->setGeometry(QRect(270, 180, 161, 31));
        label_27 = new QLabel(Dialogmodifier);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(220, 180, 91, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(14);
        label_27->setFont(font1);
        NOM = new QLineEdit(Dialogmodifier);
        NOM->setObjectName(QString::fromUtf8("NOM"));
        NOM->setGeometry(QRect(780, 180, 161, 31));
        label_25 = new QLabel(Dialogmodifier);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(700, 180, 81, 21));
        label_25->setFont(font1);
        PRENOM = new QLineEdit(Dialogmodifier);
        PRENOM->setObjectName(QString::fromUtf8("PRENOM"));
        PRENOM->setGeometry(QRect(780, 240, 161, 31));
        prenom_2 = new QLabel(Dialogmodifier);
        prenom_2->setObjectName(QString::fromUtf8("prenom_2"));
        prenom_2->setGeometry(QRect(680, 240, 91, 21));
        prenom_2->setFont(font1);
        AGE = new QLineEdit(Dialogmodifier);
        AGE->setObjectName(QString::fromUtf8("AGE"));
        AGE->setGeometry(QRect(270, 240, 161, 31));
        label_31 = new QLabel(Dialogmodifier);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(210, 240, 91, 21));
        label_31->setFont(font1);
        GENRE = new QLineEdit(Dialogmodifier);
        GENRE->setObjectName(QString::fromUtf8("GENRE"));
        GENRE->setGeometry(QRect(780, 300, 161, 31));
        genre = new QLabel(Dialogmodifier);
        genre->setObjectName(QString::fromUtf8("genre"));
        genre->setGeometry(QRect(700, 300, 81, 31));
        genre->setFont(font1);
        POSTE = new QLineEdit(Dialogmodifier);
        POSTE->setObjectName(QString::fromUtf8("POSTE"));
        POSTE->setGeometry(QRect(270, 300, 161, 31));
        label_24 = new QLabel(Dialogmodifier);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(200, 300, 91, 31));
        label_24->setFont(font1);
        STATUT = new QLineEdit(Dialogmodifier);
        STATUT->setObjectName(QString::fromUtf8("STATUT"));
        STATUT->setGeometry(QRect(780, 360, 161, 31));
        lineEdit_stat = new QLabel(Dialogmodifier);
        lineEdit_stat->setObjectName(QString::fromUtf8("lineEdit_stat"));
        lineEdit_stat->setGeometry(QRect(700, 360, 81, 31));
        lineEdit_stat->setFont(font1);
        label_29 = new QLabel(Dialogmodifier);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(90, 470, 211, 51));
        label_29->setFont(font1);
        CIN = new QLineEdit(Dialogmodifier);
        CIN->setObjectName(QString::fromUtf8("CIN"));
        CIN->setGeometry(QRect(270, 360, 161, 31));
        label_22 = new QLabel(Dialogmodifier);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(210, 370, 91, 21));
        label_22->setFont(font1);
        NUM = new QLineEdit(Dialogmodifier);
        NUM->setObjectName(QString::fromUtf8("NUM"));
        NUM->setGeometry(QRect(780, 420, 161, 31));
        label_21 = new QLabel(Dialogmodifier);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(680, 420, 161, 31));
        label_21->setFont(font1);
        MAIL = new QLineEdit(Dialogmodifier);
        MAIL->setObjectName(QString::fromUtf8("MAIL"));
        MAIL->setGeometry(QRect(270, 420, 161, 31));
        label_28 = new QLabel(Dialogmodifier);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(190, 420, 101, 31));
        label_28->setFont(font1);
        DATE_EMB = new QLineEdit(Dialogmodifier);
        DATE_EMB->setObjectName(QString::fromUtf8("DATE_EMB"));
        DATE_EMB->setGeometry(QRect(270, 480, 161, 31));
        MODIFIER = new QPushButton(Dialogmodifier);
        MODIFIER->setObjectName(QString::fromUtf8("MODIFIER"));
        MODIFIER->setGeometry(QRect(810, 520, 181, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(20);
        font2.setItalic(true);
        MODIFIER->setFont(font2);
        MODIFIER->setMouseTracking(true);
        MODIFIER->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
""));
        MODIFIER->setCheckable(true);
        MODIFIER->setChecked(true);
        MODIFIER->setAutoRepeat(false);

        retranslateUi(Dialogmodifier);

        QMetaObject::connectSlotsByName(Dialogmodifier);
    } // setupUi

    void retranslateUi(QDialog *Dialogmodifier)
    {
        Dialogmodifier->setWindowTitle(QCoreApplication::translate("Dialogmodifier", "Dialog", nullptr));
        label_26->setText(QCoreApplication::translate("Dialogmodifier", "Modifier Employ\303\251", nullptr));
        label_27->setText(QCoreApplication::translate("Dialogmodifier", "ID :", nullptr));
        label_25->setText(QCoreApplication::translate("Dialogmodifier", "Nom :", nullptr));
        prenom_2->setText(QCoreApplication::translate("Dialogmodifier", "Prenom :", nullptr));
        label_31->setText(QCoreApplication::translate("Dialogmodifier", "age:", nullptr));
        genre->setText(QCoreApplication::translate("Dialogmodifier", "genre:", nullptr));
        label_24->setText(QCoreApplication::translate("Dialogmodifier", "poste:", nullptr));
        lineEdit_stat->setText(QCoreApplication::translate("Dialogmodifier", "Statut :", nullptr));
        label_29->setText(QCoreApplication::translate("Dialogmodifier", "date d'embauhe:", nullptr));
        label_22->setText(QCoreApplication::translate("Dialogmodifier", "CIN :", nullptr));
        label_21->setText(QCoreApplication::translate("Dialogmodifier", "numero :", nullptr));
        label_28->setText(QCoreApplication::translate("Dialogmodifier", "Email :", nullptr));
        MODIFIER->setText(QCoreApplication::translate("Dialogmodifier", "modifier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialogmodifier: public Ui_Dialogmodifier {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMODIFIER_H
