
#ifndef OUTPUT_ACTION_CONSOLE_H__
#define OUTPUT_ACTION_CONSOLE_H__

#include "COutputAction.h"

class COutputActionConsole : public COutputAction
{
    public:

        COutputActionConsole();
        virtual ~COutputActionConsole();

        virtual bool PerformAction(const std::string& data, const std::string& actionArgument);

    protected:

};

#endif  // OUTPUT_ACTION_CONSOLE_H__
