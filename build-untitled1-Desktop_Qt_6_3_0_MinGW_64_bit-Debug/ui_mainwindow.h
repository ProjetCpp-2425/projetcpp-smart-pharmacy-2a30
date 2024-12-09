/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QLabel *label_26;
    QLabel *label_25;
    QLabel *prenom_2;
    QLabel *genre_2;
    QLabel *label_24;
    QLabel *lineEdit_stat;
    QLineEdit *lineEdit_nomE;
    QLineEdit *lineEdit_prenomE;
    QLineEdit *lineEdit_genreE;
    QLineEdit *lineEdit_posteE;
    QLabel *label_27;
    QLineEdit *lineEdit_idE;
    QLabel *label_22;
    QLineEdit *lineEdit_cinE;
    QLabel *label_21;
    QLineEdit *lineEdit_numE;
    QLabel *label_28;
    QLineEdit *lineEdit_mailE;
    QPushButton *pushButton_ajouter;
    QLabel *label_29;
    QLineEdit *lineEdit_date_embE;
    QLineEdit *lineEdit_statutE;
    QLineEdit *lineEdit_ageE;
    QLabel *label_31;
    QWidget *tab_2;
    QLabel *label_17;
    QPushButton *exporterEnPDF;
    QLabel *label_18;
    QComboBox *comboBox_2;
    QPushButton *refresh;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QPushButton *pushButton_supprimer;
    QLabel *label_30;
    QTableView *tableView;
    QLabel *label_32;
    QLineEdit *lineEdit_ID;
    QTabWidget *tabWidget_3;
    QWidget *tab_5;
    QLabel *label_19;
    QLineEdit *chercher;
    QWidget *tab_6;
    QComboBox *comboBoxTri;
    QPushButton *tri;
    QPushButton *resetButton;
    QLineEdit *lineEdit_idEsupp;
    QPushButton *quitter;
    QPushButton *pushButton_Modifier;
    QWidget *tab_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1514, 1157);
        MainWindow->setMouseTracking(true);
        MainWindow->setAnimated(true);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(470, 0, 691, 61));
        QPalette palette;
        QBrush brush(QColor(41, 171, 226, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 150, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 203, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 176, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 75, 127, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 100, 170, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush6(QColor(127, 202, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush7(QColor(236, 236, 236, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush7);
        QBrush brush8(QColor(255, 255, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush8);
        QBrush brush9(QColor(245, 245, 245, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush9);
        QBrush brush10(QColor(191, 191, 191, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush10);
        QBrush brush11(QColor(169, 169, 169, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush11);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush9);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush);
#endif
        label->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(36);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #29ABE2; /* Couleur du texte en bleu clair */\n"
"}\n"
""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(720, 60, 251, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Menlo")});
        font1.setItalic(false);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #646669; /* Gris fonc\303\251 */\n"
"}\n"
""));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 0, 81, 61));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../Desktop/Capture d\342\200\231\303\251cran 2024-09-30 \303\240 02.40.50.png")));
        label_3->setScaledContents(true);
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 20, 291, 701));
        QPalette palette1;
        QBrush brush12(QColor(218, 242, 243, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush12);
        tabWidget_2->setPalette(palette1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_26 = new QLabel(tab);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(0, 10, 271, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(16);
        font2.setBold(true);
        label_26->setFont(font2);
        label_26->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #99CC99 ; /* Couleur du texte en bleu clair */\n"
"}"));
        label_25 = new QLabel(tab);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(40, 110, 81, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(14);
        label_25->setFont(font3);
        prenom_2 = new QLabel(tab);
        prenom_2->setObjectName(QString::fromUtf8("prenom_2"));
        prenom_2->setGeometry(QRect(10, 150, 91, 21));
        prenom_2->setFont(font3);
        genre_2 = new QLabel(tab);
        genre_2->setObjectName(QString::fromUtf8("genre_2"));
        genre_2->setGeometry(QRect(30, 230, 81, 21));
        genre_2->setFont(font3);
        label_24 = new QLabel(tab);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(40, 270, 91, 31));
        label_24->setFont(font3);
        lineEdit_stat = new QLabel(tab);
        lineEdit_stat->setObjectName(QString::fromUtf8("lineEdit_stat"));
        lineEdit_stat->setGeometry(QRect(30, 310, 81, 31));
        lineEdit_stat->setFont(font3);
        lineEdit_nomE = new QLineEdit(tab);
        lineEdit_nomE->setObjectName(QString::fromUtf8("lineEdit_nomE"));
        lineEdit_nomE->setGeometry(QRect(110, 110, 161, 31));
        lineEdit_prenomE = new QLineEdit(tab);
        lineEdit_prenomE->setObjectName(QString::fromUtf8("lineEdit_prenomE"));
        lineEdit_prenomE->setGeometry(QRect(110, 150, 161, 31));
        lineEdit_genreE = new QLineEdit(tab);
        lineEdit_genreE->setObjectName(QString::fromUtf8("lineEdit_genreE"));
        lineEdit_genreE->setGeometry(QRect(110, 230, 161, 31));
        lineEdit_posteE = new QLineEdit(tab);
        lineEdit_posteE->setObjectName(QString::fromUtf8("lineEdit_posteE"));
        lineEdit_posteE->setGeometry(QRect(110, 270, 161, 31));
        label_27 = new QLabel(tab);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(70, 70, 91, 21));
        label_27->setFont(font3);
        lineEdit_idE = new QLineEdit(tab);
        lineEdit_idE->setObjectName(QString::fromUtf8("lineEdit_idE"));
        lineEdit_idE->setGeometry(QRect(110, 70, 161, 31));
        label_22 = new QLabel(tab);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(50, 350, 91, 21));
        label_22->setFont(font3);
        lineEdit_cinE = new QLineEdit(tab);
        lineEdit_cinE->setObjectName(QString::fromUtf8("lineEdit_cinE"));
        lineEdit_cinE->setGeometry(QRect(110, 350, 161, 31));
        label_21 = new QLabel(tab);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 390, 161, 31));
        label_21->setFont(font3);
        lineEdit_numE = new QLineEdit(tab);
        lineEdit_numE->setObjectName(QString::fromUtf8("lineEdit_numE"));
        lineEdit_numE->setGeometry(QRect(110, 390, 161, 31));
        label_28 = new QLabel(tab);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(30, 430, 101, 31));
        label_28->setFont(font3);
        lineEdit_mailE = new QLineEdit(tab);
        lineEdit_mailE->setObjectName(QString::fromUtf8("lineEdit_mailE"));
        lineEdit_mailE->setGeometry(QRect(110, 430, 161, 31));
        pushButton_ajouter = new QPushButton(tab);
        pushButton_ajouter->setObjectName(QString::fromUtf8("pushButton_ajouter"));
        pushButton_ajouter->setGeometry(QRect(40, 560, 181, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(20);
        font4.setItalic(true);
        pushButton_ajouter->setFont(font4);
        pushButton_ajouter->setMouseTracking(true);
        pushButton_ajouter->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
""));
        pushButton_ajouter->setCheckable(true);
        pushButton_ajouter->setChecked(true);
        pushButton_ajouter->setAutoRepeat(false);
        label_29 = new QLabel(tab);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(0, 460, 211, 51));
        label_29->setFont(font3);
        lineEdit_date_embE = new QLineEdit(tab);
        lineEdit_date_embE->setObjectName(QString::fromUtf8("lineEdit_date_embE"));
        lineEdit_date_embE->setGeometry(QRect(110, 500, 161, 31));
        lineEdit_statutE = new QLineEdit(tab);
        lineEdit_statutE->setObjectName(QString::fromUtf8("lineEdit_statutE"));
        lineEdit_statutE->setGeometry(QRect(110, 310, 161, 31));
        lineEdit_ageE = new QLineEdit(tab);
        lineEdit_ageE->setObjectName(QString::fromUtf8("lineEdit_ageE"));
        lineEdit_ageE->setGeometry(QRect(110, 190, 161, 31));
        label_31 = new QLabel(tab);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(50, 190, 91, 21));
        label_31->setFont(font3);
        tabWidget_2->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_17 = new QLabel(tab_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(60, 10, 181, 31));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(14);
        font5.setBold(true);
        label_17->setFont(font5);
        label_17->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #99CC99 ; /* Couleur du texte en bleu clair */\n"
