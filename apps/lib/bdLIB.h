#ifndef BDLIB_H
#define BDLIB_H

#include <windows.h>

namespace bd
{
    void set_title(const std::string& title);
    void set_theme(const std::string& theme);
    void set_theme_temp(const std::string &theme);
    void message(const std::string &title, const std::string &msg, UINT mode = MB_OK);
    void say(const std::string &msg);
    void pause();
    void check_notifications();
    void clear_notifications();
    void send_notification(const std::string &msg);
}

#endif
