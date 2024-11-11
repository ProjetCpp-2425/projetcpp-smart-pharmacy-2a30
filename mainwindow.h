#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "product.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_sup_clicked();

    void on_non_clicked();

    void on_search_clicked();


    void on_pushButton_3_clicked();
    void on_generatePdfButton_clicked();

    void on_pdf_clicked();

private:
    Ui::MainWindow *ui;
  Product product;
   void searchProducts(const QString &searchTerm);
};


#endif // MAINWINDOW_H
