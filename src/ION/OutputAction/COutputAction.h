
#ifndef OUTPUT_ACTION_H__
#define OUTPUT_ACTION_H__

#include <string>

class COutputAction
{
    public:

        COutputAction();
        virtual ~COutputAction();

        virtual bool PerformAction(const std::string& data, const std::string& actionArgument) = 0;

    protected:

};



#endif  // OUTPUT_ACTION_H__