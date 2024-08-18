#ifndef SPLITTER_ANCHOR_H
#define SPLITTER_ANCHOR_H

#include <QPushButton>
#include <qsplitter.h>

class splitter_anchor : public QPushButton
{
    Q_OBJECT
private:
    bool isDragging;
    QPointF dragStartPos;
    QSplitter* horizontal_splitter;
    int horizontal_splitter_handler_index;
    QSplitterHandle* horizontal_splitter_handler;
    QSplitter* verticle_splitter;
    int verticle_splitter_handler_index;
    QSplitterHandle* verticle_splitter_handler;
    QString default_style;
    QString clicked_style;
    void update_position(QMouseEvent *event);

    void update_splitter(QSplitter* splitter, int front_index, int back_index, int position);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void moved(const QPoint &diff);
public:
    splitter_anchor(QWidget *parent = nullptr);
    QSplitter* get_horizontal_splitter();
    QSplitter* get_verticle_splitter();
    QSplitterHandle* get_horizontal_splitter_handler();
    QSplitterHandle* get_verticle_splitter_handler();
    void set_horizontal_splitter(QSplitter* splitter, int handler_index, bool isMain=false);
    void set_verticle_splitter(QSplitter* splitter, int handler_index, bool isMain=false);
    void move_to_intersection();
};

#endif // SPLITTER_ANCHOR_H
