#include "video_player.h"

video_player::video_player(QWidget *parent)
    : QWidget(parent),
    media_player(new QMediaPlayer(this)),
    time_slider(new video_player_slider()),
    live_time_reader(new QLabel(this)),
    total_time_reader(new QLabel(this)) {
    qDebug() << "video player object created!";
    qDebug() << "video player object created!";

    /*
     * border: 2px solid #FFA07A;
     */

    QString videoPlayerStyleSheet = R"(
        QWidget#videoPlayer {
            background-color: #FFE5B4; /* Light orange background */
            border-radius: 8px;       /* Rounded corners */
        }

        QLabel {
            color: #333333;           /* Dark gray text color */
            font: bold 14px;          /* Font style for labels */
        }

        QPushButton {
            background-color: #FFA07A; /* Light coral background */
            color: white;              /* Button text color */
            border: 1px solid #FF8C00; /* Dark orange border */
            border-radius: 5px;
        }

        QPushButton:hover {
            background-color: #FFB07A; /* Slightly lighter orange on hover */
        }

        QPushButton:pressed {
            background-color: #FF7F50; /* Darker orange when pressed */
        }

        QSlider::groove:horizontal {
            background: #FFDAB9; /* Peach background for slider groove */
            height: 6px;
            border-radius: 3px;
        }

        QSlider::handle:horizontal {
            background: #FFA07A; /* Light coral handle */
            border: 1px solid #FF8C00;
            width: 12px;
            margin: -5px 0;
            border-radius: 6px;
        }

        QSlider::groove:horizontal:hover {
            background: #FFB07A; /* Lighter orange groove on hover */
        }

        QSlider::handle:horizontal:hover {
            background: #FF7F50; /* Darker handle on hover */
        }

        QProgressBar {
            background-color: #FFE4C4; /* Light peach background */
            border: 1px solid #FFA07A; /* Light coral border */
            border-radius: 5px;
            text-align: center;
            color: #333333;
        }

        QProgressBar::chunk {
            background-color: #FF8C00; /* Dark orange progress chunk */
            border-radius: 5px;
        }
    )";

    // this->(videoPlayerStyleSheet);


    this->setAcceptDrops(true);

    qDebug() << "Desktop screen size:";
    qDebug() << "Width:" << width();
    qDebug() << "Height:" << height();

    QGridLayout* widget_grid = new QGridLayout(this);

    QAudioOutput* audio_ouput = new QAudioOutput(this);
    display_player = new QVideoWidget(this);
    display_player->setAcceptDrops(true); // maybe a subclass for this one as well
    display_player->setMinimumSize(width()*0.2, height()*0.2);

    this->media_player = new QMediaPlayer(this);
    this->media_player->setVideoOutput(display_player);
    this->media_player->setAudioOutput(audio_ouput);

    top_splitter = new QSplitter(this);
    top_splitter->addWidget(get_playlist_UI());
    top_splitter->addWidget(display_player);

    top_splitter->setCollapsible(0, false);
    top_splitter->setCollapsible(1, false);

    QWidget* control = get_control_UI();
    control->setFixedHeight(70);
    control->setMinimumWidth(300);

    // QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    // splitter->addWidget(top_splitter);
    // splitter->addWidget(control);

    // splitter->setStretchFactor(0, 9);
    // splitter->setStretchFactor(1, 1);

    // splitter->setCollapsible(0, false);
    // splitter->setCollapsible(1, false);

    // widget_grid->addWidget(splitter);

    widget_grid->addWidget(top_splitter);
    widget_grid->addWidget(control);

    live_time_reader->setText("00:00:00");
    total_time_reader->setText("00:00:00");
    time_slider->set_media_player(media_player);

    connect(time_slider, &QSlider::sliderMoved, this, &video_player::handle_slider_move);

    QObject::connect(media_player, &QMediaPlayer::playbackStateChanged, media_player, [this](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            qDebug() << "Video playback finished. Unloading video.";
            media_player->stop();
            time_slider->updatePosition(0);
        }
        qDebug() << state;
    });

    QObject::connect(media_player, &QMediaPlayer::errorOccurred, media_player, [this](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << errorString;
        media_player->stop();
        time_slider->updatePosition(0);
    });

    QObject::connect(media_player, &QMediaPlayer::positionChanged, media_player, [this]() {
        // qDebug() << "Position" << media_player->position()/1000 << "/" << media_player->duration()/1000;
        time_slider->updatePosition(media_player->position());
        update_time_display();
    });

    add_new_source("Should i add directory navigation?","");
    add_new_source("Add a picture or a vid to display if the file format is wrong","");
    add_new_source("Add sound","");
    add_new_source("Add import path button or in menu","");
    add_new_source("Add zoom to full screen?","");
    add_new_source("Add play speed","");
    add_new_source("Add play mode : loop/random/ascended/descended","");
}

