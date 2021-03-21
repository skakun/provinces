#pragma once
#include<string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
template<class T> 
struct Named
{
    std::string name;
    std::shared_ptr<T> inst;
    bool operator ==(const Named<T> &n)
    {
        return name==n.name;

    };
    bool operator ==(const std::string &_name)
    {
        return name==_name;

    };
    Named<T> & operator=(const Named<T>& l)
    {
        name=l.name;
        inst=l.inst;
        return *this;
    }

    T* operator ->()
    {
        return inst.get();
    };
    struct Hash
    {
        size_t operator() (const Named<T> NT)
        {
            return std::hash<std::string>()(NT.name);
        };
        size_t operator() (const Named<T>& NT)
            const
            {
                return std::hash<std::string>()(NT.name);
            };
    };
    using InstMap=std::unordered_map<std::string,Named<T>>;
    using AsoMap=std::unordered_map<std::string,std::vector<Named<T>>>;
    using Pair=std::pair<std::string,Named<T>>;

};
template<class T, class ... A> Named<T> make_named(std::string name,A... args)
{
    return Named<T>(name,std::make_shared<T>(args...));
}
template<class From,class To> Named<To> named_cast(Named<From> f)
{
    return Named<To>{f.name,std::static_pointer_cast<To>(f.inst)};
}
template<class K,class V>
using DirectAsoMap=std::unordered_map< Named<K>,Named<V>,typename Named<K>::Hash>;
template<class N,class U> 
using Named2UnMap=std::unordered_map<Named<N>,std::vector<U>,typename Named<N>::Hash>;


template<class T>
bool operator==(const Named<T> l,const Named<T> r)
{
    return r.name==l.name;
}

    template<class T,class ...A>
std::pair<std::string,Named<T>> makeNamedPair(std::string name,A... args)
{
    return {name, {name,std::make_shared<T>(args...)}};
}
    template<class Slave> 
bool setOwnership(typename Named<Slave>::AsoMap & map,
        typename Named<Slave>::InstMap & slaves,
        std::string whose, std::string toWho)
{
    bool reasigned=false;
    for(auto &po :map)
    {
        const auto _p=&po.second;
        _p->erase(
                std::remove_if(
                    po.second.begin(),
                    po.second.end(),
                    [whose,&reasigned](const Named<Slave> &p)
                    {
                    reasigned= not reasigned
                    and p.name==whose;
                    return p.name==whose;
                    }
                    ),
                po.second.end()
                );

    }
    auto & p=slaves[whose];
    map[toWho].push_back(p);
    return reasigned;
}
namespace std
{
    template<class T> struct hash<Named<T>> 
    {
        size_t operator() (const Named<T> NT)
        {
            return hash<std::string>()(NT.name);
        };
        size_t operator() (const Named<T>& NT)
        {
            return hash<std::string>()(NT.name);
        };
    };
}
