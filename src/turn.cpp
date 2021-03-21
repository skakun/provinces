#include "turn.h"
void evalTurn(Board& board)
{
    for(auto & in :board.factions)
    {
        fetchDemenseIncome(in.second,board);
        procTaxes(in.second,board);
        applyIncome(in.second,board);

    }
}
bool ActionStack::addIfValid(std::shared_ptr<Action> a, Board &b)
{
    bool ret=a->validate(b);
    if(ret) q.push(a);
    return ret;
}
void ActionStack::exec(Board &b)
{
    auto a=q.front();
    while(a)
    {
        a->execute(b);
        q.pop();
        a=q.front();
    }

}
