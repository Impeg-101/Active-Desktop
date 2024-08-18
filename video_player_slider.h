#ifndef VIDEO_PLAYER_SLIDER_H
#define VIDEO_PLAYER_SLIDER_H

#include <qlabel.h>
#include <qmediaplayer.h>
#include <qslider.h>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QTextEdit>


class video_player_slider : public QSlider
{
private:
    QMediaPlayer* media_player;
    void set_to_mouse_position(int mouse_position);
protected:
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *ev) override;
public:
    video_player_slider(QWidget *parent = nullptr);
    void set_media_player(QMediaPlayer* player);
public slots:
    void updatePosition(qint64 position);
    void setRange(qint64 min, qint64 max);
};

#endif // VIDEO_PLAYER_SLIDER_H