QWidget* video_player::get_control_UI(){


    this->toggle_play_button = new QPushButton("Play");
    connect(toggle_play_button, &QPushButton::clicked, this, &video_player::toggle_play_pause);
    // this->toggle_play_button->setDisabled(true);

    QPushButton* next_button = new QPushButton("next");
    connect(next_button, &QPushButton::clicked, this, &video_player::handle_play_next);
    next_button->setDisabled(true);

    QPushButton* prev_button = new QPushButton("previous");
    connect(prev_button, &QPushButton::clicked, this, &video_player::handle_play_prev);
    prev_button->setDisabled(true);

    QWidget* middle_containier = new QWidget;
    QGridLayout* middle_grid = new QGridLayout(middle_containier);
    middle_grid->addWidget(prev_button, 0,0);
    middle_grid->addWidget(toggle_play_button, 0,1);
    middle_grid->addWidget(next_button, 0,2);

    middle_grid->setAlignment(prev_button, Qt::AlignLeft);
    middle_grid->setAlignment(toggle_play_button, Qt::AlignCenter);
    middle_grid->setAlignment(next_button, Qt::AlignRight);

    QPushButton* more_options = new QPushButton("more");
    more_options->setDisabled(true);

    QPushButton* full_screen_button = new QPushButton("full");
    full_screen_button->setDisabled(true);

    QWidget* left_container = new QWidget;
    QGridLayout* left_grid = new QGridLayout(left_container);
    left_grid->addWidget(more_options, 0,0);
    left_grid->addWidget(full_screen_button, 0,1);

    QPushButton* toggle_playlist_button = new QPushButton("playlist");
    connect(toggle_playlist_button, &QPushButton::clicked, this, [this](){
        video_list->setHidden(!video_list->isHidden());
    });


    QWidget* widget = new QWidget;

    QGridLayout* time_display = new QGridLayout;
    QLabel* just_a_seperater = new QLabel(" / ");
    time_display->addWidget(this->live_time_reader, 0,0);
    time_display->addWidget(just_a_seperater, 0,1);
    time_display->addWidget(this->total_time_reader, 0,2);
    time_display->addWidget(this->time_slider, 0,3);

    QGridLayout* control_grid = new QGridLayout(widget);
    control_grid->addWidget(toggle_playlist_button,0,0);
    control_grid->addWidget(middle_containier,0,1);
    control_grid->addLayout(time_display,0,2);
    control_grid->addWidget(left_container,0,3);

    control_grid->setAlignment(toggle_playlist_button, Qt::AlignLeft);
    control_grid->setAlignment(middle_containier, Qt::AlignCenter);
    control_grid->setAlignment(time_display, Qt::AlignCenter);
    control_grid->setAlignment(left_container, Qt::AlignRight);

    return widget;
}

QWidget* video_player::get_playlist_UI(){
    // QWidget* playlist_widget = new QWidget;

    // QVBoxLayout* layout = new QVBoxLayout(playlist_widget);

    QFont font("Microsoft YaHei UI", 12);
    video_list = new QListWidget();
    video_list->setMaximumWidth(width());
    video_list->setFont(font);

    // int i = 0;
    // for(video_item* video: playlist){
    //     video->set_playlist_index(i);
    //     video_list->addItem(QString::fromStdString(std::to_string(i) + ". " + video->get_name()));
    // }

    // layout->addWidget(video_list);
    // playlist_widget->setLayout(layout);

    connect(video_list, &QListWidget::itemDoubleClicked, this, &video_player::handle_start_play);
    // connect(video_list, &QListWidget::itemEntered, this, &video_player::handle_start_play);

    return video_list;
}


/**
 * @brief Plays a video from a specified source starting at a given timestamp.
 *
 * @param source The local file path of the video as a string.
 * @param timestamp The start position in milliseconds (e.g., 15000 starts at 15 seconds).
 *
 * @return bool Returns `true` if playback is initiated successfully.
 */
