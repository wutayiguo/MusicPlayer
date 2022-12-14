#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMainWindow>
#include <QMediaPlaylist>
#include <QListWidget>
#include "MusicInfo.h"
#include "SystemInfo.h"

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_select_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_test_clicked();

    void on_listWidget_musicList_itemClicked(QListWidgetItem *item);
    void on_listWidget_musicList_customContextMenuRequested(const QPoint &pos);
    void listWidget_Action_Add();

    void on_tbPlay_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QMenu *listWidget_menu;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    SystemInfo *systemInfo;
};
#endif // MAINWINDOW_H