"}"));
        exporterEnPDF = new QPushButton(tab_2);
        exporterEnPDF->setObjectName(QString::fromUtf8("exporterEnPDF"));
        exporterEnPDF->setGeometry(QRect(10, 170, 151, 31));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Segoe UI")});
        font6.setPointSize(14);
        font6.setItalic(true);
        exporterEnPDF->setFont(font6);
        exporterEnPDF->setMouseTracking(true);
        exporterEnPDF->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
"\n"
""));
        exporterEnPDF->setCheckable(true);
        exporterEnPDF->setChecked(true);
        label_18 = new QLabel(tab_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(20, 50, 121, 41));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Segoe UI")});
        font7.setPointSize(14);
        font7.setBold(false);
        font7.setItalic(true);
        label_18->setFont(font7);
        comboBox_2 = new QComboBox(tab_2);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(90, 60, 103, 32));
        QFont font8;
        font8.setPointSize(14);
        comboBox_2->setFont(font8);
        refresh = new QPushButton(tab_2);
        refresh->setObjectName(QString::fromUtf8("refresh"));
        refresh->setGeometry(QRect(30, 640, 211, 31));
        refresh->setFont(font6);
        refresh->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
"\n"
""));
        refresh->setCheckable(true);
        refresh->setChecked(true);
        tabWidget_2->addTab(tab_2, QString());
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(310, 50, 1201, 731));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        pushButton_supprimer = new QPushButton(tab_3);
        pushButton_supprimer->setObjectName(QString::fromUtf8("pushButton_supprimer"));
        pushButton_supprimer->setGeometry(QRect(230, 40, 131, 31));
        pushButton_supprimer->setFont(font6);
        pushButton_supprimer->setMouseTracking(true);
        pushButton_supprimer->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
