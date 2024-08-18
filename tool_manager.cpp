#include "tool_manager.h"
#include "splitter_anchor.h"
#include <qapplication.h>

tool_manager::tool_manager(QWidget *parent)
    : QWidget(parent){

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
    this->setFixedSize(parentWidget()->size());
    qDebug() << "tool manager screen size:";
    qDebug() << "Width:" << width();
    qDebug() << "Height:" << height();

    QGridLayout* layout = new QGridLayout(this);

    int minSize = 300;


    tool_seperator *splitter5 = new class tool_seperator(Qt::Horizontal, this);
    tool_seperator *splitter4 = new class tool_seperator(Qt::Vertical, this);
    tool_seperator *splitter3 = new class tool_seperator(Qt::Vertical, this);
    tool_seperator *splitter2 = new class tool_seperator(Qt::Horizontal, this);
    tool_seperator *splitter1 = new class tool_seperator(Qt::Horizontal, this);


    splitter1->addWidget(new QWidget);
    splitter1->addWidget(new QWidget);
    splitter1->addWidget(new QWidget);

    splitter2->addWidget(new QWidget);
    splitter2->addWidget(new QWidget);
    // splitter2->addWidget(new QWidget);

    splitter3->addWidget(new QWidget);
    splitter3->addWidget(new QWidget);
    splitter3->addWidget(new QWidget);

    splitter4->addWidget(splitter1);
    splitter4->addWidget(splitter2);

    splitter5->addWidget(splitter3);
    splitter5->addWidget(splitter4);

    tool_seperators.push_back(splitter1);
    tool_seperators.push_back(splitter2);
    tool_seperators.push_back(splitter3);
    tool_seperators.push_back(splitter4);
    tool_seperators.push_back(splitter5);

    for(tool_seperator* seperator : tool_seperators){
        for(int i=0; i < seperator->count(); i++){
            seperator->setCollapsible(i, false);
            // seperator->setStretchFactor(i, 1);
        }
    }

    main_tool = splitter5;

    layout->addWidget(splitter5, 0,0);
    setLayout(layout);

    // QObject::connect(splitter34, &QSplitter::splitterMoved, splitter34,
    //                  [this, splitter12, splitter34]() {
    //     splitter12->setSizes(splitter34->sizes());
    // });
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
                splitter_anchor* sa = new class splitter_anchor(this);

                if(seperator->orientation() == Qt::Horizontal){
                    sa->set_horizontal_splitter(seperator, i,  true);
                    sa->set_verticle_splitter(nestedSplitter, j);
                }else{
                    sa->set_horizontal_splitter(nestedSplitter, j);
                    sa->set_verticle_splitter(seperator, i,  true);
                }
                sa->show();
                sa->move_to_intersection();
            }

            // connect to the handle where handle index < splitter index
            for(int j=1; j<nestedSplitter->count() && i < seperator->count()-1; j++){
                splitter_anchor* sa = new class splitter_anchor(this);

                if(seperator->orientation() == Qt::Horizontal){
                    sa->set_horizontal_splitter(seperator, i+1,  true);
                    sa->set_verticle_splitter(nestedSplitter, j);
                }else{
                    sa->set_horizontal_splitter(nestedSplitter, j);
                    sa->set_verticle_splitter(seperator, i+1,  true);
                }
                sa->show();
                sa->move_to_intersection();
            }
        }
    }
}










