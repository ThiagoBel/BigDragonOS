/*
b                 d     OOOOOOOO   SSSSSSSSSSS
b                 d    O        O  S
b bbbbb     ddddd d    O        O  S
bb     b   d     dd    O        O  SSSSSSSSSSS
b      b   d      d    O        O            S
bbbbbbb     ddddddd     OOOOOOOO   SSSSSSSSSSS

Olá!
*/

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
#include <vector>
#include <cwctype>
#include <functional>
#include <ctime>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>

#include "storage/configs/_libs/icolor.hpp"
#include "storage/configs/_libs/MOPTS.h"
using namespace std;

string notificationsfile = "storage/configs/notifications.txt";
string historico_apps_vc = "storage/configs/historico_apps_vc.txt";
string outdated_apps_file = "storage/configs/outdated_apps.txt";
string loadertemp = "storage/configs/loader_info_temp.txt";
string mutexfile = "storage/configs/mutex.txt";
string sound_config = "storage/configs/sound.txt";
string senhakey = "storage/configs/key.txt";
string errors_log_file = "storage/configs/logs/errors.log";
string history_log_file = "storage/configs/logs/history.log";
string logsenabler = "storage/configs/logs.txt";
string versionweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_version.txt";
string updatesnweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_updates.txt";
string docweb = "https://raw.githubusercontent.com/ThiagoBel/versions_apps/refs/heads/main/bdos/bdos_doc.txt";
string usernameprofile = "";
string genderuser = "";
string SENHAFINAL = "";
string modengc = "sucess";

bool logs = true;
bool canpop = false;
bool outdated_apps = true;
bool mutex_avaliable = true;
bool sound_value = true;
bool entrada_pela_senha = false;
unsigned long long armazenamento_total_aplicativos_num = 0;
string armazenamento_total_aplicativos_str = "0 bytes";
string thisvers = "1.6";
string actualvers = "nl";
string os = "";
bool canstart = false;

bool config_perm_1 = false;
bool config_perm_2 = false;
bool config_perm_3 = false;
bool profiled = false;

string getDateTime()
{
    time_t now = time(nullptr);
    tm *t = localtime(&now);

    char buffer[32];
    sprintf(
        buffer,
        "%04d-%02d-%02d %02d:%02d:%02d",
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec);

    return string(buffer);
}
void PRINT_SYS_BLUE(const string &msgsss)
{
    cout << icolor::blue() << msgsss << icolor::finished() << endl;
}

void PRINT_SYS_FATAL(const string &msgsss)
{
    cout << icolor::fatal() << msgsss << icolor::finished() << endl;
    modengc = "error";
    if (logs == true)
    {
        ofstream logsERR(errors_log_file, ios::app);
        if (logsERR.is_open())
        {
            logsERR << "[ERROR] [" << getDateTime() << "] " << msgsss << "\n";
        }
        else
        {
            cout << icolor::fatal() << "Erro" << icolor::finished() << endl;
        }
    }
}

void PRINT_SYS_ERR(const string &msgsss)
{
    cout << icolor::error() << msgsss << icolor::finished() << endl;
    modengc = "error";
    if (logs == true)
    {
        ofstream logsERR(errors_log_file, ios::app);
        if (logsERR.is_open())
        {
            logsERR << "[ERROR] [" << getDateTime() << "] " << msgsss << "\n";
        }
        else
        {
            cout << icolor::fatal() << "Erro no print" << icolor::finished() << endl;
        }
    }
}

void PRINT_SYS_YELLOW(const string &msgsss)
{
    cout << icolor::yellow() << msgsss << icolor::finished() << endl;
}

void PRINT_SYS_SUCESS(const string &msgsss)
{
    cout << icolor::sucess() << msgsss << icolor::finished() << endl;
}

void CLEAR_LOGS_ERROR()
{
    ofstream logsERR(errors_log_file);
    if (logsERR.is_open())
    {
        logsERR << "";
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao limpar logs");
    }
}

void CLEAR_LOGS_HISTORY()
{
    ofstream logsHIS(history_log_file);
    if (logsHIS.is_open())
    {
        logsHIS << "";
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao limpar logs");
    }
}

vector<string> comandos_validos = {
    "exit", "close", "reload",
    "show_apps", "show_exec_apps",
    "open_apps", "exec_apps",
    "clear", "down_app",
    "user_info", "userinfo",
    "security",
    "check_version", "check_updates",
    "check_doc", "configs", "check_storage",
    "system_info", "beep"};

