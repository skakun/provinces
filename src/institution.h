#pragma once
#include <string>
#include <tuple>
#include "faction.h"
#include <memory>
#include "named.h"
#include <unordered_map>
#include "Params.h"
#include <math.h>
enum InstitutionType
{
    WHEAT_FIELD,GOV
};
struct Institution
{
    InstitutionType type;
    /*
    Institution(InstitutionType _type):
        type(_type) {};
    float base_yield=10;
    float yield();
    */
    std::unordered_map<Named<Faction>,float,Named<Faction>::Hash>
        ownership;
};
struct WheatField :public Institution
{
    float base_yield=10;
    int field_improvement_level;
    float yield();
    WheatField(float _base_yield,int _field_improvement_level);
};
struct Gov:public Institution
{
    Gov();
};
