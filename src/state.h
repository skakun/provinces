#pragma once
#include <string>
#include <vector>
#include <memory>
#include "province.h"
#include "named.h"
struct State
{
//								std::string id;
								int tresuery=0;
						  Named<Province> capital;	
};
typedef std::shared_ptr<State> p_State;
