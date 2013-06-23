
#ifndef OUTPUT_ACTION_EXECUTE_PROGRAM_H__
#define OUTPUT_ACTION_EXECUTE_PROGRAM_H__

#include "COutputAction.h"

class COutputActionExecuteProgram : public COutputAction
{
    public:

        COutputActionExecuteProgram();
        virtual ~COutputActionExecuteProgram();

        virtual bool PerformAction(const std::string& data, const std::string& actionArgument);

    protected:

};

#endif  // OUTPUT_ACTION_EXECUTE_PROGRAM_H__
