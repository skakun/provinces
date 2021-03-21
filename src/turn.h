#include "board.h"
#include "institution.h"
#include <queue>
#include "action.h"
#include <memory>
#include "FactionRoutine.h"
struct ActionStack
{
    std::queue<std::shared_ptr<Action>> q;
    bool addIfValid(std::shared_ptr<Action> a,Board& b);
    void exec(Board & b);

};
void evalTurn(Board & board);

