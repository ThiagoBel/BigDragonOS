#ifndef CL_HPP
#define CL_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

inline std::string CHECK_LOGS(const std::string &logname)
{
    std::string caminho = "storage/configs/logs/";
    std::ifstream louco(caminho + logname);
    std::string linha;
    std::stringstream negocios;

    if (!louco.is_open())
    {
        return "ERROR";
    }
    else
    {
        while (getline(louco, linha))
        {
            negocios << linha << "\n";
        }
        louco.close();
    }

    if (negocios.str().empty())
    {
        return "Vazio...";
    }
    return negocios.str();
}

namespace HBDOS
{
    inline std::string CHECK_LOGS_ERR() { return CHECK_LOGS("errors.log"); }
    inline std::string CHECK_LOGS_HIS() { return CHECK_LOGS("history.log"); }
}

#endif