#include "splitter_anchor.h"
#include <qevent.h>

splitter_anchor::splitter_anchor(QWidget *parent)
    : QPushButton(parent), isDragging(false) {
    setFixedSize(20, 20);
    setStyleSheet(R"(
                QPushButton {
                    background-color: #a0c4ff;
                    border: 2px solid black;
                    border-radius: 10px;
                }
                QPushButton::hover {
                    background-color: #cde1ff;
                }
                QPushButton::pressed {
                    background-color: #a0c4ff;
                    border-radius: 25px;
                }
            )");
    setEnabled(true);
    raise();
    setWindowFlag(Qt::WindowStaysOnTopHint);
}

void splitter_anchor::mousePressEvent(QMouseEvent *event) {
    isDragging = true;
    setFixedSize(50, 50);
    update_position(event);
    QPushButton::mousePressEvent(event);
}

void splitter_anchor::mouseMoveEvent(QMouseEvent *event) {
    if(isDragging){
        update_position(event);
    }
    QPushButton::mouseMoveEvent(event);
}

void splitter_anchor::mouseReleaseEvent(QMouseEvent *event) {
    QPushButton::mouseReleaseEvent(event);
    isDragging = false;
    setFixedSize(20, 20);
    update_position(event);
    move_to_intersection();
}

// void moved(const QPoint &relativePos){

// }

void splitter_anchor::update_position(QMouseEvent *event){
    QPoint globalPos = event->globalPosition().toPoint();
    QPoint relativePos = parentWidget()->mapFromGlobal(globalPos);
    relativePos -= QPoint(width() / 2, height() / 2);
    // qDebug() << "Mouse position :" << event->globalPosition().toPoint();
    move(relativePos);
    emit moved(relativePos);
}

void splitter_anchor::move_to_intersection(){
    QSplitterHandle *horizontal_handle = get_horizontal_splitter_handler();
    int horizontal_coord = horizontal_handle->pos().x();

    QSplitterHandle *verticle_handle = get_verticle_splitter_handler();
    int verticle_coord = verticle_handle->pos().y();

    move(horizontal_coord, verticle_coord);
}

void splitter_anchor::update_splitter(QSplitter* splitter, int front_index, int back_index, int position_difference){
    QList<int> new_sizes = splitter->sizes();

    new_sizes[front_index] = splitter->sizes()[front_index] - position_difference;
    new_sizes[back_index] = splitter->sizes()[back_index] + position_difference;

    splitter->setSizes(new_sizes);
}

QSplitterHandle* splitter_anchor::get_horizontal_splitter_handler(){
    return horizontal_splitter_handler;
}
QSplitterHandle* splitter_anchor::get_verticle_splitter_handler(){
    return verticle_splitter_handler;
}
QSplitter* splitter_anchor::get_horizontal_splitter(){
    return horizontal_splitter;
}
QSplitter* splitter_anchor::get_verticle_splitter(){
    return verticle_splitter;
}
void splitter_anchor::set_horizontal_splitter(QSplitter* splitter, int index, bool isMain){
    horizontal_splitter = splitter;
    horizontal_splitter_handler = splitter->handle(index);
    connect(this, &splitter_anchor::moved, this, [this, splitter, index, isMain](){
        update_splitter(splitter, index-1, index, get_horizontal_splitter_handler()->pos().x() - pos().x());
        if(isMain) emit splitter->splitterMoved(get_horizontal_splitter_handler()->pos().x(), index);
    });
    connect(splitter, &QSplitter::splitterMoved, this, [this, splitter](){
        qDebug() << "Horizontal splitter moved";
        move_to_intersection();
    });
}
void splitter_anchor::set_verticle_splitter(QSplitter* splitter, int index, bool isMain){
    verticle_splitter = splitter;
    verticle_splitter_handler = splitter->handle(index);
    connect(this, &splitter_anchor::moved, this, [this, splitter, index, isMain](){
        update_splitter(splitter, index-1, index, get_verticle_splitter_handler()->pos().y() - pos().y());
        if(isMain)
            emit splitter->splitterMoved(get_verticle_splitter_handler()->pos().y(), index);
    });
    connect(splitter, &QSplitter::splitterMoved, this, [this, splitter](){
        qDebug() << "Verticle splitter moved";
        move_to_intersection();
    });
}


