#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMainWindow>
#include <QMediaPlaylist>
#include "MusicInfo.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_select_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_test_clicked();

    void readMusicInfo_File();
private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
};
#endif // MAINWINDOW_H
