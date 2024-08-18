#include "terminal.h"

static const QRegularExpression whitespaceRegex("\\s+");
static const QRegularExpression matchRightPointer(">(?!.*>)");

terminal::terminal(QWidget *parent)
    : QTextEdit{parent},
    terminal_process(new QProcess(this))
{

    display_output(
        "tool manager"
        "\n   - think of a snapping/unsnapping of splitters logic"
        "\n   - change style layout"
        "\n   - set a limit to number of tabs"
        "\n   - add a taskbar or a floatig button for more tab views"
        "\n   - add new tool window"
        "\n   - "
        "\n   - "
        "\n--------------------------------------------------------------------------------"
        "\n- video player"
        "\n   - fix playback pitch changing"
        "\n   - volumn, full screen"
        "\n   - play prev and next fix"
        "\n   - drop/import folder/files, also show where to drop"
        "\n   - NEVER ALLOW NON VIDEO FILES! ALWAYS DELETE THEM!"
        "\n   - add a unsupported page"
        "\n   - pop out option + keyboard shortcut for show/hide the pop out"
        "\n   - add show/hide control bar logic"
        "\n   - "
        "\n   - "
        "\n--------------------------------------------------------------------------------"
        "\nterminal"
        "\n   - Handle different modified inputs"
        "\n   - change background color to black and text to green, error text remain red"
        "\n   - handle preset env, like python env (add prefix logic)"
        "\n   - copy and past, select all, and other keyboard shortcuts"
        "\n   - save a history of commands per session of main env"
        "\n   - load last session? either run again or just keep a history of past commands"
        "\n   - color text support"
        "\n--------------------------------------------------------------------------------"
        "\n "
        "\n   - "
        "\n   - "
        "\n   - "
        "\n   - "
        "\n   - "
        "\n   - "

        "\n- add a record file before closing for each of the tools"
        "\n- handle exits"
        "\n- performance optimization?"
        "\n- "
        , Qt::black);








    directory = "C:\\Users\\IMPEG";
    current_command = "";
    terminal_process->setWorkingDirectory(directory);
    // terminal_process->start("cmd.exe", QStringList() << "cd");
    display_output(directory+">", Qt::black);
    connect(terminal_process, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output = terminal_process->readAllStandardOutput();
        // terminal_process->kill();
        display_output(output, Qt::black);
    });

    connect(terminal_process, &QProcess::readyReadStandardError, this, [this]() {
        QString error = terminal_process->readAllStandardError();
        // terminal_process->kill();
        display_output(error, Qt::black);
    });

    connect(terminal_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [this](int exitCode, QProcess::ExitStatus exitStatus) {
        if (exitStatus == QProcess::CrashExit) {
            display_output(QString("Program crashed with exit code %1\n").arg(exitCode), Qt::red);
        } else if (exitCode != 0) {
            display_output(QString("Program exited with code %1\n").arg(exitCode), Qt::black);
        }
        terminal_process->kill();
        display_output(directory+">", Qt::black);
        current_command.clear();
    });

    // connect(terminal_process, &QProcess::stateChanged, this, [this](QProcess::ProcessState newState) {
    //     qDebug() << "new state" << newState;
    // });

    // connect(terminal_process, &QProcess::finished, this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
    //     qDebug() << "exit code:" << exitCode;
    //     qDebug() << "exit status:" << exitStatus;
    // });

    // connect(terminal_process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
    //     qDebug() << "error:" << error;
    // });

}

