#pragma once
#include <string>
#include "Params.h"
enum FactionType
{
    ARISTOCRATIC,
    BUREUCRATIC,
    POPULAR,
    PLUTOCRATIC
};
struct Faction
{
    FactionType type;
    float wealth;
    float newIncome=0;
    float typeIncomeRatio;
    Faction(FactionType _type, float _wealth): 
        type(_type), wealth(_wealth)
    {
        switch(type)
        {
            case ARISTOCRATIC:
                {
                    typeIncomeRatio=Params::AristocraticIncomeRatio;
                }
            case BUREUCRATIC:
                {
                    typeIncomeRatio=Params::BureucraticIncomeRatio;
                }
            case POPULAR:
                {
                    typeIncomeRatio=Params::PopularIncomeRation;
                }
            case PLUTOCRATIC:
                {
                    typeIncomeRatio=Params::PlutocraticIncomeRatio;
                }
        }
    };

};