void clear_cmd()
{
    system("cls");
}

int levenshtein(const string &a, const string &b)
{
    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));

    for (size_t i = 0; i <= a.size(); i++)
        dp[i][0] = i;

    for (size_t j = 0; j <= b.size(); j++)
        dp[0][j] = j;

    for (size_t i = 1; i <= a.size(); i++)
    {
        for (size_t j = 1; j <= b.size(); j++)
        {
            int custo = (a[i - 1] == b[j - 1]) ? 0 : 1;
            dp[i][j] = min({dp[i - 1][j] + 1,
                            dp[i][j - 1] + 1,
                            dp[i - 1][j - 1] + custo});
        }
    }

    return dp[a.size()][b.size()];
}

string sugerir_comando(const string &digitado)
{
    int menor_dist = 999;
    string melhor = "";

    for (const string &cmd : comandos_validos)
    {
        int d = levenshtein(digitado, cmd);
        if (d < menor_dist)
        {
            menor_dist = d;
            melhor = cmd;
        }
    }

    if (menor_dist <= 3)
        return melhor;

    return "";
}

string getExeDir()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string path(buffer);
    return path.substr(0, path.find_last_of("\\/"));
}

void tocarSom(const char *relativo)
{
    if (sound_value == true)
    {
        string caminho = getExeDir() + "\\" + relativo;
        PlaySoundA(caminho.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
}

void asciicall()
{
    cout << icolor::green() << " _____ _        ____                         _____ _____ \n"
         << icolor::finished();
    cout << icolor::yellow() << "| __  |_|___   |    \\ ___ ___ ___ ___ ___   |     |   __| " << thisvers << "\n"
         << icolor::finished();
    cout << icolor::blue() << "| __ -| | . |  |  |  |  _| .'| . | . |   |  |  |  |__   |\n"
         << icolor::finished();
    cout << icolor::yellow() << "|_____|_|_  |  |____/|_| |__,|_  |___|_|_|  |_____|_____| Simulator\n"
         << icolor::finished();
    cout << icolor::green() << "        |___|                |___|                       \n"
         << icolor::finished();
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
            break;
        }
        aart.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao ler o arquivo");
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
            break;
        }
        arrr.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao verificar a notificação");
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
        PRINT_SYS_FATAL("Erro ao enviar notificação");
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
        PRINT_SYS_FATAL("Erro ao limpar notificações");
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
        PRINT_SYS_FATAL("Erro ao enviar notificações");
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
        lll.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao verificar versao");
    }

    if (silenttt == false)
    {
        if (thisvers == actualvers)
        {
            cout << "Seu sistema está atualizado(" << actualvers << ")";
        }
        else
        {
            cout << "Seu sistema provalmente está desatualizado\n\nSua versão: " << thisvers << "\nVersão oficial: " << actualvers;
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
            break;
        }
        pro.close();
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
            break;
        }
        gen.close();
    }
    usernameprofile = username;
    genderuser = genero;
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
        pro.close();
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
        gen.close();
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
        genero = "Preferiu não dizer";
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
        PRINT_SYS_FATAL("Sistema operacional não permitido, use Windows");
    }
    if (config_perm_2 == false)
    {
        PRINT_SYS_FATAL("Erro na compilagem, abaixe o G++ (recomendado: MinGW)");
    }
    if (config_perm_3 == false)
    {
        PRINT_SYS_FATAL("Erro no curl, seu curl não está instalado");
    }
}

void carregamento()
{
    loadinfos();
    clear_cmd();
    cout << "Carregando...\n";
    Sleep(1000);
    clear_cmd();
    cout << "Ola " << usernameprofile << "!";
    Sleep(500);
    clear_cmd();
    tocarSom("storage\\configs\\sounds\\intro.wav");
}

