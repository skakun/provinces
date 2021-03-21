#include "faction_relation.h"

bool FactionRelation::operator==(const FactionRelation & other)
{
    return type==other.type and 
        master==other.master and
        slave==other.slave;
}

Subordination::Subordination(Named<Faction> _master, 
        Named<Faction> _slave,float _taxRate)
{
    master=_master;
    slave=_slave;
    taxRate=_taxRate;
    type=SUBORDINATION;
}
