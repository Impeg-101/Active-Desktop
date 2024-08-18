#ifndef TERMINAL_H
#define TERMINAL_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QProcess>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QRegularExpression>

class terminal : public QTextEdit
{
    Q_OBJECT
private:
    QString directory;
    QProcess *terminal_process;
    QString current_command;
    void display_output(const QString &text, const QColor &color = Qt::black);
    QString getLastLine();
    void moveCursorWithinLimits();
protected:
    // void changeEvent(QEvent *e) override;
    // void contextMenuEvent(QContextMenuEvent *event) override;
    // void dragEnterEvent(QDragEnterEvent *e) override;
    // void dragLeaveEvent(QDragLeaveEvent *e) override;
    // void dragMoveEvent(QDragMoveEvent *e) override;
    // void dropEvent(QDropEvent *e) override;
    // void focusInEvent(QFocusEvent *e) override;
    // bool focusNextPrevChild(bool next) override;
    // void focusOutEvent(QFocusEvent *e) override;
    // void inputMethodEvent(QInputMethodEvent *e) override;
    void extracted(QKeyEvent *&e);
    void keyPressEvent(QKeyEvent *e) override;
    // void keyReleaseEvent(QKeyEvent *e) override;
    // void mouseDoubleClickEvent(QMouseEvent *e) override;
    // void mouseMoveEvent(QMouseEvent *e) override;
    // void mousePressEvent(QMouseEvent *e) override;
    // void mouseReleaseEvent(QMouseEvent *e) override;
    // void paintEvent(QPaintEvent *event) override;
    // void resizeEvent(QResizeEvent *e) override;
    // void scrollContentsBy(int dx, int dy) override;
    // void showEvent(QShowEvent *event) override;
    // void wheelEvent(QWheelEvent *e) override;
public:
    explicit terminal(QWidget *parent = nullptr);

signals:
};

#endif // TERMINAL_H
