#include "board.h"
Board::Board()
{
    institutions=std::make_shared<Named<Institution>::InstMap>();
    p_relationsBySlave=std::make_shared<RelationMap>();
    p_relationsByMaster=std::make_shared<RelationMap>();
}
void Board::setProvinceOwnership(std::string prov,std::string state)
{
    setOwnership<Province>(provinceOwnership,provinces,prov,state);
}

void Board::addState(std::string name)
{
    states.insert(makeNamedPair<State>(name));
    std::vector<Named<Province>> v;
    provinceOwnership.insert(make_pair(name,v));
}
void Board::addFaction(std::string name, FactionType type,int wealth  )
{
    factions.insert(makeNamedPair<Faction>( name, type, wealth));
    std::vector<Named<Faction>> v;
    facPerProvince.insert(make_pair(name,v));//Why I did so?
    auto & f=factions[name];
    //TODO make less retarded, exec once, only iterste hrough factions?, inst would go to () operator
    /*
    factionRoutines.insert({f,
                {
                    std::make_shared<FetchDemenseIncome>(f,institutions)
                }
            }
            );

    factionRoutines.insert({f,
            {
                std::make_shared<ProcTaxes>
                (
                 f, p_relationsByMaster,p_relationsBySlave
                )
            }
            }
            );
    factionRoutines.insert({f,
            {
                std::make_shared<ApplyIncome>(f)
            }
            }
            );
    PL("Routines size: "<<factionRoutines.size());
    */
}

void Board::addInstitution(Named<Institution> insti)
{
    institutions->insert(std::make_pair(insti.name,insti));
    //   std::vector<Named<Institution>> v;
    //    instiPerProvince.insert(make_pair(insti.name,v));
}

void Board::assignInstitutionToProvince(std::string inst,
        std::string province)
{
    setOwnership<Institution>(instiPerProvince,*institutions,inst,province);
}

float Board::adjustInstitutionOwnership(std::string faction, std::string institution, float absoluteChange)
{
    auto i=(*institutions)[institution];
    auto f=factions[faction];
    if(i->ownership.find(f)==i->ownership.end())
    {
        i->ownership.insert(std::make_pair(f,absoluteChange));
    }
    else
    {
        i->ownership[f]+=absoluteChange;
    }
    float total=0;
    for(auto & io:i->ownership)
    {
        total+=io.second;
    }
    for(auto & io:i->ownership)
    {
        io.second/=total;
    }
    return 0;
}
Named<Institution>::InstMap Board:: _institutions()
{
    return *institutions;
}
void Board::addRelation(std::shared_ptr<FactionRelation> rel)
{
    rel->master=factions[rel->master.name];
    rel->slave=factions[rel->slave.name];

    relationsByMaster()[rel->master].push_back(rel);
    relationsBySlave()[rel->slave].push_back(rel);

}
Board::RelationMap Board::relationsByMaster()
{
    return *p_relationsByMaster;
}
Board::RelationMap Board::relationsBySlave()
{
    return *p_relationsBySlave;
}

