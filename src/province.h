#pragma once
#include <string>
#include <memory>
#include "institution.h"
#include <vector>
struct Province
{
    //								std::string id;
    //Tmp, separate fe?
    int pos_x=0;
    int pos_y=0;
    std::vector<std::shared_ptr<Institution>> institutions;
    //							Province(std::string _id): id(_id){};

};
typedef std::shared_ptr<Province> p_Province;