bool video_player::start(string source, qint64 timestamp){
    if(!source.length() || timestamp < 0){
        return false;
    }

    media_player->setSource(QUrl::fromLocalFile(QString::fromStdString(source)));

    media_player->setPlaybackRate(1.0);
    media_player->audioOutput()->setVolume(0.2);
    media_player->setPosition(timestamp);
    media_player->play();

    QObject::connect(media_player, &QMediaPlayer::mediaStatusChanged, media_player, [this, timestamp](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::MediaStatus::LoadedMedia) {
            // media_player->setPosition(timestamp);
            time_slider->setRange(0, media_player->duration());
            time_slider->updatePosition(media_player->position());
            update_time_display(true);
            toggle_play_button->setText("Pause");
        }
        // if (status == QMediaPlayer::MediaStatus::BufferedMedia) {
        //     media_player->setPosition(timestamp);
        //     time_slider->setRange(0, media_player->duration());
        //     time_slider->updatePosition(timestamp);
        // }
        qDebug() << status;
    });

    return true;
}

bool video_player::find_and_play(int index){
    if(playlist.size() <= index || index < 0)
        return false;

    video_item* video = playlist[index];
    if(!start(video->get_source(), video->get_watch_position()))
        return false;
    current_index = index;
    qDebug() << "Playing video: " << video->get_name();
    return true;
}

bool video_player::toggle_play_pause(){

    if(media_player->isPlaying()){
        media_player->pause();
        this->toggle_play_button->setText("Play");
        return true;
    }

    if(media_player->hasVideo()){
        media_player->play();
        this->toggle_play_button->setText("Pause");
        return true;
    }
    // handle no video playing
    // call start() to start playing video

    return find_and_play(0);
}

void video_player::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void video_player::dropEvent(QDropEvent *event){
    qDebug() << "\ndropped";
    QList<QUrl> urls = event->mimeData()->urls();

    if (urls.isEmpty())
        return;

    QString filePath = urls.first().toLocalFile();
    QFileInfo fileInfo(filePath);
    qDebug() << "\nfile path dropped : " << filePath;
    if(!fileInfo.isDir())
        return add_new_source(fileInfo.fileName().toStdString(), filePath.toStdString());

    QDir dir(filePath);
    QStringList filters;
    filters << "*";
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files | QDir::NoSymLinks);
    QStringList videoExtensions = {"mp4", "avi", "mov", "mkv", "flv", "wmv", "webm"};

    foreach (const QFileInfo &fileInfo, fileList) {
        if (videoExtensions.contains(QFileInfo(fileInfo.fileName()).suffix().toLower())) {
            add_new_source(fileInfo.fileName().toStdString(), fileInfo.absoluteFilePath().toStdString());
        }
    }
}

void video_player::handle_slider_move(int position) {
    qint64 newPosition = static_cast<qint64>(position) * media_player->duration() / time_slider->maximum();
    media_player->setPosition(newPosition);
}


void video_player::handle_start_play(QListWidgetItem *item) {
    QString text = item->text();
    QStringList parts = text.split('.');

    if (parts.size() > 0) {
        bool ok;
        int index = parts[0].toInt(&ok) - 1;

        if (!find_and_play(index)) {
            qDebug() << "Invalid index or index out of bounds : " << index;
        }
    } else {
        qDebug() << "Text does not contain the expected format : " << text;
    }
}

void video_player::add_new_source(string name, string path){
    video_item* video = new class video_item(name, path);
    playlist.push_back(video);
    video->set_playlist_index(playlist.size());
    video_list->addItem(QString::fromStdString(std::to_string(playlist.size()) + ". " + video->get_name()));
}

void video_player::handle_play_next(){
    find_and_play(current_index+1);
}

void video_player::handle_play_prev(){
    find_and_play(current_index-1);
}

void video_player::update_time_display(bool duration_updated){

    if(!media_player->hasVideo()){
        qDebug() << "update_time_display() failed : No video";
        return;
    }

    if(duration_updated){
        QTime time(0, 0);
        time = time.addSecs(media_player->duration()/1000);
        QString formattedTime = time.toString("hh:mm:ss");
        total_time_reader->setText(formattedTime);
    }

    QTime time(0, 0);
    time = time.addSecs(media_player->position()/1000);
    QString formattedTime = time.toString("hh:mm:ss");
    live_time_reader->setText(formattedTime);
}
