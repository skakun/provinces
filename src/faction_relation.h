#pragma once
#include "named.h"
#include "faction.h"
enum RelationType
{
    DEF,
    SUBORDINATION
};

struct FactionRelation
{
    Named<Faction> master;
    Named<Faction> slave;
    RelationType type;
    bool operator==(const FactionRelation & other);
};
struct Subordination: public FactionRelation
{
    float taxRate;
    Subordination(Named<Faction> _master, Named<Faction> _slave,float _taxRate); 

};
