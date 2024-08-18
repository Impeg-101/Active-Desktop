#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include <QWidget>
#include "tool_seperator.h"
#include "splitter_anchor.h"
#include "video_player.h"
#include "terminal.h"
#include <QGridLayout>

class tool_manager : public QWidget
{
private:
    std::vector<splitter_anchor> splitter_anchors;
    void updateWidgetMaxSizes(QSplitter *splitter);
    std::vector<QWidget*> open_space_queue;
    std::vector<tool_seperator*> tool_seperators;
    tool_seperator* main_tool;
public:
    tool_manager(QWidget *parent = nullptr);
    QWidget* get_UI();
    void add_tool(std::string tool_name);
    void delete_tool(std::string tool_name);
    void update_anchors();
};

#endif // TOOL_MANAGER_H
