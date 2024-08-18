#include "tool_manager.h"
#include "splitter_anchor.h"
#include <qapplication.h>

tool_manager::tool_manager(QWidget *parent)
    : QWidget(parent){

    QString orangeStyle = R"(
        QWidget {
            background-color: #FFA500; /* Orange background */
            border: 2px solid #FF8C00; /* Darker orange border */
        }

        QLabel {
            color: white;             /* Text color */
            font: bold 14px;          /* Font style */
        }

        QPushButton {
            background-color: #FF8C00; /* Button background */
            color: white;              /* Button text color */
            border: 2px solid #FF7F50; /* Slightly lighter border */
            border-radius: 5px;
        }

        QPushButton:hover {
            background-color: #FF7F50; /* Lighter orange on hover */
        }

        QPushButton:pressed {
            background-color: #FF4500; /* Even darker when pressed */
        }
    )";

    QString splitterStyle = R"(
        QSplitter::handle {
            background-color: black; /* Set the handle color to black */
        }

        QSplitter::handle:horizontal {
            height: 2px; /* Adjust thickness for horizontal splitters */
        }

        QSplitter::handle:vertical {
            width: 2px; /* Adjust thickness for vertical splitters */
        }
    )";

    this->setStyleSheet(splitterStyle);


    // this->setFixedSize(500, 500);
    this->setMinimumSize(parentWidget()->size());
    qDebug() << "Desktop screen size:";
    qDebug() << "Width:" << width();
    qDebug() << "Height:" << height();

    QGridLayout* layout = new QGridLayout(this);

    video_player* tool1 = new class video_player;
    video_player* tool2 = new class video_player;
    video_player* tool3 = new class video_player;
    terminal* tool4 = new class terminal;

    tool1->add_new_source("source", "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 01.mkv");
    tool2->add_new_source("source", "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 02.mkv");
    tool3->add_new_source("source", "C:/Users/IMPEG/Videos/anime downloads/dangers in my heart/Boku no Kokoro no Yabai Yatsu - 03.mkv");

    // tool1->setStyleSheet("background-color: blue; border: 1px solid black;");
    // tool2->setStyleSheet("background-color: red; border: 1px solid black;");
    // tool3->setStyleSheet("background-color: green; border: 1px solid black;");
    // tool4->setStyleSheet("background-color: yellow; border: 1px solid black;");

    int minSize = 300;

    tool1->setMinimumSize(minSize, minSize);
    tool2->setMinimumSize(minSize, minSize);
    tool3->setMinimumSize(minSize, minSize);
    tool4->setMinimumSize(minSize, minSize);





    tool_seperator *splitter12 = new class tool_seperator(Qt::Horizontal, this);
    tool_seperator *splitter34 = new class tool_seperator(Qt::Horizontal, this);
    tool_seperator *splitter13 = new class tool_seperator(Qt::Vertical, this);

    splitter12->addWidget(tool1);
    splitter12->addWidget(tool2);
    splitter12->addWidget(tool3);
    // splitter34->addWidget(tool3);
    // splitter34->addWidget(tool4);
    splitter13->addWidget(splitter12);
    splitter13->addWidget(tool4);



    // tool1->setMaximumSize(parentWidget()->width()-minSize, parentWidget()->height()-minSize);
    // tool2->setMaximumSize(parentWidget()->width()-minSize, parentWidget()->height()-minSize);
    // tool3->setMaximumSize(parentWidget()->width()-minSize, parentWidget()->height()-minSize);
    // tool4->setMaximumSize(parentWidget()->width()-minSize, parentWidget()->height()-minSize);

    // splitter12->setStretchFactor(0, 1);
    // splitter12->setStretchFactor(1, 1);
    // splitter34->setStretchFactor(0, 1);
    // splitter34->setStretchFactor(1, 1);
    // splitter13->setStretchFactor(0, 1);
    // splitter13->setStretchFactor(1, 1);

    splitter12->setCollapsible(0, false);
    splitter12->setCollapsible(1, false);
    splitter34->setCollapsible(0, false);
    splitter34->setCollapsible(1, false);
    splitter13->setCollapsible(0, false);
    splitter13->setCollapsible(1, false);

    tool_seperators.push_back(splitter12);
    tool_seperators.push_back(splitter13);

    layout->addWidget(splitter13, 0,0);
    setLayout(layout);

    QObject::connect(splitter12, &QSplitter::splitterMoved, splitter12,
                     [this, splitter12, splitter34]() {
        // splitter34->setSizes(splitter12->sizes());
        // QSplitterHandle *handle12 = splitter12->handle(1);
        // QPoint handlePos12 = handle12->pos();
        // QPoint globalHandlePos12 = splitter12->mapToGlobal(handlePos12);

        // qDebug() << "splitter12 coords" << globalHandlePos12;
    });

    // QObject::connect(splitter34, &QSplitter::splitterMoved, splitter34,
    //                  [this, splitter12, splitter34]() {
    //     splitter12->setSizes(splitter34->sizes());
    // });



}

