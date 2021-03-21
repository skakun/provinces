#include "FactionRoutine.h"
/*
FetchDemenseIncome::
    FetchDemenseIncome(Named<Faction>_ins,
        std::shared_ptr<Named<Institution>::InstMap> _institutions)
{
    ins=_ins;
    institutions=_institutions;
    switch (ins->type)
    {
        case PLUTOCRATIC:
            {
                typeIncomeRatio=1;
                break;
            };
        case BUREUCRATIC:
            {
                typeIncomeRatio=0.8;
                break;
            }
        case ARISTOCRATIC:
            {
                typeIncomeRatio=0.7;
                break;
            }
        case POPULAR:
            {
               typeIncomeRatio=0.5; 
               break;
            }
    }
}

void FetchDemenseIncome::operator()() 
{
    PL(" Enterng FetchDemense");
    for(auto &ip:*(institutions))
    {
        if(ip.second->type==WHEAT_FIELD)
        {
            try
            {
                float ownership=ip.second->ownership.at(ins);
                PL(ins.name<<" ratio: "<<typeIncomeRatio);
                auto wf=
                    std::static_pointer_cast<WheatField>(
                            ip.second.inst);
                float income=wf->yield()*typeIncomeRatio*ownership;
                PL("income: "<<income<<ins.name<<" :"<<ip.first);
                ins->newIncome+=income;
            }
            catch(std::out_of_range ex)
            {
                PL("oor: "<<ins.name<<" :"<<ip.first);
                ;
            }
        }
    }
}
ProcTaxes::ProcTaxes(Named<Faction> _ins,p_RelationMap bm,p_RelationMap bs)
{
    ins=_ins;
    byMaster=bm;
    bySlave=bs;
}
void ProcTaxes::operator()()
{//TODO:: sort by hierarchy?
    PL(" Enterng ProcTaxes");
    for(auto & bs:*bySlave)
    {
        for(auto  s:bs.second)
        {
            if(s->type==SUBORDINATION)
            {
                float d=0;
                auto r=std::static_pointer_cast<Subordination>(s);
                d=r->taxRate*r->slave->newIncome;
                PL("d= "<<d);
                r->slave->newIncome-=d;
                r->master->newIncome+=d;
            }
        }
    }
}
ApplyIncome::ApplyIncome(Named<Faction> _inst)
{
    ins=_inst;
}
void ApplyIncome::operator()()
{
    PL(" Enterng ApplyIncome");
    ins->wealth+=ins->newIncome;
    ins->newIncome=0;
}
*/
void fetchDemenseIncome(Named<Faction> ins,Board& board)
{
    PL(" Enterng FetchDemense");
    for(auto &ip:*board.institutions)
    {
        if(ip.second->type==WHEAT_FIELD)
        {
            try
            {
                float ownership=ip.second->ownership.at(ins);
                PL(ins.name<<" ratio: "<<ins->typeIncomeRatio);
                auto wf=
                    std::static_pointer_cast<WheatField>(
                            ip.second.inst);
                float income=wf->yield()*ins->typeIncomeRatio*ownership;
                PL("income: "<<income<<ins.name<<" :"<<ip.first);
                ins->newIncome+=income;
            }
            catch(std::out_of_range ex)
            {
                PL("oor: "<<ins.name<<" :"<<ip.first);
                ;
            }
        }
    }
}
void procTaxes(Named<Faction> ins,Board& board)
{//TODO:: sort by hierarchy?
    PL(" Enterng ProcTaxes");
    for(auto & bs:board.relationsBySlave())
    {
        for(auto  s:bs.second)
        {
            if(s->type==SUBORDINATION)
            {
                float d=0;
                auto r=std::static_pointer_cast<Subordination>(s);
                d=r->taxRate*r->slave->newIncome;
                PL("d= "<<d);
                r->slave->newIncome-=d;
                r->master->newIncome+=d;
            }
        }
    }
}

void applyIncome(Named<Faction> ins,Board& board)
{
    PL(" Enterng ApplyIncome");
    ins->wealth+=ins->newIncome;
    ins->newIncome=0;
}
