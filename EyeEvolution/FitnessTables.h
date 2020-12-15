#pragma once
#include <vector>
#include "predator.h"
#include "prey.h"

class PreyTable {
public:

    int fitness_sum = 0;
    vector<pair<Prey*, double>> data;

    PreyTable()
    {

    }

    void Add(Prey* p, double f)
    {
        data.push_back(make_pair(p, f));
        fitness_sum += f;
    }

    void Add(Prey* p)
    {
        data.push_back(make_pair(p, p->fitness));
        fitness_sum += p->fitness;
    }

    void Sort()
    {
        sort(data.begin(), data.end());
    }

    bool sortFunction(pair<Prey*, double>& a, pair<Prey*, double>& b)
    {
        return a.second > b.second;
    }

    vector<Prey*> getTable()
    {

        vector<Prey*> table;
        for (int i = 0; i < data.size(); i++)
        {
            table.push_back(data[i].first);
        }
        return table;
    }

    void clear()
    {
        data.clear();
    }

};

class PredatorTable {
public:

    vector<pair<Predator*, double>> data;

    int fitness_sum = 0;


    PredatorTable()
    {

    }

    void Add(Predator* p, double f)
    {
        data.push_back(make_pair(p, f));
        fitness_sum += f;
    }

    void Add(Predator* p)
    {
        data.push_back(make_pair(p, p->fitness));
        fitness_sum += p->fitness;
    }

    void Sort()
    {
        sort(data.begin(), data.end());
    }

    bool sortFunction(pair<Predator*, double>& a, pair<Predator*, double>& b)
    {
        return a.second > b.second;
    }

    vector<Predator*> getTable()
    {

        vector<Predator*> table;
        for (int i = 0; i < data.size(); i++)
        {
            table.push_back(data[i].first);
        }
        return table;
    }

    void clear()
    {
        data.clear();
    }
};

Prey rouletteWheel(vector<Prey*> Prey, int fitnessSum)
{
    int r;
    if (fitnessSum == 0)
        r = rand() % Prey.size() - 1;
    else
        r = (rand() % fitnessSum) % (Prey.size());
    int iteratedSum = 0;
    for (int i = 0; i < Prey.size(); i++)
    {
        iteratedSum += Prey[i]->fitness;
        if (iteratedSum >= r)
            return *Prey[i];
    }
    return *Prey[r];
}


Predator rouletteWheelpred(vector<Predator*> predator, int fitnessSum)
{
    int r;
    if (fitnessSum == 0)
        r = rand() % predator.size() - 1;
    else
        r = (rand() % fitnessSum) % (predator.size());
    int iteratedSum = 0;
    for (int i = 0; i < predator.size(); i++)
    {
        iteratedSum += predator[i]->fitness;
        if (iteratedSum >= r)
            return *predator[i];
    }
    return *predator[r];
}
