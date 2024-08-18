#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
#include <QFile>
#include "video_item.h"

video_item::video_item(string name, string source){
    QFile file(QString::fromStdString(source));

    // if(!file.exists()){
    //     return; //throw std::runtime_error("File does not exist: " + source);
    // }else if(name.length() == 0){
    //     return;// throw std::runtime_error("Please input a valid name.");
    // }

    this->playlist_index = -1;
    this->name = name;
    this->source = source;
    this->watch_position = 0;

}

std::string video_item::get_name() const {
    return name;
}

std::string video_item::get_source() const {
    return source;
}

qint64 video_item::get_watch_position() const {
    return watch_position;
}

std::chrono::system_clock::time_point video_item::getLastVisited() const {
    return last_visited;
}

int video_item::get_playlist_index() {
    return playlist_index;
}

void video_item::set_name(const std::string& newName) {
    name = newName;
}

void video_item::set_source(const std::string& newSource) {
    source = newSource;
}

void video_item::set_watch_position(const qint64 newWatchPosition) {
    watch_position = newWatchPosition;
    last_visited = chrono::system_clock::now();
}

void video_item::set_playlist_index(int i) {
    playlist_index = i;
}