"\n"
""));
        pushButton_supprimer->setCheckable(true);
        pushButton_supprimer->setChecked(true);
        label_30 = new QLabel(tab_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(40, 40, 51, 31));
        label_30->setFont(font3);
        tableView = new QTableView(tab_3);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(20, 80, 1151, 411));
        label_32 = new QLabel(tab_3);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(770, 40, 51, 31));
        label_32->setFont(font3);
        lineEdit_ID = new QLineEdit(tab_3);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setGeometry(QRect(810, 40, 141, 31));
        tabWidget_3 = new QTabWidget(tab_3);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        tabWidget_3->setGeometry(QRect(70, 500, 871, 101));
        QPalette palette2;
        QBrush brush13(QColor(227, 246, 245, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush13);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush13);
        tabWidget_3->setPalette(palette2);
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        label_19 = new QLabel(tab_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(40, 20, 291, 21));
        label_19->setFont(font3);
        chercher = new QLineEdit(tab_5);
        chercher->setObjectName(QString::fromUtf8("chercher"));
        chercher->setGeometry(QRect(310, 20, 389, 26));
        tabWidget_3->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        comboBoxTri = new QComboBox(tab_6);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("vert");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        comboBoxTri->addItem(icon, QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->setObjectName(QString::fromUtf8("comboBoxTri"));
        comboBoxTri->setGeometry(QRect(140, 20, 251, 31));
        comboBoxTri->setFont(font8);
        tri = new QPushButton(tab_6);
        tri->setObjectName(QString::fromUtf8("tri"));
        tri->setGeometry(QRect(480, 20, 141, 31));
        tri->setFont(font6);
        tri->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
""));
        tri->setCheckable(true);
        tri->setChecked(true);
        resetButton = new QPushButton(tab_6);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(660, 20, 141, 31));
        resetButton->setFont(font6);
        resetButton->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
""));
        resetButton->setCheckable(true);
        resetButton->setChecked(true);
        tabWidget_3->addTab(tab_6, QString());
        lineEdit_idEsupp = new QLineEdit(tab_3);
        lineEdit_idEsupp->setObjectName(QString::fromUtf8("lineEdit_idEsupp"));
        lineEdit_idEsupp->setGeometry(QRect(80, 40, 141, 31));
        quitter = new QPushButton(tab_3);
        quitter->setObjectName(QString::fromUtf8("quitter"));
        quitter->setGeometry(QRect(1010, 580, 161, 31));
        quitter->setFont(font5);
        quitter->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
""));
        quitter->setCheckable(true);
        quitter->setChecked(true);
        pushButton_Modifier = new QPushButton(tab_3);
        pushButton_Modifier->setObjectName(QString::fromUtf8("pushButton_Modifier"));
        pushButton_Modifier->setGeometry(QRect(970, 40, 151, 31));
        pushButton_Modifier->setFont(font6);
        pushButton_Modifier->setMouseTracking(true);
        pushButton_Modifier->setStyleSheet(QString::fromUtf8("QPushButton:checked {\n"
"    background-color: #99CC99; /* Couleur de fond lorsque le bouton est coch\303\251 */\n"
"    color: white;              /* Couleur du texte souhait\303\251e */\n"
"    border: 1px solid #99CC99; /* Bordure si n\303\251cessaire */\n"
"}\n"
"\n"
""));
        pushButton_Modifier->setCheckable(true);
        pushButton_Modifier->setChecked(true);
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1514, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(1);
        tabWidget->setCurrentIndex(1);
        tabWidget_3->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "    Gestion des Employ\303\251s", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "G\303\251rez efficacement votre \303\251quipe", nullptr));
        label_3->setText(QString());
        label_26->setText(QCoreApplication::translate("MainWindow", "Formulaire Employ\303\251", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        prenom_2->setText(QCoreApplication::translate("MainWindow", "Prenom :", nullptr));
        genre_2->setText(QCoreApplication::translate("MainWindow", "genre:", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "poste:", nullptr));
        lineEdit_stat->setText(QCoreApplication::translate("MainWindow", "Statut :", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "CIN :", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "numero :", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "Email :", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "date d'embauhe:", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "age:", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QCoreApplication::translate("MainWindow", "formulaire", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Actions Rapides  ", nullptr));
        exporterEnPDF->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Filtrer:", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "actif", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "inactif", nullptr));

        refresh->setText(QCoreApplication::translate("MainWindow", "Refresh Statistiques", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("MainWindow", "actions rapides", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "chercher avec nom:", nullptr));
        chercher->setInputMask(QString());
        chercher->setText(QString());
        chercher->setPlaceholderText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_5), QCoreApplication::translate("MainWindow", "cherche", nullptr));
        comboBoxTri->setItemText(0, QCoreApplication::translate("MainWindow", "Date d'embauche", nullptr));
        comboBoxTri->setItemText(1, QCoreApplication::translate("MainWindow", "poste", nullptr));
        comboBoxTri->setItemText(2, QCoreApplication::translate("MainWindow", "statut", nullptr));

        tri->setText(QCoreApplication::translate("MainWindow", "trier", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "reset", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_6), QCoreApplication::translate("MainWindow", "trier", nullptr));
        quitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        pushButton_Modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
