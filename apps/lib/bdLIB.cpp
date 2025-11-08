#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

namespace bd
{
    string notificationsfile = "notifications.txt";
    void set_title(const string &title)
    {
        system(("title Big Dragon OS - " + title).c_str());
    }
    void set_theme(const string &theme)
    {
        ofstream aa("theme.txt");
        if (aa.is_open())
        {
            system(("color " + theme).c_str());
            aa << theme;
            aa.close();
        }
        else
        {
            cout << "erro";
        }
    }
    void set_theme_temp(const string &theme)
    {
        ofstream aa("theme.txt");
    }
    void message(const string &title, const string &msg, UINT mode = MB_OK)
    {
        MessageBoxA(NULL, msg.c_str(), title.c_str(), mode);
    }
    void say(const string &msg)
    {
        cout << msg << endl;
    }
    void pause()
    {
        system("pause");
    }
    void check_notifications()
    {
        string linha;
        ifstream arrr(notificationsfile);

        if (arrr.is_open())
        {
            while (getline(arrr, linha))
            {
                cout << linha << endl;
            }
            arrr.close();
        }
        else
        {
            cout << "Erro\n";
        }
    }

    void clear_notifications()
    {
        ofstream arrr(notificationsfile);
        if (arrr.is_open())
        {
            arrr << "";
            arrr.close();
        }
        else
        {
            cout << "Erro\n";
        }
    }

    void send_notification(const string &msg)
    {
        ofstream arrr(notificationsfile);
        if (arrr.is_open())
        {
            arrr << msg << "\n";
            arrr.close();
        }
        else
        {
            cout << "Erro\n";
        }
    }
};