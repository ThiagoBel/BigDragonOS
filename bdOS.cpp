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
#include <functional>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>

#include "storage/configs/_libs/icolor.hpp"
#include "storage/configs/_libs/MOPTS.h"
using namespace std;

string notificationsfile = "storage/configs/notifications.txt";
string historico_apps_vc = "storage/configs/historico_apps_vc.txt";
string loadertemp = "storage/configs/loader_info_temp.txt";
string senhakey = "storage/configs/key.txt";
string versionweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_version.txt";
string updatesnweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_updates.txt";
string docweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_doc.txt";
string usernameprofile = "";
string genderuser = "";
string SENHAFINAL = "";
bool entrada_pela_senha = false;
unsigned long long armazenamento_total_aplicativos_num = 0;
string armazenamento_total_aplicativos_str = "0 bytes";
string thisvers = "1.0";
string actualvers = "nl";
string theme = "0c";
string os = "";
bool canstart = false;

bool config_perm_1 = false;
bool config_perm_2 = false;
bool config_perm_3 = false;
bool profiled = false;

string getExeDir()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string path(buffer);
    return path.substr(0, path.find_last_of("\\/"));
}

void tocarSom(const char *relativo)
{
    string caminho = getExeDir() + "\\" + relativo;
    PlaySoundA(caminho.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void asciicall()
{
    cout << " _____ _        ____                         _____ _____ \n";
    cout << "| __  |_|___   |    \\ ___ ___ ___ ___ ___   |     |   __|\n";
    cout << "| __ -| | . |  |  |  |  _| .'| . | . |   |  |  |  |__   |\n";
    cout << "|_____|_|_  |  |____/|_| |__,|_  |___|_|_|  |_____|_____| Simulator\n";
    cout << "        |___|                |___|                       \n";
}

void gender_user(const string &classss)
{
    genderuser = classss;
}

string hashSenha(const string &senha)
{
    hash<string> hasher;
    size_t hashValue = hasher(senha);
    return to_string(hashValue);
}

void read_files(const string &filename)
{
    ifstream aart(filename);
    string linha;
    if (aart.is_open())
    {
        while (getline(aart, linha))
        {
            cout << linha << endl;
        }
        aart.close();
    }
    else
    {
        cout << "Erro\n";
    }
}

void clear_files(const string &filename)
{
    ofstream aarf(filename, ios::trunc);
    aarf.close();
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

void install_obj_curl(const string &link, const string &file)
{
    system(("curl -s --ssl-no-revoke " + link + " > " + file).c_str());
}

void send_historico_apps(const string &obj)
{
    ofstream aaa(historico_apps_vc);
    if (aaa.is_open())
    {
        aaa << obj << "\n";
        aaa.close();
    }
    else
    {
        cout << "Erro\n";
    }
}

void check_historico_apps()
{
    read_files(historico_apps_vc);
}

void clear_historico_apps()
{
    clear_files(historico_apps_vc);
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

unsigned long long calcularTamanhoPasta(const string &pasta)
{
    unsigned long long total = 0;

    string busca = pasta + "\\*";
    WIN32_FIND_DATAA dados;
    HANDLE hFind = FindFirstFileA(busca.c_str(), &dados);

    if (hFind == INVALID_HANDLE_VALUE)
        return 0;

    do
    {
        string nome = dados.cFileName;

        if (nome == "." || nome == "..")
            continue;

        string caminhoCompleto = pasta + "\\" + nome;

        if (dados.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            total += calcularTamanhoPasta(caminhoCompleto);
        }
        else
        {
            unsigned long long tamanho =
                (static_cast<unsigned long long>(dados.nFileSizeHigh) << 32) |
                dados.nFileSizeLow;

            total += tamanho;
        }

    } while (FindNextFileA(hFind, &dados));

    FindClose(hFind);
    return total;
}
void verificar_armazenamento()
{
    string pasta = "storage";
    string armazenamentot = "storage/configs/armazenamento_check.txt";

    unsigned long long total_bytes = calcularTamanhoPasta(pasta);

    armazenamento_total_aplicativos_num = total_bytes;
    armazenamento_total_aplicativos_str = to_string(total_bytes) + " bytes";

    ofstream saida(armazenamentot);
    if (saida.is_open())
    {
        saida << total_bytes;
        saida.close();
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
    string genero = "";

    string linha;
    ifstream pro("storage/configs/profile.txt");
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

    string linha2;
    ifstream gen("storage/configs/gender.txt");
    if (gen.is_open())
    {
        while (getline(gen, linha2))
        {
            if (genero == "")
            {
                genero = linha2;
            }
        }
    }
    usernameprofile = username;
    genderuser = genero;
}

void PRINT_SYS_BLUE(const string &msgsss)
{
    cout << icolor::blue() << msgsss << icolor::finished() << endl;
}

void PRINT_SYS_FATAL(const string &msgsss)
{
    cout << icolor::fatal() << msgsss << icolor::finished() << endl;
}

void PRINT_SYS_ERR(const string &msgsss)
{
    cout << icolor::error() << msgsss << icolor::finished() << endl;
}

void PRINT_SYS_YELLOW(const string &msgsss)
{
    cout << icolor::yellow() << msgsss << icolor::finished() << endl;
}

void PRINT_SYS_SUCESS(const string &msgsss)
{
    cout << icolor::sucess() << msgsss << icolor::finished() << endl;
}

void userinfos()
{
    string username = "";
    string genero = "";

    string linha;
    ifstream pro("storage/configs/profile.txt");
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

    string linha2;
    ifstream gen("storage/configs/gender.txt");
    if (gen.is_open())
    {
        while (getline(gen, linha2))
        {
            if (genero == "")
            {
                genero = linha2;
            }
        }
    }
    if (genero == "M")
    {
        genero = "Masculino";
    }
    else if (genero == "F")
    {
        genero = "Feminino";
    }
    else
    {
        genero = "Preferiu nao dizer";
    }
    cout << "Username: " + username << endl;
    cout << "Genero: " + genero << endl;
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
    ifstream file("storage/configs/theme.txt");
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
    Sleep(1000);
    system("cls");
    cout << "Ola " << usernameprofile << "!";
    Sleep(500);
    system(("color " + theme).c_str());
    system("cls");
    tocarSom("storage\\configs\\sounds\\intro.wav");
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
    system("title Big Dragon OS");
}

bool senha_loader()
{
    ifstream senhapraloadar(senhakey);
    string linha;
    string senhamesmo = "";
    if (senhapraloadar.is_open())
    {
        while (getline(senhapraloadar, linha))
        {
            senhamesmo = linha;
            break;
        }
        senhapraloadar.close();
        if (senhamesmo == "")
        {
            return false;
        }
        else
        {
            SENHAFINAL = senhamesmo;
            return true;
        }
    }
    else
    {
        return false;
    }
}

void profile_config()
{
    asciicall();
    string nameuser = "";
    cout << "Seja bem-vindo(a) ao BigDragonOS, um sistema operacional bem simples, antes de tudo, precisaremos de algumas informacoes." << endl;
    cout << "Crie um nome de usuario: ";
    getline(cin, nameuser);

    MOPTS::MenuOption gender_opt[] = {
        {"Masculino", "M", gender_user},
        {"Feminino", "F", gender_user},
        {"Prefiro nao dizer", "N", gender_user},
    };

    MOPTS::ShowMenu("Qual seu genero? (Mova com W/S e selecione com enter)", gender_opt, "> ", "");

    ofstream arrq("storage/configs/profile.txt");
    ofstream arrq2("storage/configs/gender.txt");

    if (arrq.is_open() && arrq2.is_open())
    {
        arrq << nameuser << "\n";
        arrq.close();
        arrq2 << genderuser << "\n";
        arrq2.close();
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
    ifstream arq("storage/configs/profile.txt");
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
    bool cancelado = false;

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD modoOriginal;
    GetConsoleMode(hInput, &modoOriginal);

    if (CreateProcessA(
            NULL,
            (LPSTR)exe.c_str(),
            NULL,
            NULL,
            TRUE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        while (true)
        {
            DWORD status;
            if (!GetExitCodeProcess(pi.hProcess, &status) || status != STILL_ACTIVE)
                break;

            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                TerminateProcess(pi.hProcess, 0);

                SetConsoleMode(hInput, modoOriginal);
                FlushConsoleInputBuffer(hInput);

                cancelado = true;
                break;
            }

            Sleep(100);
        }

        WaitForSingleObject(pi.hProcess, 500);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        system("title Big Dragon OS");
    }
    else
    {
        cout << "Falha\n";
    }
}

void salvarTema()
{
    ofstream file("storage/configs/theme.txt");
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

void criar_senha(const string &)
{
    string senha;
    cout << "Crie uma senha: ";
    getline(cin, senha);

    string senhaHash = hashSenha(senha);

    ofstream file(senhakey);
    if (file.is_open())
    {
        file << senhaHash;
        file.close();
        PRINT_SYS_SUCESS("Senha criada com sucesso!");
        Sleep(250);
        system("cls");
        asciicall();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao criar senha");
    }
}

void del_senha(string const &senha)
{
    ofstream senhapracriararq(senhakey);
    if (senhapracriararq.is_open())
    {
        senhapracriararq << "";
        senhapracriararq.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao deletar senha");
    }
}

void security_aba(const string &what)
{
    if (what == "senhas")
    {
        MOPTS::MenuOption senhasa[] = {
            {"Criar senha", "criar", criar_senha},
            {"Remover senhas", "del", del_senha},
        };

        MOPTS::ShowMenu("Escolha uma opcao:", senhasa, "> ", "");
    }
    else
    {
    }
}

int main()
{
    HANDLE h = CreateMutexA(0, 1, "_BigDragonOS__bdOS__");
    MOPTS::color = false;
    MOPTS::all_color_line = false;
    MOPTS::clear_opts = false;
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
            while (true)
            {
                if (senha_loader() == true)
                {
                    string senhausadapraentrar = "";
                    cout << "Senha: ";
                    getline(cin, senhausadapraentrar);
                    if (hashSenha(senhausadapraentrar) != SENHAFINAL)
                    {
                        cout << "Senha incorreta, tente de novo!" << endl;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            carregarTema();
            system(("color " + theme).c_str());
            carregamento();
            asciicall();
            check_version(true);
            string comandoa;
            while (true)
            {
                verificar_armazenamento();
                cout << "\n->> ";
                getline(cin, comandoa);
                string comando = toLowerCase(comandoa);

                if (comando == "exit" || comando == "close")
                {
                    exit(0);
                    break;
                }
                else if (comando == "reload")
                {
                    break;
                }
                else if (comando == "show_apps")
                {
                    listarArquivos("storage/apps");
                }
                else if (comando.rfind("open_apps ", 0) == 0)
                {
                    string app = comando.substr(10);
                    string caminho = "storage/apps/" + app + ".cpp";
                    string exe = app + ".exe";
                    string cmdCompilar = "g++ " + caminho + " storage/apps/lib/bdLIB.cpp -o " + exe;
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
                        cout << "Falha na compilacao\n";
                    }
                }
                else if (comando.rfind("exec_apps ", 0) == 0)
                {
                    string app = comando.substr(10);
                    string caminho = "storage/apps/EXECUTER/" + app + ".exe";
                    executarComCancelamento(caminho);
                }

                else if (comando.rfind("open_apps_lib ", 0) == 0)
                {
                    string app = comando.substr(14);
                    string caminho = "storage/apps/" + app + ".cpp";
                    string exe = app + ".exe";
                    string lib;
                    cout << "Caminho da biblioteca: ";
                    getline(cin, lib);
                    string cmdCompilar = "g++ " + caminho + " storage/apps/" + lib + " -o " + exe;
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
                        cout << "Falha na compilacao\n";
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
                    string caminho = "storage/apps/" + appp + ".cpp";
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
                    string caminho = "storage/apps/" + ap + ".cpp";

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
                        PRINT_SYS_BLUE("Formatando...");
                        Sleep(100);
                        theme = "0c";
                        PRINT_SYS_BLUE("Definindo temas...");
                        Sleep(100);
                        salvarTema();
                        PRINT_SYS_BLUE("Salvando temas definidos...");
                        Sleep(100);
                        clear_notifications();
                        PRINT_SYS_BLUE("Limpando notificacoes...");
                        Sleep(100);
                        clear_historico_apps();
                        PRINT_SYS_BLUE("Limpando historicos...");
                        Sleep(100);
                        if (remove("storage/configs/profile.txt"))
                        {
                            PRINT_SYS_BLUE("Limpando perfil...");
                            Sleep(100);
                        }
                        if (remove("storage/configs/gender.txt"))
                        {
                            PRINT_SYS_BLUE("Limpando genero...");
                            Sleep(100);
                        }
                        if (remove("storage/configs/key.txt"))
                        {
                            PRINT_SYS_BLUE("Limpando senhas...");
                            Sleep(100);
                        }
                        PRINT_SYS_BLUE("Limpando tela...");
                        Sleep(100);
                        PRINT_SYS_BLUE("Verificando perfil...");
                        Sleep(100);
                        PRINT_SYS_SUCESS("SUCESSO!!!");
                        Sleep(100);
                        PRINT_SYS_SUCESS("Reiniciando...");
                        Sleep(50);
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
                    cout << "historico_apps_vc: " << historico_apps_vc << endl;
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
                    cout << "armazenamento_total_aplicativos_num: " << armazenamento_total_aplicativos_num << endl;
                    cout << "armazenamento_total_aplicativos_str: " << armazenamento_total_aplicativos_str << endl;
                }
                else if (comando.rfind("down_app", 0) == 0)
                {
                    string link = comando.substr(9);

                    link.erase(0, link.find_first_not_of(" "));

                    size_t pos = link.find_last_of('/');
                    if (pos == string::npos)
                    {
                        cout << "Link invalido\n";
                        continue;
                    }

                    string filename = link.substr(pos + 1);
                    string path = "storage/apps/" + filename;

                    install_obj_curl(link, path);
                    send_historico_apps(filename + " -> " + link);
                    cout << filename << " abaixado com sucesso" << endl;
                }
                else if (comando == "check_history" || comando == "check_historico")
                {
                    check_historico_apps();
                }
                else if (comando == "clear_history" || comando == "clear_historico" || comando == "cls_historico" || comando == "cls_history")
                {
                    clear_historico_apps();
                }
                else if (comando == "check_storage" || comando == "check_armazenamento")
                {
                    verificar_armazenamento();
                    cout << armazenamento_total_aplicativos_str << "\n";
                }
                else if (comando == "security")
                {
                    MOPTS::MenuOption security_opts[] = {
                        {"Senhas", "senhas", security_aba},
                        {"Voltar", "voltar", security_aba},
                    };
                    MOPTS::ShowMenu("Configuracoes de seguranca", security_opts, "> ", "");
                }
                else if (comando == "system_info" || comando == "sys_info")
                {
                    cout << "OS: BigDragonOS" << endl;
                    cout << "Storage: " << armazenamento_total_aplicativos_str << endl;
                    cout << "Theme: " << theme << endl;
                    cout << "User: " << usernameprofile << endl;
                    cout << "Gender: " << genderuser << endl;
                    cout << "Actual version: " << thisvers << endl;
                    cout << "This version: " << actualvers << endl;
                }
                else if (comando == "beep")
                {
                    tocarSom("storage\\configs\\sounds\\beep.wav");
                }
                else
                {
                    cout << "Comando desconhecido\n";
                }
                tocarSom("storage\\configs\\sounds\\pop.wav");
            }
        }
    }
    system("pause >nul");
    return 0;
}