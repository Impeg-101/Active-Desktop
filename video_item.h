#ifndef VIDEO_ITEM_H
#define VIDEO_ITEM_H
#include <string>
#include <chrono>
#include <QGridLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QObject>
#include <QTime>

using namespace::std;

class video_item : public QObject
{
private:
    int playlist_index;
    string name;
    string source;
    qint64 watch_position;
    std::chrono::system_clock::time_point last_visited;
public:
    video_item(string name = "", string source = "");

    std::string get_name() const;
    std::string get_source() const;
    qint64 get_watch_position() const;
    std::chrono::system_clock::time_point getLastVisited() const;
    int get_playlist_index();

    void set_name(const std::string& newName);
    void set_source(const std::string& newSource);
    void set_watch_position(const qint64 newWatchPosition);

    void set_playlist_index(int i);
};


#endif // VIDEO_ITEM_H