void tool_manager::updateWidgetMaxSizes(QSplitter *splitter) {
    qDebug() << "updateWidgetMaxSizes";
    QList<int> sizes = splitter->sizes();
    for(int i=0; i < sizes.length(); i++){
        if (QWidget *widget = splitter->widget(i)) {
            if (QSplitter *nestedSplitter = qobject_cast<QSplitter*>(widget)) {
                updateWidgetMaxSizes(nestedSplitter);
                continue;
            }

            int size = sizes[i];
            qDebug() << "sizes" << size;

            if(splitter->orientation() == Qt::Horizontal){
                widget->setMaximumSize(size, widget->maximumHeight());
            }else if(splitter->orientation() == Qt::Vertical){
                widget->setMaximumSize(widget->maximumWidth(), size);
            }
        }
    }
    qDebug() << "Done";
}

void tool_manager::update_anchors(){

    QApplication::processEvents();

    for(tool_seperator* seperator : tool_seperators){
        qDebug() << "total count in seperator" << seperator->count();
        for(int i=0; i < seperator->count(); i++){
            QSplitter *nestedSplitter = qobject_cast<QSplitter*>(seperator->widget(i));
            if(!nestedSplitter || seperator->orientation() == nestedSplitter->orientation())
                continue;
            qDebug() << "total count in nestedSplitter" << nestedSplitter->count();

            // connect to the handle where handle index > splitter index
            for(int j=1; j<nestedSplitter->count() && i > 0; j++){
                splitter_anchor* sa = new class splitter_anchor(this->parentWidget());

                if(seperator->orientation() == Qt::Horizontal){
                    sa->set_horizontal_splitter(seperator, i,  true);
                    sa->set_verticle_splitter(nestedSplitter, j);
                }else{
                    sa->set_horizontal_splitter(nestedSplitter, j);
                    sa->set_verticle_splitter(seperator, i,  true);
                }

                QSplitterHandle *horizontal_splitter_handle = sa->get_horizontal_splitter_handler();
                int horizontal_coord = horizontal_splitter_handle->pos().x();

                QSplitterHandle *verticle_splitter_handle = sa->get_verticle_splitter_handler();
                int verticle_coord = verticle_splitter_handle->pos().y();

                qDebug() << "horizontal_coord" << horizontal_coord;
                qDebug() << "verticle_coord" << verticle_coord;

                sa->move(horizontal_coord, verticle_coord);
                sa->show();
            }

            // connect to the handle where handle index < splitter index
            for(int j=1; j<nestedSplitter->count() && i < seperator->count()-1; j++){
                splitter_anchor* sa = new class splitter_anchor(this->parentWidget());

                if(seperator->orientation() == Qt::Horizontal){
                    sa->set_horizontal_splitter(seperator, i+1,  true);
                    sa->set_verticle_splitter(nestedSplitter, j);
                }else{
                    sa->set_horizontal_splitter(nestedSplitter, j);
                    sa->set_verticle_splitter(seperator, i+1,  true);
                }

                QSplitterHandle *horizontal_splitter_handle = sa->get_horizontal_splitter_handler();
                int horizontal_coord = horizontal_splitter_handle->pos().x();

                QSplitterHandle *verticle_splitter_handle = sa->get_verticle_splitter_handler();
                int verticle_coord = verticle_splitter_handle->pos().y();

                qDebug() << "horizontal_coord" << horizontal_coord;
                qDebug() << "verticle_coord" << verticle_coord;

                sa->move(horizontal_coord, verticle_coord);
                sa->show();
            }
        }
    }


    // splitter12->update();
    // splitter13->update();
    // splitter12->updateGeometry();
    // splitter13->updateGeometry();


    // sa1->move(splitter13->sizes()[0], splitter12->sizes()[0]);
}










