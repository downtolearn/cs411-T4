#ifndef CUSTOMDOWNLOADMANAGER_H
#define CUSTOMDOWNLOADMANAGER_H

#include <QtCore>
#include <QtNetwork>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QDir>
#include <cstdio>

class QSslError;

using namespace std;


class CustomDownloadManager: public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QVector<QNetworkReply *> currentDownloads;

private:
    string imageDirectory;
    static CustomDownloadManager* _instance;
    static int count;

protected:
    CustomDownloadManager();

public:
    ~CustomDownloadManager();
    static CustomDownloadManager* Instance();
    void startDownload(const QUrl &url);
    bool saveFileToDisk(const QString &fileame, QIODevice *data);
    static bool isHttpRedirect(QNetworkReply *reply);
    QString saveFileName(const QUrl &url);
    int getCount();

public slots:
    void execute();
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);

signals:
    void imageDownloaded(QString filename);

};

#endif // CUSTOMDOWNLOADMANAGER_H
