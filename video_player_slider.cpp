#include "video_player_slider.h"

video_player_slider::video_player_slider(QWidget *parent)
    : QSlider(parent), media_player(nullptr) {
    // Optional: Initialize any custom properties or settings here
    setOrientation(Qt::Horizontal);
}

void video_player_slider::set_media_player(QMediaPlayer* player) {
    media_player = player;
}

void video_player_slider::updatePosition(qint64 position) {
    setSliderPosition(position);
}

void video_player_slider::setRange(qint64 min, qint64 max) {
    setMaximum(max);
    setMinimum(min);
}

void video_player_slider::set_to_mouse_position(int mouse_position){
    qDebug() << "current posttion" << media_player->position();
    int slider_lenth = mapToGlobal(rect().topRight()).x() - mapToGlobal(rect().topLeft()).x();

    int new_media_postion = (media_player->duration()*mouse_position)/slider_lenth;

    if(new_media_postion < 0){
        new_media_postion = 0;
    }else if(new_media_postion > media_player->duration()){
        new_media_postion = media_player->duration();
    }

    qDebug() << "moving media to" << new_media_postion/60000;
    media_player->setPosition(new_media_postion);
}

void video_player_slider::mouseMoveEvent(QMouseEvent *ev) {
    QSlider::mouseMoveEvent(ev);
    set_to_mouse_position(ev->pos().x());
}

void video_player_slider::mousePressEvent(QMouseEvent *ev) {
    QSlider::mousePressEvent(ev);
    media_player->pause();
    set_to_mouse_position(ev->pos().x());
}

void video_player_slider::mouseReleaseEvent(QMouseEvent *ev) {
    QSlider::mouseReleaseEvent(ev);
    set_to_mouse_position(ev->pos().x());
    media_player->play();
}

void video_player_slider::paintEvent(QPaintEvent *ev) {
    QSlider::paintEvent(ev); // Call base class implementation if needed

    // Custom painting code
    QPainter painter(this);
    painter.setPen(QPen(Qt::red)); // Example: set a red pen
    painter.drawRect(rect()); // Draw a border around the slider
}
