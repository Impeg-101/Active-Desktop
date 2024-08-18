#include <iostream>
#include <QApplication>
#include <QTimer>
#include <QGridLayout>
#include <QThread>
#include <QFile>
#include <QPushButton>
#include <QScreen>
#include <QWidget>
#include <QVBoxLayout>
#include <libavutil/version.h>
#include <libavcodec/version.h>
#include <libavformat/version.h>
#include <libavdevice/version.h>
#include <libavfilter/version.h>
#include <libswscale/version.h>
#include <libswresample/version.h>
#include <libpostproc/version.h>
#include "video_player.h"
#include "tool_manager.h"
#include <QFontDatabase>
#include <QListWidget>
#include <QLabel>

using namespace std;

void load_style_sheet(QApplication &app, const QString &filepath) {
    QFile file(filepath);
    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QString style_sheet = stream.readAll();
        app.setStyleSheet(style_sheet);
    } else {
        throw invalid_argument("filepath given not found : " + filepath.toStdString());
    }
}

video_player* get_video_player_widget(QWidget* parent) {
    string source = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 01.mkv";
    string source1 = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 02.mkv";
    string source2 = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 03.mkv";
    string source3 = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 04.mkv";
    string source4 = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 05.mkv";
    string source5 = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 06.mkv";
    string source6 = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 07.mkv";
    string source7 = "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 08.mkv";
    video_player* video_player = new class video_player(parent);
    video_player->add_new_source("source", source);
    video_player->add_new_source("source1", source1);
    video_player->add_new_source("source2", source2);
    video_player->add_new_source("source3", source3);
    video_player->add_new_source("source4", source4);
    video_player->add_new_source("source5", source5);
    video_player->add_new_source("source6", source6);
    video_player->add_new_source("source7", source7);
    return video_player;
}

tool_manager* get_tool_manager_widget(QWidget* parent) {
    tool_manager* tool_manager = new class tool_manager(parent);
    return tool_manager;
}

int main(int argc, char *argv[]) {
    qputenv("QT_MEDIA_BACKEND", "ffmpeg");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");


    QApplication app(argc, argv);

    // QWidget window;
    // QVBoxLayout *layout = new QVBoxLayout(&window);

    // QListWidget *fontListWidget = new QListWidget(&window);
    // layout->addWidget(fontListWidget);

    // QStringList fontFamilies = QFontDatabase::families();

    // foreach (const QString &family, fontFamilies) {
    //     QListWidgetItem *item = new QListWidgetItem(family, fontListWidget);
    //     QFont font(family);
    //     font.setPointSize(16);  // Set a larger size for better visibility
    //     item->setFont(font);
    // }

    // window.setLayout(layout);
    // window.resize(400, 600);
    // window.setWindowTitle("Font Preview");
    // window.show();

    // return app.exec();

    // load_style_sheet(app, "C:/Users/IMPEG/Desktop/Qt projects/ActiveDesktop/style.qss");

    QWidget *window = new QWidget;
    QGridLayout *layout = new QGridLayout(window);


    // window.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);
    window->setWindowFlags(Qt::FramelessWindowHint);

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        qDebug() << "Desktop screen size:";
        qDebug() << "Width:" << screenGeometry.width();
        qDebug() << "Height:" << screenGeometry.height();
    } else {
        qDebug() << "No screen available.";
    }
    QRect availableGeometry = screen->availableGeometry(); // This excludes the taskbar
    window->setGeometry(availableGeometry);
    window->layout()->setContentsMargins(0, 0, 0, 0);

    // video_player *widget = get_video_player_widget(window);
    tool_manager *widget = get_tool_manager_widget(window);
    // QWidget *widget = get_tool_manager_widget(window;
    // QWidget *widget = get_tool_manager_widget(window);
    // QWidget *widget = get_tool_manager_widget(window);
    // QWidget *widget = get_tool_manager_widget(window);
    // QWidget *widget = get_tool_manager_widget(window);
    // QWidget *widget = get_tool_manager_widget(window);
    // QWidget *widget = get_tool_manager_widget(window);

    // layout->setRowStretch(0, 10);
    // layout->setColumnStretch(0, 10);
    // layout->addWidget(widget, 0, 0);

    window->setLayout(layout);
    window->layout()->addWidget(widget);
    window->show();

    widget->update_anchors();

    window->update();

    return app.exec();
}
