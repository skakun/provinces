#include"action.h"
ImproveWheatField::ImproveWheatField(std::string _faction,std::string _institution)
{
    faction=_faction;
    institution=_institution;
};
bool ImproveWheatField::validate(Board &board)
{
    auto& f=board.factions[faction];
    auto _in=board._institutions()[institution];
    auto in=named_cast<Institution,WheatField>(_in);
    if(in->ownership[f] <0.1) return false;
    return f->wealth > Params::initFarmCost+(in->field_improvement_level+1)*Params::farmYieldIncrease;
}
void ImproveWheatField::execute(Board &board)
{
    auto _in=board._institutions()[institution];
    auto in=named_cast<Institution,WheatField>(_in);
    in->field_improvement_level++;

    auto& f=board.factions[faction];
    f->wealth-=Params::initFarmCost+(in->field_improvement_level+1)*Params::farmYieldIncrease;
}

