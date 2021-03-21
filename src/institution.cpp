#include "institution.h"
float WheatField::yield()
{
    return base_yield*log2(field_improvement_level+2);
}
WheatField::WheatField(float _base_yield,int _field_improvement_level=0)
    :base_yield(_base_yield)
{
    type=WHEAT_FIELD;
    field_improvement_level=_field_improvement_level;

}
Gov::Gov()
{
    type=GOV;
}