void reopen(const int &ret)
{
    // system("start \"\" \"bdOS.exe\"");
    // exit(ret);
    canpop = false;
    clear_cmd();
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
    cout << "Seja bem-vindo(a) ao BigDragonOS, um sistema operacional bem simples, antes de tudo, precisaremos de algumas informações." << endl;
    cout << "Crie um nome de usuario: ";
    getline(cin, nameuser);

    MOPTS::MenuOption gender_opt[] = {
        {"Masculino", "M", gender_user},
        {"Feminino", "F", gender_user},
        {"Prefiro não dizer", "N", gender_user},
    };

    MOPTS::ShowMenu("Qual seu gênero? (Mova com W/S e selecione com enter)", gender_opt, "> ", "");

    ofstream arrq("storage/configs/profile.txt");
    ofstream arrq2("storage/configs/gender.txt");

    if (arrq.is_open() && arrq2.is_open())
    {
        arrq << nameuser << "\n";
        arrq.close();
        arrq2 << genderuser << "\n";
        arrq2.close();
        cout << "Reabrindo...";
        // reopen(0);
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao abrir arquivo de perfil");
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

void put_volume_sound()
{
    ifstream coiso(sound_config);
    string linha;

    if (coiso.is_open())
    {
        while (getline(coiso, linha))
        {
            if (linha == "true")
            {
                sound_value = true;
            }
            if (linha == "false")
            {
                sound_value = false;
            }
            break;
        }
        coiso.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao mudar o volume");
    }
}

void set_sound(const string &value)
{
    if (value == "true")
    {
        sound_value = true;
    }
    else if (value == "false")
    {
        sound_value = false;
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao setar volume");
    }
    ofstream coiso(sound_config);

    if (coiso.is_open())
    {
        coiso << value;
        coiso.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao setar volume");
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
        PRINT_SYS_FATAL("Erro ao criar processo");
    }
}

void listarArquivos(const string &pasta)
{
    string busca = pasta + "\\*";
    WIN32_FIND_DATAA arquivo;
    HANDLE hFind = FindFirstFileA(busca.c_str(), &arquivo);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        PRINT_SYS_FATAL("Pasta corrompida ou inexistente.");
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
                    {
                        temCPP = true;
                    }
                    else if (ext == "h")
                    {
                        temH = true;
                    }

                } while (FindNextFileA(hSubFind, &subArquivo));

                FindClose(hSubFind);
            }

            if (temCPP && temH)
            {
                cout << " - " << nome << " [Biblioteca]\n";
            }
            else
            {
                cout << " - " << nome << " [Pasta]\n";
            }
        }
        else
        {
            string ext = "";
            size_t pos = nome.find_last_of('.');
            if (pos != string::npos)
                ext = nome.substr(pos + 1);

            if (ext == "cpp")
            {
                cout << " - " << nome.substr(0, pos) << " [Codigo-fonte do aplicativo]\n";
            }
            else if (ext == "h")
            {
                cout << " - " << nome.substr(0, pos) << " [Header]\n";
            }
            else if (ext == "hpp")
            {
                cout << " - " << nome.substr(0, pos) << " [Header]\n";
            }
            else if (ext == "exe")
            {
                cout << " - " << nome.substr(0, pos) << " [Aplicativo]\n";
            }
            else
            {
                cout << " - " << nome << " [Arquivo]\n";
            }
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
        clear_cmd();
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

void check_outdated_apps()
{
    ifstream oaf(outdated_apps_file);
    string linha;
    if (oaf.is_open())
    {
        while (getline(oaf, linha))
        {
            if (linha == "true")
            {
                outdated_apps = true;
            }
            if (linha == "false")
            {
                outdated_apps = false;
            }
            break;
        }
        oaf.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro verificar outdated apps");
    }
}

void ativar_outdated_apps(const string &baguilouco)
{
    ofstream oaf(outdated_apps_file);
    if (oaf.is_open())
    {
        oaf << baguilouco;
        if (baguilouco == "true")
        {
            outdated_apps = true;
        }
        if (baguilouco == "false")
        {
            outdated_apps = false;
        }
        oaf.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao ativar outdated apps");
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

        MOPTS::ShowMenu("Escolha uma opção:", senhasa, "> ", "");
    }
    else if (what == "outdated_apps")
    {
        MOPTS::MenuOption outdatedA[] = {
            {"Ativar outdated apps", "true", ativar_outdated_apps},
            {"Desativar outdated apps", "false", ativar_outdated_apps},
        };

        MOPTS::ShowMenu("Escolha uma opção:", outdatedA, "> ", "");
    }
    else
    {
    }
}

void check_mutex()
{
    ifstream muttt(mutexfile);
    string linha;
    if (muttt.is_open())
    {
        while (getline(muttt, linha))
        {
            if (linha == "true")
            {
                mutex_avaliable = true;
            }
            else if (linha == "false")
            {
                mutex_avaliable = false;
            }
            else
            {
                PRINT_SYS_FATAL("Erro ao verificar o mutex");
            }
            break;
        }
        muttt.close();
    }
}

void ativar_mutex(const string &clsss)
{
    ofstream muttt(mutexfile);
    if (muttt.is_open())
    {
        muttt << clsss;
        muttt.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro pra ativar o mutex");
    }
}

void check_logs()
{
    ifstream baguiloucodms(logsenabler);
    string linha;
    if (baguiloucodms.is_open())
    {
        while (getline(baguiloucodms, linha))
        {
            if (linha == "true")
            {
                logs = true;
            }
            else if (linha == "false")
            {
                logs = false;
            }
            else
            {
                logs = true;
                PRINT_SYS_FATAL("Erro ao verificar logs pois um sinal foi sinalizado errado");
            }
            break;
        }
        baguiloucodms.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao verificar as logs pois o arquivo não existe");
    }
}

void set_logs(const string &abca)
{
    ofstream baguiloucodms(logsenabler);
    if (baguiloucodms.is_open())
    {
        baguiloucodms << abca;
        if (abca == "true")
        {
            logs = true;
        }
        else if (abca == "false")
        {
            logs = false;
        }
        else
        {
            PRINT_SYS_FATAL("Erro ao setar logs pois um sinal foi sinalizado errado");
        }
        baguiloucodms.close();
    }
    else
    {
        PRINT_SYS_FATAL("Erro ao setar logs, o arquivo não existe");
    }
}

void configs_aba(const string &what)
{
    if (what == "mutex")
    {
        MOPTS::MenuOption MutexA[] = {
            {"Ativar Mutex", "true", ativar_mutex},
            {"Desativar Mutex", "false", ativar_mutex},
        };

        MOPTS::ShowMenu("Mutex", MutexA, "> ", "");
    }
    else if (what == "sounds")
    {
        MOPTS::MenuOption SoundsA[] = {
            {"Ativar sons", "true", set_sound},
            {"Desativar sons", "false", set_sound},
        };

        MOPTS::ShowMenu("Sons", SoundsA, "> ", "");
    }
    else if (what == "logs")
    {
        MOPTS::MenuOption SoundsA[] = {
            {"Ativar logs", "true", set_logs},
            {"Desativar logs", "false", set_logs},
        };

        MOPTS::ShowMenu("Logs", SoundsA, "> ", "");
    }
    else
    {
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    check_mutex();
    if (mutex_avaliable == true)
    {
        HANDLE h = CreateMutexA(0, 1, "_BigDragonOS__bdOS__");
    }
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
            check_logs();
            put_volume_sound();
            check_outdated_apps();
            while (true)
            {
                if (senha_loader() == true)
                {
                    string senhausadapraentrar = "";
                    cout << "Senha: ";
                    getline(cin, senhausadapraentrar);
                    if (hashSenha(senhausadapraentrar) != SENHAFINAL)
                    {
                        PRINT_SYS_FATAL("Senha incorreta, tente novamente!");
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
            carregamento();
            asciicall();
            check_version(true);
            string comandoa;
            while (true)
            {
                modengc = "sucess";
                verificar_armazenamento();
                cout << icolor::white() << "\n[" << icolor::finished() << icolor::gray_10() << "bdOS@" << usernameprofile << icolor::finished() << icolor::white() << "] " << icolor::finished() << "->> ";
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
                    if (outdated_apps == true)
                    {
                        PRINT_SYS_FATAL("'show_apps' está desatualizado, use 'show_exec_apps'");
                    }
                    else
                    {
                        listarArquivos("storage/apps");
                    }
                }
                else if (comando == "show_exec_apps")
                {
                    listarArquivos("storage/apps/EXECUTER");
                }
                else if (comando.rfind("open_apps ", 0) == 0)
                {
                    if (outdated_apps == true)
                    {
                        PRINT_SYS_FATAL("'open_apps' está desatualizado, use 'exec_apps'");
                    }
                    else
                    {
                        string app = comando.substr(10);
                        string caminho = "storage/apps/" + app + ".cpp";
                        string exe = app + ".exe";
                        string cmdCompilar = "g++ " + caminho + " -o " + exe;
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
                            PRINT_SYS_FATAL("Falha na compilação");
                        }
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
                    if (outdated_apps == true)
                    {
                        PRINT_SYS_BLUE("'open_apps_lib' está desatualizado, use 'exec_apps'");
                    }
                    else
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
                            PRINT_SYS_FATAL("Falha na compilação");
                        }
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
                        PRINT_SYS_FATAL("Erro ao deletar aplicativos");
                }
                else if (comando.rfind("del_exec_app ", 0) == 0)
                {
                    string appp = comando.substr(13);
                    string caminho = "storage/apps/EXECUTER/" + appp + ".exe";
                    if (remove(caminho.c_str()) == 0)
                    {
                        cout << "Deletado\n";
                    }
                    else
                    {
                        PRINT_SYS_FATAL("Erro ao deletar arquivos executores");
                    }
                }
                else if (comando.rfind("say", 0) == 0)
                {
                    string msg = comando.substr(4);
                    cout << msg << endl;
                }
                else if (comando.rfind("test_apps", 0) == 0)
                {
                    string ap = comando.substr(10);
                    string caminho = "storage/apps/EXECUTER/" + ap + ".exe";

                    struct stat info;
                    if (stat(caminho.c_str(), &info) != 0)
                    {
                        PRINT_SYS_FATAL("Erro, o caminho não existe");
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
                    clear_cmd();
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
                    cout << "Tem certeza que você quer reiniciar seu sistema? Não terá mais como voltar caso você reiniciar, seus dados do sistema serão perdidos, os aplicativos ainda fica, menos os dados importantes, deseja reiniciar completamente? (Y/N): ";
                    getline(cin, vv);

                    if (vv == "Y" || vv == "y")
                    {
                        int delaytime = 50;
                        canpop = false;
                        PRINT_SYS_BLUE("Formatando...");
                        Sleep(delaytime);
                        clear_notifications();
                        PRINT_SYS_BLUE("Limpando notificações...");
                        Sleep(delaytime);
                        set_sound("true");
                        PRINT_SYS_BLUE("Arrumando sons...");
                        Sleep(delaytime);
                        clear_historico_apps();
                        PRINT_SYS_BLUE("Limpando históricos...");
                        Sleep(delaytime);
                        CLEAR_LOGS_ERROR();
                        CLEAR_LOGS_HISTORY();
                        PRINT_SYS_BLUE("Limpando logs...");
                        Sleep(delaytime);
                        set_logs("true");
                        PRINT_SYS_BLUE("Limpando dados das logs...");
                        Sleep(delaytime);
                        ativar_mutex("true");
                        PRINT_SYS_BLUE("Arrumando mutex...");
                        Sleep(delaytime);
                        ativar_outdated_apps("true");
                        PRINT_SYS_BLUE("Arrumando outdated_apps...");
                        Sleep(delaytime);
                        if (remove("storage/configs/profile.txt"))
                        {
                            PRINT_SYS_BLUE("Limpando perfil...");
                            Sleep(delaytime);
                        }
                        if (remove("storage/configs/gender.txt"))
                        {
                            PRINT_SYS_BLUE("Limpando gênero...");
                            Sleep(delaytime);
                        }
                        if (remove("storage/configs/key.txt"))
                        {
                            PRINT_SYS_BLUE("Limpando senhas...");
                            Sleep(delaytime);
                        }

                        PRINT_SYS_BLUE("Limpando tela...");
                        Sleep(delaytime);
                        PRINT_SYS_BLUE("Verificando perfil...");
                        Sleep(delaytime);
                        PRINT_SYS_SUCESS("SUCESSO!!!");
                        Sleep(delaytime);
                        PRINT_SYS_SUCESS("Reiniciando...");
                        Sleep(delaytime / 2);
                        clear_cmd();
                        verification_profile();
                        reopen(0);
                    }
                    else
                    {
                        cout << "Reinicialização cancelada";
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
                        PRINT_SYS_FATAL("Link inválido");
                        continue;
                    }

                    string filename = link.substr(pos + 1);
                    string path = "storage/apps/EXECUTER/" + filename;

                    int r = system(("curl -s --ssl-no-revoke " + link + " > " + path).c_str());
                    if (r == 0)
                    {
                        send_historico_apps(filename + " -> " + link);
                        PRINT_SYS_SUCESS("Download concluído");
                    }
                    else
                    {
                        PRINT_SYS_FATAL("Falha no download");
                    }
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
                        {"Outdated apps", "outdated_apps", security_aba},
                        {"Voltar", "voltar", security_aba},
                    };
                    MOPTS::ShowMenu("Configurações de seguranca", security_opts, "> ", "");
                }
                else if (comando == "system_info" || comando == "sys_info")
                {
                    cout << "OS: BigDragonOS" << endl;
                    cout << "Storage: " << armazenamento_total_aplicativos_str << endl;
                    cout << "User: " << usernameprofile << endl;
                    cout << "Gender: " << genderuser << endl;
                    cout << "Actual version: " << actualvers << endl;
                    cout << "This version: " << thisvers << endl;
                }
                else if (comando == "beep")
                {
                    tocarSom("storage\\configs\\sounds\\beep.wav");
                    Sleep(1000);
                }
                else if (comando.rfind("sound ", 0) == 0)
                {
                    string onouoff = comando.substr(6);
                    if (onouoff == "on" || onouoff == "unmute")
                    {
                        set_sound("true");
                    }
                    else if (onouoff == "off" || onouoff == "mute")
                    {
                        set_sound("false");
                    }
                    else
                    {
                        PRINT_SYS_FATAL("Erro, um sinal foi enviado errado");
                    }
                }
                else if (comando == "shutdown")
                {
                    clear_cmd();
                    while (true)
                    {
                        Sleep(1000);
                    }
                }
                else if (comando == "configs")
                {
                    MOPTS::MenuOption configs_opts[] = {
                        {"Mutex", "mutex", configs_aba},
                        {"Sounds", "sounds", configs_aba},
                        {"Logs", "logs", configs_aba},
                        {"Voltar", "voltar", configs_aba},
                    };

                    MOPTS::ShowMenu("Configurações", configs_opts, "> ", "");
                }
                else if (comando == "credits")
                {
                    PRINT_SYS_BLUE("Criado por: ThiagoBel");
                }
                else if (comando == "clear_logs")
                {
                    CLEAR_LOGS_ERROR();
                    CLEAR_LOGS_HISTORY();
                }
                else if (comando == "clear_logs_error")
                {
                    CLEAR_LOGS_ERROR();
                }
                else if (comando == "clear_logs_history")
                {
                    CLEAR_LOGS_HISTORY();
                }
                else if (comando == "show_logs_error")
                {
                    ifstream filefilefile(errors_log_file);
                    string linha;
                    if (filefilefile.is_open())
                    {
                        while (getline(filefilefile, linha))
                        {
                            PRINT_SYS_BLUE(linha);
                        }
                    }
                    else
                    {
                        PRINT_SYS_FATAL("Erro ao mostrar as logs de erro");
                    }
                    filefilefile.close();
                }
                else if (comando == "show_logs_history")
                {
                    ifstream filefilefile(history_log_file);
                    string linha;
                    if (filefilefile.is_open())
                    {
                        while (getline(filefilefile, linha))
                        {
                            PRINT_SYS_BLUE(linha);
                        }
                    }
                    else
                    {
                        PRINT_SYS_FATAL("Erro ao mostrar as logs de historico de comandos");
                    }
                    filefilefile.close();
                }
                else
                {
                    string sugestao = sugerir_comando(comando);

                    if (!sugestao.empty())
                    {
                        PRINT_SYS_FATAL("Comando desconhecido, você quis dizer '" + sugestao + "'?");
                    }
                    else
                    {
                        PRINT_SYS_FATAL("Comando desconhecido");
                    }
                    modengc = "error";
                }
                if (modengc == "sucess")
                {
                    if (canpop == true)
                    {
                        tocarSom("storage\\configs\\sounds\\pop.wav");
                    }
                }
                else
                {
                    tocarSom("storage\\configs\\sounds\\error.wav");
                }
                canpop = true;
                if (logs == true)
                {
                    ofstream logsHIS(history_log_file, ios::app);
                    if (logsHIS.is_open())
                    {
                        logsHIS << "[HISTORY] [" << getDateTime() << "] " << comando << "\n";
                    }
                    else
                    {
                        PRINT_SYS_FATAL("Erro ao abrir arquivo de logs de histórico");
                    }
                }
            }
        }
    }
    system("pause >nul");
    return 0;
}