#include"named.h"
#include <algorithm>
template<class L,class R>
struct OneToOneMap
{
    using LType=L;
    using RType=R;
    std::unordered_map<Named<L>,Named<R>,typename Named<L>::Hash>  RperL;
    std::unordered_map<Named<R>,Named<L>,typename Named<R>::Hash>  LperR;
    void insert(Named<L> l, Named<R> r)
    {
        RperL[l]=r;
        LperR[l]=r;

     }
};

template<class L,class R>
struct OneToManyMap
{
    using LType=L;
    using RType=R;
    using RVec=std::vector<Named<R>>;
    std::unordered_map<Named<L>,RVec,typename Named<L>::Hash>  RperL;
    std::unordered_map<Named<R>,Named<L>,typename Named<R>::Hash>  LperR;
    
    void insert(Named<L> l, Named<R> r)
    {
        for(auto &p :RperL)
        {
            if
            (
                p.second.erease(
                            std::remove(
                                p.second.begin(),
                                p.second.end(),
                                r
                            ),
                            p.second.end()
                        )
            ) break;

        }
        LperR[l].push_back(r);
        RperL[l]=r;
     }
};
