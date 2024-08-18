#ifndef TOOL_SEPERATOR_H
#define TOOL_SEPERATOR_H

#include <QSplitter>

class tool_seperator : public QSplitter
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public:
    tool_seperator(Qt::Orientation orientation, QWidget *parent = nullptr);
};

#endif // TOOL_SEPERATOR_H
