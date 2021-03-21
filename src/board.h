#pragma once
#include "province.h"
#include "state.h"
#include "province.h"
#include <unordered_map>
#include <algorithm>
#include <vector>
#include "named.h"
#include "institution.h"
#include "faction_relation.h"
/*
   Main containers should be like
   unordered_list<std::string,Named<T>>
Associacions:
unordedered_list<string,Named<T>>

To keep things simple lets do it semi structural and keep all stuff here
*/
struct Board
{
    //-------------------------------------------------								
    //Main containers
    Named<State>::InstMap states;
    Named<Province>::InstMap provinces;
    std::shared_ptr<Named<Institution>::InstMap> institutions;
    Named<Faction>::InstMap factions;

    //-------------------------------------------------
    //Associacions
    Named<Province>::AsoMap provinceOwnership;//by state
    Named<Institution>::AsoMap instiPerProvince;
    Named<Faction>::AsoMap facPerProvince;
//    Named2UnMap<Faction, std::shared_ptr<FactionRoutine>> factionRoutines;
    //std::vector<std::shared_ptr<FactionRoutine>> factionRoutines;


    using RelationMap=
        std::unordered_map<Named<Faction>,
            std::vector<std::shared_ptr<FactionRelation>>,
            Named<Faction>::Hash>;
    using p_RelationMap=std::shared_ptr<RelationMap>; 

    p_RelationMap p_relationsByMaster;
    p_RelationMap p_relationsBySlave;
    RelationMap relationsByMaster();
    RelationMap relationsBySlave();


    //------------------------------------------------
    Board();
    void setProvinceOwnership(std::string prov,std::string state);
    float adjustInstitutionOwnership(std::string faction, std::string institution, float absoluteChange);
    void addState(std::string name);
    void addFaction(std::string name,FactionType type,int wealth);
    void addInstitution(Named<Institution> insti);
    void assignInstitutionToProvince(std::string inst,std::string province);
    void addRelation(std::shared_ptr<FactionRelation> rel);
    void delRelation(std::shared_ptr<FactionRelation> rel);
    Named<Institution>::InstMap _institutions();
    
};
