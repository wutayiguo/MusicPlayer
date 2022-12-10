#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player=new QMediaPlayer(this);
    player->setVolume(50);
    playlist=new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_select_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"select",".","music(*.mp3 *.wav)");
    qDebug()<<fileName;
//    playlist->addMedia(QUrl::fromLocalFile(fileName));
//    player->setPlaylist(playlist);


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
//    QStringList fileNames = QFileDialog::getOpenFileNames(this,"select",".","music(*.mp3 *.wav)");
//    for(int i=0;i<fileNames.count();i++)
//    {
//        auto item=new QListWidgetItem(fileNames[i]);
//        ui->listWidget_musicList->addItem(item);
//    }
    QString s= "nums:0|times:03:25|count:0|local:E:/音乐/音乐/作曲家-李荣浩.wav";
    MusicInfo *musicInfo = new MusicInfo(s);
}

void MainWindow::readMusicInfo_File()
{

}



