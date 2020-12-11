#pragma once
#include <vector>
#include "predator.h"
#include "prey.h"

class PreyTable {
public:


    vector<pair<Prey*, double>> data;

    PreyTable()
    {

    }

    void Add(Prey* p, double f)
    {
        data.push_back(make_pair(p, f));
    }

    void Sort()
    {
        sort(data.begin(), data.end());
    }

    bool sortFunction(pair<Prey, double>& a, pair<Prey, double>& b)
    {
        return a.second > b.second;
    }
};

class PredatorTable {
public:

    vector<pair<Predator*, double>> data;


    PredatorTable()
    {

    }

    void Add(Predator* p, double f)
    {
        data.push_back(make_pair(p, f));
    }

    void Sort()
    {
        sort(data.begin(), data.end());
    }

    bool sortFunction(pair<Predator, double>& a, pair<Predator, double>& b)
    {
        return a.second > b.second;
    }
};

