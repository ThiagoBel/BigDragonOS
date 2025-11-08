#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <string>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <algorithm>
#include <cwctype>
using namespace std;

string notificationsfile = "notifications.txt";
string loadertemp = "loader_info_temp.txt";
string versionweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_version.txt";
string updatesnweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_updates.txt";
string docweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_doc.txt";
string usernameprofile = "";
string thisvers = "1.0";
string actualvers = "nl";
string theme = "0c";
string os = "";
bool canstart = false;

bool config_perm_1 = false;
bool config_perm_2 = false;
bool config_perm_3 = false;
bool profiled = false;

void asciicall()
{
    cout << " _____ _        ____                         _____ _____ \n";
    cout << "| __  |_|___   |    \\ ___ ___ ___ ___ ___   |     |   __|\n";
    cout << "| __ -| | . |  |  |  |  _| .'| . | . |   |  |  |  |__   |\n";
    cout << "|_____|_|_  |  |____/|_| |__,|_  |___|_|_|  |_____|_____|\n";
    cout << "        |___|                |___|                       \n";
}

void check_updates()
{
    system(("curl -s --ssl-no-revoke " + updatesnweb).c_str());
}

void check_doc()
{
    system(("curl -s --ssl-no-revoke " + docweb).c_str());
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

void send_notification(string const &msg)
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

void check_version(const bool &silenttt)
{
    system(("curl -s --ssl-no-revoke " + versionweb + " > " + loadertemp).c_str());
    ifstream lll(loadertemp);
    string ain;
    if (lll.is_open())
    {
        while (getline(lll, ain))
        {
            actualvers = ain;
            break;
        }
    }
    else
    {
        cout << "Erro\n";
    }

    if (silenttt == false)
    {
        if (thisvers == actualvers)
        {
            cout << "Seu sistema esta atualizado(" << actualvers << ")";
        }
        else
        {
            cout << "Seu sistema provalmente esta desatualizado\n\nSua versao: " << thisvers << "\nVersao oficial: " << actualvers;
        }
    }
}

void loadinfos()
{
    string username = "";

    string linha;
    ifstream pro("profile.txt");
    if (pro.is_open())
    {
        while (getline(pro, linha))
        {
            if (username == "")
            {
                username = linha;
            }
        }
    }
    usernameprofile = username;
}

void userinfos()
{
    string username = "";

    string linha;
    ifstream pro("profile.txt");
    if (pro.is_open())
    {
        while (getline(pro, linha))
        {
            if (username == "")
            {
                username = linha;
            }
        }
    }
    cout << "Username: " + username;
}

void verification_total()
{
    if (config_perm_1 == true && config_perm_2 == true && config_perm_3 == true && profiled == true)
    {
        canstart = true;
    }
    else
    {
        canstart = false;
    }

    if (config_perm_1 == false)
    {
        cout << "Sistema operacional nao permitido, use Windows\n";
    }
    if (config_perm_2 == false)
    {
        cout << "Erro na compilagem, abaixe o G++ (recomendado: MinGW)\n";
    }
    if (config_perm_3 == false)
    {
        cout << "Erro no curl, seu curl nao esta instalado\n";
    }
}

void carregarTema()
{
    ifstream file("theme.txt");
    if (file.is_open())
    {
        getline(file, theme);
        file.close();
    }
}

void carregamento()
{
    loadinfos();
    system("cls");
    system("color 05");
    cout << "Carregando...\n";
    Sleep(1300);
    system("cls");
    cout << "Ola " << usernameprofile << "!";
    Sleep(500);
    system(("color " + theme).c_str());
    system("cls");
}

void reopen(const int &ret)
{
    // system("start \"\" \"bdOS.exe\"");
    // exit(ret);

    carregarTema();
    system("cls");
    carregamento();
    asciicall();
    check_version(true);
}

void profile_config()
{
    string nameuser = "";
    cout << "Nome: ";
    getline(cin, nameuser);

    ofstream arrq("profile.txt");

    if (arrq.is_open())
    {
        arrq << nameuser << "\n";
        arrq.close();
        cout << "Reabrindo...";
        reopen(0);
    }
    else
    {
        cout << "Falha\n";
    }
}

void verification_os()
{
#ifdef _WIN32
    os = "Windows";
#elif defined(__linux__)
    os = "Linux";
#elif defined(__APPLE__)
    os = "MacOS";
#else
    os = "?";
#endif

    if (os != "Windows")
    {
        config_perm_1 = false;
    }
    else
    {
        system("title Big Dragon OS");
        config_perm_1 = true;
    }
}

void verification_compiler()
{
    int a = system("g++ --version >nul 2>&1");
    if (a == 0)
    {
        config_perm_2 = true;
    }
    else
    {
        config_perm_2 = false;
    }
}

void verification_profile()
{
    ifstream arq("profile.txt");
    string conteudo;

    if (arq.is_open())
    {
        getline(arq, conteudo);
        arq.close();

        if (conteudo.empty())
        {
            profiled = false;
            profile_config();
        }
        else
        {
            profiled = true;
            usernameprofile = conteudo;
        }
    }
    else
    {
        profiled = false;
        profile_config();
    }
}

void verification_curl()
{
    int curldetect = system("curl --version >nul");
    if (curldetect == 0)
    {
        config_perm_3 = true;
    }
    else
    {
        config_perm_3 = false;
    }
}

void executarComCancelamento(const string &exe)
{
    STARTUPINFOA si = {sizeof(STARTUPINFOA)};
    PROCESS_INFORMATION pi;

    if (CreateProcessA(
            NULL,
            (LPSTR)exe.c_str(),
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {

        while (true)
        {
            DWORD status;
            if (GetExitCodeProcess(pi.hProcess, &status) == 0 || status != STILL_ACTIVE)
                break;

            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                TerminateProcess(pi.hProcess, 0);
                break;
            }

            Sleep(100);
        }

        WaitForSingleObject(pi.hProcess, 500);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        Sleep(400);

        if (remove(exe.c_str()) == 0)
        {
            system("cls");
            system("title Big Dragon OS");
            Sleep(100);
            asciicall();
        }
        else
            cout << "Falha.\n";
    }
    else
    {
        cout << "Falha ao executar " << exe << "\n";
    }
}

void salvarTema()
{
    ofstream file("theme.txt");
    if (file.is_open())
    {
        file << theme;
        file.close();
    }
}

void listarArquivos(const string &pasta)
{
    string busca = pasta + "\\*";
    WIN32_FIND_DATAA arquivo;
    HANDLE hFind = FindFirstFileA(busca.c_str(), &arquivo);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Pasta corrompida ou inexistente\n";
        return;
    }

    do
    {
        string nome = arquivo.cFileName;
        if (nome == "." || nome == "..")
            continue;

        string caminhoCompleto = pasta + "\\" + nome;
        DWORD atributos = GetFileAttributesA(caminhoCompleto.c_str());

        if (atributos & FILE_ATTRIBUTE_DIRECTORY)
        {
            bool temCPP = false, temH = false;
            string subBusca = caminhoCompleto + "\\*";
            WIN32_FIND_DATAA subArquivo;
            HANDLE hSubFind = FindFirstFileA(subBusca.c_str(), &subArquivo);

            if (hSubFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    string subNome = subArquivo.cFileName;
                    if (subNome == "." || subNome == "..")
                        continue;

                    string ext = subNome.substr(subNome.find_last_of('.') + 1);
                    if (ext == "cpp")
                        temCPP = true;
                    else if (ext == "h")
                        temH = true;

                } while (FindNextFileA(hSubFind, &subArquivo));

                FindClose(hSubFind);
            }

            if (temCPP && temH)
                cout << " - " << nome << " [Biblioteca]\n";
            else
                cout << " - " << nome << " [Pasta]\n";
        }
        else
        {
            string ext = "";
            size_t pos = nome.find_last_of('.');
            if (pos != string::npos)
                ext = nome.substr(pos + 1);

            if (ext == "cpp")
                cout << " - " << nome.substr(0, pos) << " [Aplicativo]\n";
            else if (ext == "h")
                cout << " - " << nome.substr(0, pos) << " [Header]\n";
            else
                cout << " - " << nome << " [Arquivo]\n";
        }

    } while (FindNextFileA(hFind, &arquivo));

    FindClose(hFind);
}

