#include "pagemanager.h"
pageManager *pageManager::_instance = 0;

pageManager::pageManager()
{
    CDM = CustomDownloadManager::Instance();
    QObject::connect(CDM,SIGNAL(imageDownloaded(QString)),SLOT(setNewsImage(QString)));
}

pageManager::~pageManager(){
    delete _instance;
}

pageManager* pageManager::Instance()
{
    if(_instance == NULL)
        _instance = new pageManager();
    return _instance;
}

void pageManager::createPages(QSqlQuery query, QListWidget* newsList)
{
    QString dateFormat = "dddd, MMMM d, yyyy"; //day of week, month, day num, year
    QString imgFileName = "";
    while(query.next())
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0,145));

        //create custom widget item and layout
        QWidget *newWidget = new QWidget();
        QLayout *newGrid = new QGridLayout();
        auto *newHLayout = new QHBoxLayout();

        //create item labels
        QLabel *titleLabel = new QLabel("<strong>Title: " + query.value(TITLE).toString() + "</strong>");
        QLabel *destLabel = new QLabel("<strong>Description:</strong> " + query.value(DESCRIPTION).toString());
            destLabel->setWordWrap(true);
        QLabel *srcLabel = new QLabel("<strong>Source:</strong> " + query.value(SOURCE).toString());
        QLabel *datLabel = new QLabel("<strong>Date:</strong> " + query.value(DATE).toDateTime().toString(dateFormat));
        QLabel *catLabel = new QLabel("<strong>Category:</strong> " + query.value(CATEGORY).toString());
        QLabel *picLabel = new QLabel();
        picLabel->setMaximumSize(200,200);
        picLabel->setMinimumSize(200,200);

        //create hashmap from pic name to pic label points
        imgFileName = CDM->saveFileName(QUrl(query.value(IMAGE).toString()));
        downloadNewsImage(query.value(IMAGE).toString());
        imgHash[imgFileName] = picLabel;


        newGrid->setSpacing(0);
        newGrid->addWidget(titleLabel);
        newGrid->addWidget(destLabel);
        newGrid->addWidget(srcLabel);
        newGrid->addWidget(datLabel);
        newGrid->addWidget(catLabel);

        newHLayout->addWidget(picLabel);
        newHLayout->addLayout(newGrid);
        newWidget->setLayout(newHLayout);

        item->setData(3, query.value(URL).toString());
        newsList->addItem(item);
        newsList->setItemWidget(item, newWidget);
    }
}

void pageManager::downloadNewsImage(QString url){
    CDM->startDownload(QUrl(url));
    //qDebug() << "downloading: " << url << endl;
}

void pageManager::setNewsImage(QString imageName){
    //qDebug() << "setting: " << imageName << endl;
    try{
        QLabel* picLabel = imgHash[imageName];

        QPixmap img(imageName);
        QSize imgSize(200,200);
        QPixmap smallerImg = img.scaled(imgSize);//,Qt::KeepAspectRatio);

        picLabel->setPixmap(smallerImg);
    }catch(...){
        qDebug() << "could not set news image";
    }
}

