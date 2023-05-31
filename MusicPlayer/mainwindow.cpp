#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//1拖拽列表可以调整列表音乐的顺序 顺序播放 同时间只加载一首音乐
//2点击音乐时，重置播放按钮状态，音乐播放次数+1
//3找个地方显示音乐播放次数这种信息
//4歌词
//音乐时长、播放次数留用   错误日志  player那个库的error信号
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

void MainWindow::onDurationChanged(qint64 duration)
{
    ui->slider->setMaximum(duration);
    int secs = duration/1000;
    int mins = secs/60;
    secs = secs % 60;
    durationTime = QString::asprintf("%d:%d",mins,secs);
    ui->labPlayDurat->setText(durationTime);
}


void MainWindow::onPositionChanged(qint64 position)
{
    if(ui->slider->isSliderDown())
    {
        return;
    }
    if(state->isPlaying==false)
    {
        return;
    }

    ui->slider->setSliderPosition(position);
    int secs = position/1000;
    int mins = secs/60;
    secs = secs % 60;
    CurrentDurationTime = QString::asprintf("%d:%d",mins,secs);
    ui->labPlayCurrentDurat->setText(CurrentDurationTime);
    if(CurrentDurationTime==durationTime && durationTime!="0:0")
    {
        qDebug()<<CurrentDurationTime<<"CurrentDurationTime"<<CurrentDurationTime;
        player->stop();
        state->isPlaying = false;
        nextMusic();
    }

}

void MainWindow::on_pushButton_select_clicked()
{
//    QString fileName = QFileDialog::getOpenFileName(this,"select",".","music(*.mp3 *.wav *.flac *.ape)");
//    playlist->addMedia(QUrl::fromLocalFile(fileName));
//    player->setPlaylist(playlist);
//    ui->pushButton_play->setText("播放");
}

void MainWindow::on_pushButton_play_clicked()
{
    if(state->isPlaying)
    {
        pause();
        state->isPlaying=false;
        ui->pushButton_play->setText("播放");
    }
    else
    {
        player->play();
        state->isPlaying=true;
        ui->pushButton_play->setText("暂停");
    }


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

    query();
}

void MainWindow::playerInit()
{
    player=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    player->setVolume(50);
    ui->volumeSlider->setValue(50);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);

    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(onDurationChanged(qint64)));
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

void MainWindow::play()
{
    playlist->clear();
    //去掉\r\n
    int num = systemInfo->musicVector[systemInfo->currentPlayingOrder].localFilePath.count()-2;
    playlist->addMedia(QUrl::fromLocalFile(systemInfo->musicVector[systemInfo->currentPlayingOrder].localFilePath.left(num)));
    player->play();
    state->isPlaying =true;
}

void MainWindow::pause()
{
    player->pause();
    state->isPlaying =false;
}

void MainWindow::nextMusic()
{
    if(++systemInfo->currentPlayingOrder == ui->listWidget_musicList->count())
    {
        systemInfo->currentPlayingOrder=0;
    }
    play();
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    player->setVolume(value);
    state->setVolume(value);
}

void MainWindow::on_slider_sliderReleased()
{
    player->setPosition(ui->slider->value());
}

void MainWindow::on_listWidget_musicList_doubleClicked(const QModelIndex &index)
{
    state->isPlaying = false;
    player->stop();

    systemInfo->currentPlayingOrder = ui->listWidget_musicList->currentRow();
    play();
    ui->pushButton_play->setText("暂停");
}
