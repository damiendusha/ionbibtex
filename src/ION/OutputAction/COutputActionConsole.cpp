
#include "COutputActionConsole.h"
#include <iostream>


COutputActionConsole::COutputActionConsole()
{
}


COutputActionConsole::~COutputActionConsole()
{
}


bool COutputActionConsole::PerformAction(const std::string& data, const std::string&)
{
    std::cout << data << std::endl;
    return true;
}
