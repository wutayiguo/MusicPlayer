#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMainWindow>
#include <QMediaPlaylist>
#include <QListWidget>
#include "MusicInfo.h"
#include "SystemInfo.h"
#include "playerstate.h"

#include <QMenu>
#include <QAction>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void readMusicInfo_File();
    void listWidgetInit();
    void playerInit();
    void query();
    void play();
    void pause();
    void nextMusic();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_select_clicked();
    void on_pushButton_play_clicked();
    void on_pushButton_test_clicked();
    void on_listWidget_musicList_customContextMenuRequested(const QPoint &pos);
    void listWidget_Action_Add();
    void on_volumeSlider_valueChanged(int value);
    void on_slider_sliderReleased();
    void onPositionChanged(qint64);
    void onDurationChanged(qint64);

    void on_listWidget_musicList_doubleClicked(const QModelIndex &index);

private:
    PlayerState *state = new PlayerState();
    QString durationTime;
    QString CurrentDurationTime;
    Ui::MainWindow *ui;
    QMenu *listWidget_menu;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    SystemInfo *systemInfo;
};
#endif // MAINWINDOW_H
