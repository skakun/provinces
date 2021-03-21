#include<iostream>
#include<string.h>
#include "board.h"
#include "turn.h"
#include "action.h"
#define PL(x) std::cout<<x<<std::endl;
void debugPrint(Board & board)
{
PL("/____________________________________________________________");
    for(auto po: board.provinceOwnership)
    {
        std::cout<<po.first<<" owns:\n";
        for(auto p: po.second)
        {
            auto p_inst=p.inst;
            std::cout<<"\t"<<p.name<<"\n";
        }
    //    auto state=board.states[po.first];

    }
    for(auto& f: board.factions)
    {
        PL(f.first<<" owns:\n")
        for(auto & i: *board.institutions)
        {
            if( i.second->ownership.find(f.second)!=
                    i.second->ownership.end() )
            {
                PL("\t"<<i.first<<" "
                        <<100*i.second->ownership[f.second]<<"%");
            }

        }
        PL("tresuary: "<<f.second->wealth);

    }
}
int main(int argc, char ** argv)
{
    std::cout<<"Witam\n";


    Board board;
    board.provinces=
    { 
        {makeNamedPair<Province>("p_assur")},
        {makeNamedPair<Province>("p_uruk")}
    };

    board.addState("s_assur");
    board.addState("s_uruk");
    board.addFaction("f_palace_uruk", BUREUCRATIC, 1000);
    board.addFaction("f_merchants_uruk", PLUTOCRATIC, 0);
//    board.addInstitution("i_fields_uruk", WHEAT_FIELD);
    board.addInstitution(Named<Institution>{"i_fields_uruk",
            std::make_shared<WheatField>(Params::WheatFieldBaseYield,0)}
            );
    board.addInstitution(Named<Institution>{ "i_palace_uruk",
                std::make_shared<Gov>()}
                );
    board.setProvinceOwnership("p_uruk","s_uruk");
    board.setProvinceOwnership("p_assur","s_assur");
    board.assignInstitutionToProvince("i_fields_uruk","p_uruk");
    board.adjustInstitutionOwnership("f_palace_uruk","i_fields_uruk" ,1.0 );
    board.adjustInstitutionOwnership("f_palace_uruk","i_palace_uruk" ,1.0 );
    board.adjustInstitutionOwnership("f_merchants_uruk","i_fields_uruk" ,1.0 );
    board.addRelation
        (
         std::static_pointer_cast<FactionRelation>
         (
          std::make_shared<Subordination>
          (
           Named<Faction>{"f_palace_uruk"},
           Named<Faction>{"f_merchants_uruk"},
           0.1
          )
         )
        );

    ActionStack as;
    as.addIfValid(std::static_pointer_cast<Action>
            (
             std::make_shared<ImproveWheatField>
                 ("f_palace_uruk","i_fields_uruk")
            ),
            board
            );
    for(int i=0; i<10; i++)
    {
        PL("Turn"<<i);
        evalTurn(board);
        as.exec(board);
        debugPrint(board);
    }

}
