#pragma once
#include "faction.h"
#include "named.h"
#include "institution.h"
#include <stdexcept>
#include "Params.h"
#include <unordered_map>
#include "faction_relation.h"
#include "board.h"

#include <iostream>
#define PL(x) std::cout<<x<<std::endl;
/*
struct FactionRoutine
{
    float typeIncomeRatio=0;
    virtual void operator()(Named<)=0;
};
struct FetchDemenseIncome:public FactionRoutine
{
    std::shared_ptr<Named<Institution>::InstMap> institutions;
    FetchDemenseIncome(Named<Faction>_ins,
        std::shared_ptr<Named<Institution>::InstMap> _institutions);
    void operator()() override;
};
struct ProcTaxes:public FactionRoutine
{
    using RelationMap=
        std::unordered_map<
            Named<Faction>,
            std::vector<std::shared_ptr<FactionRelation>>,
            Named<Faction>::Hash
                >;
    using p_RelationMap=std::shared_ptr<RelationMap>;
    p_RelationMap byMaster;
    p_RelationMap bySlave;
    ProcTaxes(Named<Faction> inst,p_RelationMap bm,p_RelationMap bs);
    void operator()() override;
};
struct ApplyIncome:public FactionRoutine
{
    ApplyIncome(Named<Faction>_inst);
    void operator()() override;
};
*/
void fetchDemenseIncome(Named<Faction> inst,Board& board);
void procTaxes(Named<Faction> inst,Board& board);
void applyIncome(Named<Faction> inst,Board& board);


