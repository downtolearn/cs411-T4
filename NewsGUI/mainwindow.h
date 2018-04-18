#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <algorithm>
#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include "querybuilder.h"
#include "customdownloadmanager.h"
#include "sqlconn.hpp"
//#include "newspages.h"
#include <QDesktopServices>
#include <QListWidget>
#include <QUrl>
#include <QLabel>
#include <QDialog>
#include <QSqlError>
#include <QSettings>
#include <QDateTime>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QObject>
#include <QHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* Instance(QString username, QString pass);
    void setupCategories();
    void setupSources();
    void driver();
    void restoreSettings();
    ~MainWindow();


protected:
     explicit MainWindow(QWidget *parent = 0);
     MainWindow(QString,QString,QWidget *parent = 0);

public slots:
    void loadDLImage(QString url);
    void addImage(QString imageName);

private slots:
    void on_clearSettingsButton_clicked();

    void on_updateSettingsButton_clicked();

    void on_newsListWidget_itemClicked(QListWidgetItem *item);

    void on_actionSettings_triggered();

    void on_categoryListWidget_itemChanged(QListWidgetItem *item);

    void on_sourcesListWidget_itemChanged(QListWidgetItem *item);

    void on_filterLineEdit_returnPressed();

    void on_sourcesLineEdit_textEdited(const QString &arg1);

    void on_dateCheckBox_stateChanged(int arg1);

    void downloadNewsImage(QString);

    void setNewsImages();

    void print_newsItems();
/*
    void getImageFromUrl(QString url);

    QPixmap downloadFinished(QNetworkReply *reply);
*/
private:
    Ui::MainWindow *ui;
    static MainWindow* _instance;
    QDialog settingsWindow;
    QSqlDatabase database;
    QueryBuilder queryBuilder;
    QStringList sources;
    QStringList activeSources;
    QStringList activeCategories;
    QStringList filterList;
    bool limitDate;
    QSettings settings;
    QDate begin;
    QDate end;
    CustomDownloadManager* CDM;
    QVector<QWidget*> newsListItems;
    QHash<QString,QLabel*> hashmap;

};

#endif // MAINWINDOW_H