string toLowerCase(const string &str)
{
    string lower = str;
    for (char &c : lower)
        c = tolower((unsigned char)c);
    return lower;
}

int main()
{
    HANDLE h = CreateMutexA(0, 1, "_BigDragonOS__bdOS__");

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return 0;
    }
    while (true)
    {
        verification_os();
        verification_compiler();
        verification_profile();
        verification_curl();
        verification_total();

        if (canstart == true)
        {
            carregarTema();
            system(("color " + theme).c_str());
            carregamento();
            asciicall();
            check_version(true);
            string comandoa;
            while (true)
            {
                cout << "\n->>";
                getline(cin, comandoa);
                string comando = toLowerCase(comandoa);

                if (comando == "exit" || comando == "close")
                {
                    break;
                }
                else if (comando == "show_apps")
                {
                    listarArquivos("apps");
                }
                else if (comando.rfind("open_apps ", 0) == 0)
                {
                    string app = comando.substr(10);
                    string caminho = "apps/" + app + ".cpp";
                    string exe = app + ".exe";
                    string cmdCompilar = "g++ " + caminho + " apps/lib/bdLIB.cpp -o " + exe;
                    int result = system(cmdCompilar.c_str());
                    if (result == 0)
                    {
                        executarComCancelamento(exe);
                        if (remove(exe.c_str()) == 0)
                        {
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                        cout << "Falha na compilação\n";
                    }
                }

                else if (comando.rfind("open_apps_lib ", 0) == 0)
                {
                    string app = comando.substr(14);
                    string caminho = "apps/" + app + ".cpp";
                    string exe = app + ".exe";
                    string lib;
                    cout << "Caminho da biblioteca: ";
                    getline(cin, lib);
                    string cmdCompilar = "g++ " + caminho + " apps/" + lib + " -o " + exe;
                    int result = system(cmdCompilar.c_str());

                    if (result == 0)
                    {
                        executarComCancelamento(exe);
                        if (remove(exe.c_str()) != 0)
                        {
                        }
                    }
                    else
                    {
                        cout << "Falha na compilação\n";
                    }
                }
                else if (comando == "reopen")
                {
                    reopen(0);
                }
                else if (comando == "version")
                {
                    cout << thisvers;
                }
                else if (comando.rfind("del_app ", 0) == 0)
                {
                    string appp = comando.substr(8);
                    string caminho = "apps/" + appp + ".cpp";
                    if (remove(caminho.c_str()) == 0)
                        cout << "Deletado\n";
                    else
                        cout << "Falha\n";
                }
                else if (comando.rfind("theme", 0) == 0)
                {
                    string tema = comando.substr(6);
                    if (tema == "classic")
                    {
                        theme = "0c";
                        system("color 0c");
                    }
                    else if (tema == "light")
                    {
                        theme = "70";
                        system("color 70");
                    }
                    else if (tema == "blue")
                    {
                        theme = "01";
                        system("color 01");
                    }
                    else if (tema == "cmd")
                    {
                        theme = "07";
                        system("color 07");
                    }
                    else if (tema == "hackerman")
                    {
                        theme = "0a";
                        system("color 0a");
                    }

                    else
                    {
                        cout << "Esse tema nao existe";
                        continue;
                    }

                    salvarTema();
                }
                else if (comando.rfind("c_theme", 0) == 0)
                {
                    string aaa = comando.substr(8);
                    theme = aaa;
                    system(("color " + aaa).c_str());
                    salvarTema();
                }
                else if (comando.rfind("say", 0) == 0)
                {
                    string msg = comando.substr(4);
                    cout << msg << endl;
                }
                else if (comando.rfind("test_apps", 0) == 0)
                {
                    string ap = comando.substr(10);
                    string caminho = "apps/" + ap + ".cpp";

                    struct stat info;
                    if (stat(caminho.c_str(), &info) != 0)
                    {
                        cout << "Erro\n";
                    }
                    else
                    {
                        cout << "Arquivo: " << caminho << "\n";
                        cout << "Tamanho: " << info.st_size << " bytes\n";
                        cout << "Permissoes: " << info.st_mode << "\n";
                    }
                }
                else if (comando == "clear" || comando == "cls")
                {
                    system("cls");
                    Sleep(100);
                    asciicall();
                }
                else if (comando == "user_info" || comando == "userinfo")
                {
                    userinfos();
                }
                else if (comando == "format_os")
                {
                    string vv = "";
                    cout << "Tem certeza que voce quer reiniciar seu sistema? Nao tera mais como voltar caso voce reiniciar, seus dados do sistema serao perdidos, os aplicativos ainda fica, menos os dados importantes, deseja reiniciar completamente? (Y/N): ";
                    getline(cin, vv);

                    if (vv == "Y" || vv == "y")
                    {
                        theme = "01";
                        carregarTema();
                        clear_notifications();
                        if (remove("profile.txt"))
                        {
                        }
                        system("cls");
                        verification_profile();
                        reopen(0);
                    }
                    else
                    {
                        cout << "Reinicializacao cancelada";
                    }
                }
                else if (comando == "check_version" || comando == "check_vers")
                {
                    check_version(false);
                }
                else if (comando == "check_updates")
                {
                    check_updates();
                }
                else if (comando == "check_doc" || comando == "check_docs" || comando == "help" || comando == "ajuda" || comando == "socorro")
                {
                    check_doc();
                }
                else if (comando == "check_notifications")
                {
                    check_notifications();
                }
                else if (comando == "clear_notifications")
                {
                    clear_notifications();
                }
                else if (comando == "check_variables" || comando == "check_var" || comando == "check_vars")
                {
                    cout << "config_perm_1: " << config_perm_1 << endl;
                    cout << "config_perm_2: " << config_perm_2 << endl;
                    cout << "config_perm_3: " << config_perm_3 << endl;
                    cout << "notificationsfile: " << notificationsfile << endl;
                    cout << "loadertemp: " << loadertemp << endl;
                    cout << "versionweb: " << versionweb << endl;
                    cout << "updatesnweb: " << updatesnweb << endl;
                    cout << "docweb: " << docweb << endl;
                    cout << "usernameprofile: " << usernameprofile << endl;
                    cout << "thisvers: " << thisvers << endl;
                    cout << "actualvers: " << actualvers << endl;
                    cout << "theme: " << theme << endl;
                    cout << "os: " << os << endl;
                    cout << "canstart: " << canstart << endl;
                    cout << "profiled: " << profiled << endl;
                }
                else
                {
                    cout << "Comando desconhecido\n";
                }
            }
        }
    }
    system("pause >nul");
    return 0;
}