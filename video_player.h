#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H
#include "video_item.h"
#include <iostream>
#include <string>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QAudioOutput>
#include <QSplitter>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QGridLayout>
#include <QString>
#include <QUrl>
#include <QProgressBar>
#include "video_player_slider.h"
#include <QTimer>
#include <QListWidget>
#include <QFileInfo>
#include <QDir>
#include <QStringList>
#include <QFileInfoList>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>

using namespace::std;

class video_player : public QWidget
{
    Q_OBJECT
private:
    QMediaPlayer* media_player;
    QVideoWidget* display_player;
    QPushButton *toggle_play_button;
    QListWidget* video_list;
    int vl_size_before_hide;
    QSplitter* top_splitter;
    QLabel* live_time_reader;
    QLabel* total_time_reader;
    video_player_slider* time_slider;
    vector<video_item*> playlist;
    int current_index;
    QWidget* get_control_UI();
    QWidget* get_playlist_UI();
    bool toggle_play_pause();
    void handle_slider_move(int position);
    void update_slider();
    void handle_start_play(QListWidgetItem *item);
    bool start(std::string source, qint64 timestamp = 0);
    bool find_and_play(int index);
    void handle_play_next();
    void handle_play_prev();
    void update_time_display(bool duration_updated=false);
protected:
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;

public:
    video_player(QWidget *parent = nullptr);
    // bool add_video(std::string source, qint64 timestamp = 0);
    void add_new_source(string name, string path);
};

#endif // VIDEO_PLAYER_H