void terminal::extracted(QKeyEvent *&e) {
    QTextCursor cursor = textCursor();
    int key = e->key();

    if (e->modifiers() & Qt::ControlModifier && key == Qt::Key_A){
        qDebug() << "Ctrl + A pressed";
    }

    switch (key) {
        case Qt::Key_0: qDebug() << "Qt::Key_0"; break;
        case Qt::Key_1: qDebug() << "Qt::Key_1"; break;
        case Qt::Key_2: qDebug() << "Qt::Key_2"; break;
        case Qt::Key_3: qDebug() << "Qt::Key_3"; break;
        case Qt::Key_4: qDebug() << "Qt::Key_4"; break;
        case Qt::Key_5: qDebug() << "Qt::Key_5"; break;
        case Qt::Key_6: qDebug() << "Qt::Key_6"; break;
        case Qt::Key_7: qDebug() << "Qt::Key_7"; break;
        case Qt::Key_8: qDebug() << "Qt::Key_8"; break;
        case Qt::Key_9: qDebug() << "Qt::Key_9"; break;
        case Qt::Key_A: qDebug() << "Qt::Key_A"; break;
        case Qt::Key_B: qDebug() << "Qt::Key_B"; break;
        case Qt::Key_C: qDebug() << "Qt::Key_C"; break;
        case Qt::Key_D: qDebug() << "Qt::Key_D"; break;
        case Qt::Key_E: qDebug() << "Qt::Key_E"; break;
        case Qt::Key_F: qDebug() << "Qt::Key_F"; break;
        case Qt::Key_G: qDebug() << "Qt::Key_G"; break;
        case Qt::Key_H: qDebug() << "Qt::Key_H"; break;
        case Qt::Key_I: qDebug() << "Qt::Key_I"; break;
        case Qt::Key_J: qDebug() << "Qt::Key_J"; break;
        case Qt::Key_K: qDebug() << "Qt::Key_K"; break;
        case Qt::Key_L: qDebug() << "Qt::Key_L"; break;
        case Qt::Key_M: qDebug() << "Qt::Key_M"; break;
        case Qt::Key_N: qDebug() << "Qt::Key_N"; break;
        case Qt::Key_O: qDebug() << "Qt::Key_O"; break;
        case Qt::Key_P: qDebug() << "Qt::Key_P"; break;
        case Qt::Key_Q: qDebug() << "Qt::Key_Q"; break;
        case Qt::Key_R: qDebug() << "Qt::Key_R"; break;
        case Qt::Key_S: qDebug() << "Qt::Key_S"; break;
        case Qt::Key_T: qDebug() << "Qt::Key_T"; break;
        case Qt::Key_U: qDebug() << "Qt::Key_U"; break;
        case Qt::Key_V: qDebug() << "Qt::Key_V"; break;
        case Qt::Key_W: qDebug() << "Qt::Key_W"; break;
        case Qt::Key_X: qDebug() << "Qt::Key_X"; break;
        case Qt::Key_Y: qDebug() << "Qt::Key_Y"; break;
        case Qt::Key_Z: qDebug() << "Qt::Key_Z"; break;
        case Qt::Key_Alt: qDebug() << "Qt::Key_Alt"; break;
        case Qt::Key_AltGr: qDebug() << "Qt::Key_AltGr"; break;
        case Qt::Key_Backspace: qDebug() << "Qt::Key_Backspace"; break;
        case Qt::Key_CapsLock: qDebug() << "Qt::Key_CapsLock"; break;
        case Qt::Key_Control: qDebug() << "Qt::Key_Control"; break;
        case Qt::Key_Delete: qDebug() << "Qt::Key_Delete"; break;
        case Qt::Key_Enter: qDebug() << "Qt::Key_Enter"; break;
        case Qt::Key_Escape: qDebug() << "Qt::Key_Escape"; break;
        case Qt::Key_F1: qDebug() << "Qt::Key_F1"; break;
        case Qt::Key_F2: qDebug() << "Qt::Key_F2"; break;
        case Qt::Key_F3: qDebug() << "Qt::Key_F3"; break;
        case Qt::Key_F4: qDebug() << "Qt::Key_F4"; break;
        case Qt::Key_F5: qDebug() << "Qt::Key_F5"; break;
        case Qt::Key_F6: qDebug() << "Qt::Key_F6"; break;
        case Qt::Key_F7: qDebug() << "Qt::Key_F7"; break;
        case Qt::Key_F8: qDebug() << "Qt::Key_F8"; break;
        case Qt::Key_F9: qDebug() << "Qt::Key_F9"; break;
        case Qt::Key_F10: qDebug() << "Qt::Key_F10"; break;
        case Qt::Key_F11: qDebug() << "Qt::Key_F11"; break;
        case Qt::Key_F12: qDebug() << "Qt::Key_F12"; break;
        case Qt::Key_F13: qDebug() << "Qt::Key_F13"; break;
        case Qt::Key_F14: qDebug() << "Qt::Key_F14"; break;
        case Qt::Key_F15: qDebug() << "Qt::Key_F15"; break;
        case Qt::Key_F16: qDebug() << "Qt::Key_F16"; break;
        case Qt::Key_F17: qDebug() << "Qt::Key_F17"; break;
        case Qt::Key_F18: qDebug() << "Qt::Key_F18"; break;
        case Qt::Key_F19: qDebug() << "Qt::Key_F19"; break;
        case Qt::Key_F20: qDebug() << "Qt::Key_F20"; break;
        case Qt::Key_F21: qDebug() << "Qt::Key_F21"; break;
        case Qt::Key_F22: qDebug() << "Qt::Key_F22"; break;
        case Qt::Key_F23: qDebug() << "Qt::Key_F23"; break;
        case Qt::Key_F24: qDebug() << "Qt::Key_F24"; break;
        case Qt::Key_Home: qDebug() << "Qt::Key_Home"; break;
        case Qt::Key_Insert: qDebug() << "Qt::Key_Insert"; break;
        case Qt::Key_Left: qDebug() << "Qt::Key_Left"; break;
        case Qt::Key_MediaNext: qDebug() << "Qt::Key_MediaNext"; break;
        case Qt::Key_MediaPlay: qDebug() << "Qt::Key_MediaPlay"; break;
        case Qt::Key_MediaPrevious: qDebug() << "Qt::Key_MediaPrevious"; break;
        case Qt::Key_Menu: qDebug() << "Qt::Key_Menu"; break;
        case Qt::Key_Meta: qDebug() << "Qt::Key_Meta"; break;
        case Qt::Key_NumLock: qDebug() << "Qt::Key_NumLock"; break;
        case Qt::Key_PageDown: qDebug() << "Qt::Key_PageDown"; break;
        case Qt::Key_PageUp: qDebug() << "Qt::Key_PageUp"; break;
        case Qt::Key_Pause: qDebug() << "Qt::Key_Pause"; break;
        case Qt::Key_Print: qDebug() << "Qt::Key_Print"; break;
        case Qt::Key_Right: qDebug() << "Qt::Key_Right"; break;
        case Qt::Key_Shift: qDebug() << "Qt::Key_Shift"; break;
        case Qt::Key_Space: qDebug() << "Qt::Key_Space"; break;
        case Qt::Key_Tab: qDebug() << "Qt::Key_Tab"; break;
        case Qt::Key_Up: qDebug() << "Qt::Key_Up"; break;
        // case Qt::Key_WindowsLeft: qDebug() << "Qt::Key_WindowsLeft"; break;
        // case Qt::Key_WindowsRight: qDebug() << "Qt::Key_WindowsRight"; break;
        case Qt::Key_Backtab: qDebug() << "Qt::Key_Backtab"; break;
        case Qt::Key_Super_L: qDebug() << "Qt::Key_Super_L"; break;
        case Qt::Key_Super_R: qDebug() << "Qt::Key_Super_R"; break;
        // Add other keys as necessary
        default: qDebug() << "Other key or unknown key";
    }

    switch(key){
    case Qt::Key_Return:
    case Qt::Key_Enter:
            // QString command = current_command;
            if (!current_command.trimmed().isEmpty()) {
                QStringList args = current_command.split(whitespaceRegex, Qt::SkipEmptyParts);
                QString program = args[0];
                args.pop_front();

                terminal_process->setWorkingDirectory(directory);
                terminal_process->setProgram(program);
                terminal_process->setArguments(args);

                // terminal_process->setProgram("python");
                // terminal_process->setArguments(QStringList() << "-c" << "print(\"Hello World\")");

                terminal_process->start();

                qDebug() << "Command :" << current_command;

            }else{
                display_output(directory+">", Qt::black);
            }
            // Clear the input field
            // setPlainText("");
            current_command.clear();
            break;
        case Qt::Key_Backspace:
            if(current_command.isEmpty()){
                return;
            }
            // Handle backspace
            current_command.chop(1);
            cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();
            setTextCursor(cursor);
            break;
        // Control, Shift, and Alt keys (modifiers)
        case Qt::Key_Control:
        case Qt::Key_Shift:
        case Qt::Key_Alt:
            // Usually, you would not handle these directly, but could be used in combination with other keys
            break;

            // Alphanumeric keys
        case Qt::Key_A:
        case Qt::Key_B:
        case Qt::Key_C:
        case Qt::Key_D:
        case Qt::Key_E:
        case Qt::Key_F:
        case Qt::Key_G:
        case Qt::Key_H:
        case Qt::Key_I:
        case Qt::Key_J:
        case Qt::Key_K:
        case Qt::Key_L:
        case Qt::Key_M:
        case Qt::Key_N:
        case Qt::Key_O:
        case Qt::Key_P:
        case Qt::Key_Q:
        case Qt::Key_R:
        case Qt::Key_S:
        case Qt::Key_T:
        case Qt::Key_U:
        case Qt::Key_V:
        case Qt::Key_W:
        case Qt::Key_X:
        case Qt::Key_Y:
        case Qt::Key_Z:
            if (e->text().length() > 0) {
                current_command += e->text();
                cursor.insertText(e->text());
                setTextCursor(cursor);
            }
            break;

            // Numeric keys (0-9)
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            if (e->text().length() > 0) {
                current_command += e->text();
                cursor.insertText(e->text());
                setTextCursor(cursor);
            }
            break;

            // Punctuation and special characters
        case Qt::Key_Exclam:
        case Qt::Key_QuoteDbl:
        case Qt::Key_NumberSign:
        case Qt::Key_Dollar:
        case Qt::Key_Percent:
        case Qt::Key_Ampersand:
        case Qt::Key_Apostrophe:
        case Qt::Key_ParenLeft:
        case Qt::Key_ParenRight:
        case Qt::Key_Asterisk:
        case Qt::Key_Plus:
        case Qt::Key_Comma:
        case Qt::Key_Minus:
        case Qt::Key_Period:
        case Qt::Key_Slash:
        case Qt::Key_Colon:
        case Qt::Key_Semicolon:
        case Qt::Key_Less:
        case Qt::Key_Equal:
        case Qt::Key_Greater:
        case Qt::Key_Question:
        case Qt::Key_At:
        case Qt::Key_BracketLeft:
        case Qt::Key_Backslash:
        case Qt::Key_BracketRight:
        case Qt::Key_AsciiCircum:
        case Qt::Key_Underscore:
        case Qt::Key_QuoteLeft:
        case Qt::Key_BraceLeft:
        case Qt::Key_Bar:
        case Qt::Key_BraceRight:
        case Qt::Key_AsciiTilde:
        case Qt::Key_Space:
            if (e->text().length() > 0) {
                current_command += e->text();
                cursor.insertText(e->text());
                setTextCursor(cursor);
            }
            break;

            // Handle other non-printable or special keys if needed
        default:
            // Do nothing for unhandled keys or provide custom logic
            break;
        // default:
        //     if (e->text().length() > 0) {
        //         current_command = current_command + e->text();
        //         cursor.insertText(e->text());
        //         setTextCursor(cursor);
        //     }
    }
    // if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
    //     // Execute command

    // }else if (e->key() == Qt::Key_Backspace) {

    // } else if (e->key() == Qt::Key_Tab) {
    // } else {
    //     // Handle other keys
    //     if (e->text().length() > 0 && e->text()[0].unicode() <= 0x7F) {
    //         current_command = current_command + e->text();
    //         cursor.insertText(e->text());
    //         setTextCursor(cursor);
    //     }
    // }
}

QString terminal::getLastLine() {
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);

    QString text = current_command;//cursor.selectedText();
    qDebug() << "getLastLine() text =" << text;
    QStringList parts = text.split(matchRightPointer, Qt::SkipEmptyParts);
    parts.pop_front();
    return parts.isEmpty() ? QString() : parts.last().trimmed();
}

// void terminal::moveCursorWithinLimits() {
//     QTextCursor cursor = textCursor();
//     cursor.movePosition(QTextCursor::Start);

//     // Move to the end of the last block
//     cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
//     setTextCursor(cursor);
// }


void terminal::keyPressEvent(QKeyEvent *e) {
    QWidget::keyPressEvent(e);
    extracted(e);
}

void terminal::display_output(const QString &text, const QColor &color) {
    qDebug() << "display_output(" << text << ")";

    QTextCharFormat format;
    format.setForeground(color);

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.setCharFormat(format);
    cursor.insertText("\n"+text);

    setTextCursor(cursor);
}
