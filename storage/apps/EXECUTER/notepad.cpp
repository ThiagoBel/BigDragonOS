#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "NOTEPAD_APP/MOPTS.h"

using namespace std;

const string blacklist[] = {"MOPTS.h"};

bool EstaProtegido(const string &nomeArquivo)
{
    for (const auto &protegido : blacklist)
    {
        if (nomeArquivo == protegido)
            return true;
    }
    return false;
}

vector<string> ListarArquivos()
{
    vector<string> arquivos;
    string cmd = "dir \"storage/apps/EXECUTER/NOTEPAD_APP\" /b /A:-D";
    FILE *fp = _popen(cmd.c_str(), "r");
    if (!fp)
        return arquivos;

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        string linha(buffer);
        linha.erase(linha.find_last_not_of("\r\n") + 1);
        if (!linha.empty())
            arquivos.push_back(linha);
    }
    _pclose(fp);
    return arquivos;
}

void VerArquivos(const string &classe)
{
    vector<string> arquivos = ListarArquivos();
    cout << "Arquivos existentes:\n\n";
    for (const auto &arq : arquivos)
        cout << "- " << arq << endl;

    cout << "\nPressione Enter para continuar...";
    cin.ignore();
}

void CriarOuEditar(const string &classe)
{
    system("mkdir storage/apps/EXECUTER/NOTEPAD_APP > nul 2> nul");
    string nomeArquivo;
    cout << "Digite o nome do arquivo para criar/editar: ";
    getline(cin, nomeArquivo);
    if (EstaProtegido(nomeArquivo))
    {
        cout << "Erro, esse arquivo não pode ser editado\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        return;
    }
    string caminho = "storage/apps/EXECUTER/NOTEPAD_APP\\" + nomeArquivo + ".txt";
    ofstream arquivo(caminho, ios::app);
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }
    cout << "Digite seu texto (digite '/save' para terminar):\n";
    string linha;
    while (true)
    {
        getline(cin, linha);
        if (linha == "/save")
            break;
        arquivo << linha << endl;
    }
    arquivo.close();
    cout << "Arquivo salvo com sucesso\n";
    cout << "Pressione Enter para continuar...";
    cin.ignore();
}

void LerArquivo(const string &classe)
{
    vector<string> arquivos = ListarArquivos();

    if (arquivos.empty())
    {
        cout << "Não achamos nenhum arquivo\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        return;
    }

    MOPTS::MenuOption *opcoes = new MOPTS::MenuOption[arquivos.size() + 1];

    for (size_t i = 0; i < arquivos.size(); i++)
    {
        opcoes[i].texto = arquivos[i];
        opcoes[i].classe = arquivos[i];
        opcoes[i].func = [](const string &nome)
        {
            string caminho = "storage/apps/EXECUTER/NOTEPAD_APP\\" + nome;
            ifstream arquivo(caminho);
            if (!arquivo.is_open())
            {
                cout << "Erro, não achei o arquivo\n";
            }
            else
            {
                cout << "\n--------------\n";
                string linha;
                while (getline(arquivo, linha))
                {
                    cout << linha << endl;
                }
                cout << "--------------\n";
                arquivo.close();
            }
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
        };
    }

    opcoes[arquivos.size()].texto = "Cancelar";
    opcoes[arquivos.size()].classe = "";
    opcoes[arquivos.size()].func = [](const string &)
    {
        cout << "Operação cancelada\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore();
    };

    MOPTS::ShowMenuDynamic("Selecione o arquivo para ler", opcoes, arquivos.size() + 1, "> ", "");

    delete[] opcoes;
}

void DeletarArquivoSelecionado(const string &arquivo)
{
    string caminho = "storage/apps/EXECUTER/NOTEPAD_APP\\" + arquivo;
    if (remove(caminho.c_str()) == 0)
        cout << "" << arquivo << " deletado\n";
    else
        cout << "Erro ao deletar o arquivo\n";

    cout << "Pressione Enter para continuar...";
    cin.ignore();
}

void ExcluirArquivo(const string &classe)
{
    vector<string> arquivos = ListarArquivos();

    vector<string> deletaveis;
    for (auto &arq : arquivos)
        if (!EstaProtegido(arq))
            deletaveis.push_back(arq);

    if (deletaveis.empty())
    {
        cout << "Não achei nenhum arquivo\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        return;
    }

    MOPTS::MenuOption *opcoes = new MOPTS::MenuOption[deletaveis.size() + 1];

    for (size_t i = 0; i < deletaveis.size(); i++)
    {
        opcoes[i].texto = deletaveis[i];
        opcoes[i].classe = deletaveis[i];
        opcoes[i].func = [](const string &nome)
        {
            string caminho = "storage/apps/EXECUTER/NOTEPAD_APP\\" + nome;
            if (remove(caminho.c_str()) == 0)
                cout << "" << nome << " deletado\n";
            else
                cout << "Erro ao deletar o arquivo\n";

            cout << "Pressione Enter para continuar...";
            cin.ignore();
        };
    }

    opcoes[deletaveis.size()].texto = "Cancelar";
    opcoes[deletaveis.size()].classe = "";
    opcoes[deletaveis.size()].func = [](const string &)
    {
        cout << "Operação cancelada\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore();
    };

    MOPTS::ShowMenuDynamic("Selecione o arquivo para deletar", opcoes, deletaveis.size() + 1, "> ", "");

    delete[] opcoes;
}

int main()
{
    MOPTS::color = false;
    MOPTS::all_color_line = false;
    MOPTS::clear_opts = true;

    MOPTS::MenuOption opcoes[] = {
        {"Criar/Editar arquivo", "CRIAR_EDITAR", CriarOuEditar},
        {"Ler arquivo", "LER", LerArquivo},
        {"Deletar arquivo", "EXCLUIR", ExcluirArquivo},
        {"Ver arquivos", "VER", VerArquivos},
        {"Sair", "SAIR", [](const string &)
         { exit(0); }}};

    while (true)
    {
        MOPTS::ShowMenu("Bloco de notas", opcoes, "> ", "");
    }

    return 0;
}