#include "tool_seperator.h"
#include <qevent.h>

tool_seperator::tool_seperator(Qt::Orientation orientation, QWidget *parent)
    : QSplitter(orientation, parent) {

}

void tool_seperator::mousePressEvent(QMouseEvent *event){
    // QPoint pos = event->pos();
    /*Unsnapping logic:
     *  When ctrl + click on a splitter
     *      first check if the splitter's child are two widget or splitter
     *      if two widget then just  tell the other splitter to disconnect from this one
     *      if only one of them is splitter or widget, then this action cant be done?
     *          or maybe it can by redistributing the splitters again
     *              ? get the widget that is expanding from the splitter
     *              ? make a new splitter and put the one widget and the widget that is not expanding together into one splitter window
     *              ? then make that a side and the widget that is expanding on the other side
     *              ? then of course the diagonal half is changed
     *              ? but should i leave this to a button cuz there really is no resizing,
     *              ? rather it is ONLY redistributing
     *      if two are splitter then redistribute the splitters
     *          simply get the one widges from each of the splitter where they are on the same side
     *          and then group them together and do the same thing with the others
     *              ! But what if there is one splitter seperating two splitter
     *                  where one of them is seperating 3 windows and 2 windows?
     *                  How will it redistribute?
     *
     *
     */
}

void tool_seperator::mouseReleaseEvent(QMouseEvent *event){
    // QPoint pos = event->pos();
}
