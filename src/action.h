#pragma once
#include <vector>
#include <string>
#include "board.h"
#include "Params.h"
enum ActionType
{
 BUILD/*what institution,what building*/
};
struct Action
{
    virtual bool validate(Board & board)=0;
    virtual void execute(Board & board)=0;
};

struct ImproveWheatField :public Action
{
    //args: faction,institution
    std::string faction;
    std::string institution;
    ImproveWheatField(std::string faction,std::string institution);
    bool validate(Board & board) override;
    void execute(Board & board) override;
};
