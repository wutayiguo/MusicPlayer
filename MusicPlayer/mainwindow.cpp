#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//1拖拽列表可以调整列表音乐的顺序
//2点击音乐时，重置播放按钮状态，音乐播放次数+1
//3找个地方显示音乐播放次数这种信息
//4歌词
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
    ui->slider->setSliderPosition(position);
    int secs = position/1000;
    int mins = secs/60;
    secs = secs % 60;
    positionTime = QString::asprintf("%d:%d",mins,secs);
    ui->labPlayCurrentDurat->setText(positionTime);


//    //(分*60+秒)*100+厘秒
//    int pos = position/10;
//    QMap<int, QString>::iterator iter = lrcMap.begin();
//        while (iter != lrcMap.end())
//        {
//            if(pos-50<=iter.key()&& pos+50>=iter.key())
//            {
//                    int j=0;
//                    if(iter != lrcMap.begin())
//                    {
//                        iter--;
//                        ui->label_20->setText(iter.value());
//                        j++;
//                    }
//                    if(iter != lrcMap.begin())
//                    {
//                        iter--;
//                        ui->label_19->setText(iter.value());
//                        j++;
//                    }

//                    if(iter != lrcMap.begin())
//                    {
//                        iter--;
//                        ui->label_6->setText(iter.value());
//                        j++;
//                    }
//                    for(;j>0;j--)
//                    {
//                        iter++;
//                    }
//               //中间
//               ui->label_21->setText(iter.value());
//               iter++;
//               if(iter != lrcMap.end())
//               {
//                   ui->label_22->setText(iter.value());
//               }
//               else
//               {
//                   ui->label_22->setText("");
//                   return;
//               }
//               iter++;
//               if(iter != lrcMap.end())
//               {
//                   ui->label_23->setText(iter.value());
//               }
//               else
//               {
//                   ui->label_23->setText("");
//                   return;
//               }
//               iter++;
//               if(iter != lrcMap.end())
//               {
//                   ui->label_24->setText(iter.value());
//               }
//               else
//               {
//                   ui->label_24->setText("");
//                   return;
//               }
//               iter++;
//               if(iter != lrcMap.end())
//               {
//                   ui->label_25->setText(iter.value());
//               }
//               else
//               {
//                   ui->label_25->setText("");
//                   return;
//               }
//               iter++;
//               if(iter != lrcMap.end())
//               {
//                   ui->label_26->setText(iter.value());
//               }
//               else
//               {
//                   ui->label_26->setText("");
//                   return;
//               }
//               iter++;
//               if(iter != lrcMap.end())
//               {
//                   ui->label_27->setText(iter.value());
//               }
//               else
//               {
//                   ui->label_27->setText("");
//                   return;
//               }
//            }
//            iter++;
//        }
}

void MainWindow::on_pushButton_select_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"select",".","music(*.mp3 *.wav *.flac *.ape)");
    playlist->addMedia(QUrl::fromLocalFile(fileName));
    player->setPlaylist(playlist);
}

void MainWindow::on_pushButton_play_clicked()
{
    if(state->isPlaying)
    {
        pause();
        ui->pushButton_play->setText("播放");
    }
    else
    {
        play();
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
    player->setVolume(60);
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

void MainWindow::on_listWidget_musicList_itemClicked(QListWidgetItem *item)
{
    playlist->clear();
    //去掉\r\n
    int num = systemInfo->musicVector[ui->listWidget_musicList->currentRow()].localFilePath.count()-2;

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

void MainWindow::play()
{
    player->play();
    state->isPlaying =true;
}

void MainWindow::pause()
{
    player->pause();
    state->isPlaying =false;
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    player->setVolume(value);
    state->setVolume(value);
    qDebug()<<value;
}

void MainWindow::on_slider_sliderPressed()
{

}

void MainWindow::on_slider_sliderReleased()
{
    qDebug()<<ui->slider->value();
    player->setPosition(ui->slider->value());
}
