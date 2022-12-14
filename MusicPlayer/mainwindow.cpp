#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    systemInfo = new SystemInfo();
    listWidgetInit();
    playerInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_select_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"select",".","music(*.mp3 *.wav *.flac *.ape)");
    playlist->addMedia(QUrl::fromLocalFile(fileName));
    player->setPlaylist(playlist);
}

void MainWindow::on_pushButton_play_clicked()
{
    player->play();
}

void MainWindow::on_pushButton_pause_clicked()
{
    player->pause();
}

void MainWindow::on_pushButton_test_clicked()
{
    //"music(*.mp3 *.wav *.flac *.ape)" 仅支持前两种？
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"select",".","music(*.mp3 *.wav)");
    for(int i=0;i<fileNames.count();i++)
    {
        auto item=new QListWidgetItem(fileNames[i]);
        ui->listWidget_musicList->addItem(item);
    }

}

void MainWindow::readMusicInfo_File()
{

}

void MainWindow::listWidgetInit()
{
    ui->listWidget_musicList->setContextMenuPolicy(Qt::CustomContextMenu);
    listWidget_menu = new QMenu(ui->listWidget_musicList);
    QAction *actionAdd = new QAction("添加", this);
    connect(actionAdd, SIGNAL(triggered()), this, SLOT(listWidget_Action_Add()));
    listWidget_menu->addAction(actionAdd);


//        action = new QAction("Remove", this);
//        connect(action, SIGNAL(triggered()), this, SLOT(slotActionRemove()));
//        table_widget_menu->addAction(action);
    query();
}

void MainWindow::playerInit()
{
    player=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    player->setVolume(60);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
}

void MainWindow::query()
{
    ui->listWidget_musicList->clear();
    for(int i=0;i<systemInfo->musicVector.count();i++)
    {
        auto item=new QListWidgetItem(systemInfo->musicVector[i].name);
        ui->listWidget_musicList->addItem(item);
    }
}

void MainWindow::on_listWidget_musicList_itemClicked(QListWidgetItem *item)
{
    playlist->clear();
    //去掉\r\n
    int num = systemInfo->musicVector[ui->listWidget_musicList->currentRow()].localFilePath.count()-2;
    qDebug()<<"addMedia:"+systemInfo->musicVector[ui->listWidget_musicList->currentRow()].localFilePath;
    playlist->addMedia(QUrl::fromLocalFile(systemInfo->musicVector[ui->listWidget_musicList->currentRow()].localFilePath.left(num)));
    //playlist->addMedia(QUrl::fromLocalFile(systemInfo->musicVector[ui->listWidget_musicList->currentRow()].localFilePath));
}

void MainWindow::on_listWidget_musicList_customContextMenuRequested(const QPoint &pos)
{
    listWidget_menu->exec(QCursor::pos());
}

void MainWindow::listWidget_Action_Add()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"select",".","music(*.mp3 *.wav)");
    for(auto str:fileNames)
    {
        systemInfo->add(str);
    }
    query();
}

void MainWindow::on_tbPlay_toggled(bool checked)
{
    if(checked){
        ui->tbPlay->setIcon(QIcon(":/new/prefix1/images/pause.png"));
        player->play();}
    else{ui->tbPlay->setIcon(QIcon(":/new/prefix1/images/play.png"));
        player->pause();}
}
