#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#pragma once
#include "prey.h"
#include "predator.h"
#include <SFML/Graphics.hpp>
#include "FitnessTables.h"


class Food
{
public:
    sf::CircleShape shape;

    Food()
    {
        shape.setFillColor(Color::Yellow);
        shape.setRadius(10);
        shape.setOrigin(Vector2f(shape.getRadius(), shape.getRadius()));
        shape.setRotation(45);
    }
};

class Environment
{
public:

    int NUM_ITERATIONS = 0;

    bool bCaught = false;
    bool bTimedOut = false;

	vector<Prey*> preyVector;
    vector<Prey*> preySoloVector;
	vector<Predator*> predatorVector;
    vector<Predator*> predatorSoloVector;
    sf::RenderWindow* window;
    int NUM_EYES = 2;
    int timeElapsed = 0;
    int TEST_Duration = 4000;
    bool bShouldDraw = true;
    bool bOver = false;


    int num_prey = 10;
    int num_predators = 10;


    bool bAllPreyDead = false;
    bool bAllPredatorsDead = false;


    vector<Food*> foodVector;








    sf::Text Iteration_Counter;




    bool bBatchTest = false;
    bool bSoloTest = false;


    Environment()
    {
        if (NUM_ITERATIONS > 0)
            bShouldDraw = true;
        else
            bShouldDraw = true;

        Iteration_Counter.setPosition(100, 100);

 //       Iteration_Counter.setFont(font); // font is a sf::Font
    //       Iteration_Counter.setString(to_string(NUM_ITERATIONS));
        Iteration_Counter.setCharacterSize(50); // in pixels, not points!
        Iteration_Counter.setFillColor(sf::Color::Blue);
    //    Iteration_Counter.setStyle(sf::Text::Bold | sf::Text::Underlined);





        for (int i = 0; i < num_prey; i++)
        {
            preyVector.push_back(new Prey(NUM_EYES));


        }

        for (int i = 0; i < num_predators; i++)
        {
            predatorVector.push_back(new Predator(NUM_EYES));

        }

        for (int i = 0; i < num_prey; i++)
        {
            for (int j = 0; j < num_predators; j++)
                preyVector[i]->chasingPredator.push_back(&predatorVector[j]->shape);

            cout << num_prey;
        }

        

        for (int i = 0; i < num_predators; i++)
        {
            predatorVector[i]->chasedPrey = preyVector;
        }
    }


    void InitializeTest()
    {
        for (int i = 0; i < num_prey; i++)
        {
            preyVector[i]->bCaught = false;
            preyVector[i]->shape.setPosition(Vector2f(700, 700));
            preyVector[i]->fitness = 0;
            preyVector[i]->shape.setRotation(0);
        }

        for (int i = 0; i < num_predators; i++)
        {
            predatorVector[i]->bCaught = false;
            predatorVector[i]->shape.setPosition(Vector2f(200, 200));
            predatorVector[i]->fitness = 0;
            predatorVector[i]->shape.setRotation(0);
        }

        timeElapsed = 0;
        bCaught = false;
        bTimedOut = false;

        NUM_ITERATIONS++;
    }

	void Run()
	{
        for (int i = 0; i < num_prey; i++)
        {
            if (preyVector[i]->bCaught)
                preyVector[i]->Die();
        }

        for (int i = 0; i < num_prey; i++)
        {
            if (!preyVector[i]->bCaught) //if prey not caught, i.e. still alive
            {
                bAllPreyDead = false;
            }
        }

        for (int i = 0; i < num_predators; i++)
        {
            if (!predatorVector[i]->bCaught) //if prey not caught, i.e. still alive
            {
                bAllPredatorsDead = false;
            }
        }

        if (bAllPredatorsDead || bAllPreyDead)
        {
            cout << "yo";
    //        bTimedOut = true;
            bOver = true;
            End();
        }


        if (!bCaught && !bTimedOut)
        {
            if (timeElapsed > TEST_Duration)
            {
                bTimedOut = true;
                return;
            }
            if (bTimedOut)
            {
           //     for(int i=0;i<prey.size();i++)
           //         if(!prey[i]->bCaught)
           //             prey[i]->fitness += 10000;
                return;
            }

    //        for (int i = 0; i < preyVector.size(); i++)
          //      if (!preyVector[i]->bCaught)
              //      preyVector[i]->fitness++;

   //         for (int i = 0; i < predatorVector.size(); i++)
      //          predatorVector[i]->fitness--;

            if (timeElapsed % 300 == 0)
            {
                GenerateFood();

            }
            vector<CircleShape*> foodVec;
            for (int prey_i = 0; prey_i < num_prey; prey_i++)
            {
                for (int food_i = 0; food_i < foodVector.size(); food_i++)
                {
                    foodVec.push_back(&(foodVector[food_i]->shape));
                }
                preyVector[prey_i]->foodVector = foodVec;
                foodVec.clear();



         //       preyVector[prey_i]->fitness += 1; // fitness increment;

                preyVector[prey_i]->Behave();

                    if (bShouldDraw)
                    {
                        window->draw(preyVector[prey_i]->shape);
                        for (int i = 0; i < preyVector[prey_i]->num_eyes; i++)
                        {
                            window->draw(preyVector[prey_i]->rays[i].line);
                        }
                    }

                    for (int predator_i = 0; predator_i < num_predators; predator_i++)
                    {
                        if (preyVector[prey_i]->shape.getGlobalBounds().intersects(predatorVector[predator_i]->shape.getGlobalBounds()))
                        {
                    //        predator[predator_i]->fitness += 100000; //predator gets a big reward if he catches prey
                            preyVector[prey_i]->bCaught = true;
                            preyVector[prey_i]->fitness -= 1000;
                            predatorVector[predator_i]->fitness += 1000;
                            predatorVector[predator_i]->bCaught = true;

                        }
                    }


                    //food foraging stuff
                    for(int food_i = 0; food_i <foodVector.size(); food_i++)
                    {
                        if (preyVector[prey_i]->shape.getGlobalBounds().intersects(foodVector[food_i]->shape.getGlobalBounds()))
                        {
                            //rewards prey
                            preyVector[prey_i]->fitness += 1000;

                            //destroys food
                            foodVector.erase(foodVector.begin() + food_i);
                        }
                    }

            }

            for (int predator_i = 0; predator_i < num_predators; predator_i++)
            {
                predatorVector[predator_i]->Behave();

                if (bShouldDraw)
                {
                    window->draw(predatorVector[predator_i]->shape);
                    for (int i = 0; i < predatorVector[predator_i]->num_eyes; i++)
                        window->draw(predatorVector[predator_i]->rays[i].line);

                }
            }



            timeElapsed++;
        }
        else
        {
            bOver = true;
            End();
        }


        for (int i = 0; i < foodVector.size(); i++)
        {
            window->draw(foodVector[i]->shape);
        }


        // inside the main loop, between window.clear() and window.display()
  //      Iteration_Counter.setString(to_string(NUM_ITERATIONS));
        Iteration_Counter.setString(to_string(NUM_ITERATIONS));
        window->draw(Iteration_Counter);
	}

    void GenerateFood()
    {
        foodVector.push_back(new Food());
        foodVector[foodVector.size() - 1]->shape.setPosition(Vector2f(rand() % 1000,rand() % 1000));
    }

    void End()
    {
        if(bBatchTest)
            RunGeneticAlgorithm(preyVector,predatorVector,preyVector,predatorVector);

        if (bSoloTest)
        {
            for (int i = 0; i < preyVector.size(); i++)
            {
                preySoloVector.push_back(preyVector[i]);
            }
            for (int i = 0; i < predatorVector.size(); i++)
            {
                predatorSoloVector.push_back(predatorVector[i]);
            }


            if (NUM_ITERATIONS % 10 == 0) //change 10 to number_of_runs or something
            {
                RunGeneticAlgorithm(preySoloVector, predatorSoloVector, preyVector, predatorVector);
                preySoloVector.clear();
                predatorSoloVector.clear();
                foodVector.clear();
            }
            else
            {
                InitializeTest();
                bOver = false;
            }
        }

    }

    void RunGeneticAlgorithm(vector<Prey*> &prey,vector<Predator*> &predator, vector<Prey*>& destPrey, vector<Predator*>& destPredator)
    {
        vector<Prey*> sortedPrey;
        vector<Predator*> sortedPredators;

        vector<Prey*> newPrey;
        vector<Predator*> newPredators;

        Prey preyA(NUM_EYES);
        Prey preyB(NUM_EYES);
        Predator predatorA(NUM_EYES);
        Predator predatorB(NUM_EYES);

        PreyTable preyTable;
        PredatorTable predatorTable;
        int current_env_index = 0;

        bool bAllTestsOver;

        cout << "not even started";

        for (int l = 0; l < 1; l++) //get rid of this loop entirely
        {
            for (int prey_i = 0; prey_i < prey.size(); prey_i++)
                preyTable.Add(prey[prey_i], prey[prey_i]->fitness);
            for (int predator_i = 0; predator_i < prey.size(); predator_i++)
                predatorTable.Add(predator[predator_i], predator[predator_i]->fitness);


            preyTable.Sort();
            predatorTable.Sort();
            sortedPrey = preyTable.getTable();
            sortedPredators = predatorTable.getTable();

            cout << "sorted";

            //Perform Roulette Wheel Selections and obtain new weights by crossing over using the genetic algorithm.
            for (int i = 0; i < sortedPrey.size(); i += 2)
            {
                preyA = rouletteWheel(sortedPrey, preyTable.fitness_sum);
                preyB = rouletteWheel(sortedPrey, preyTable.fitness_sum);
                ChildrenPair children = GeneticAlgorithm::Crossover(preyA.gene, preyB.gene);
                //               newPrey.push_back(Prey(NUM_EYES));
                newPrey.push_back(new Prey(NUM_EYES));
                newPrey[i]->brain.SetWeights(children.gene1.weights);
                int ki = i + 1;
                if ((ki) < sortedPrey.size())
                {
                    newPrey.push_back(new Prey(NUM_EYES));
                    //            newPrey.push_back(Prey(NUM_EYES));
                    newPrey[ki]->brain.SetWeights(children.gene2.weights);
                }
            }

            cout << "rouletted";

            //Update existing brains with the new values
            for (int i = 0; i < newPrey.size(); i++)
            {
                for (int prey_i = 0; prey_i < destPrey.size(); prey_i++)
                {
                    destPrey[prey_i]->fitness = 0;
                    destPrey[prey_i]->brain.SetWeights(newPrey[i]->brain.GetWeights());
                }

                cout << "prey updated";

            }
            //PREDATOR GOES HERE

            //Perform Roulette Wheel Selections and obtain new weights by crossing over using the genetic algorithm.
            for (int i = 0; i < sortedPredators.size(); i += 2)
            {
                predatorA = rouletteWheelpred(sortedPredators, predatorTable.fitness_sum);
                predatorB = rouletteWheelpred(sortedPredators, predatorTable.fitness_sum);
                ChildrenPair children = GeneticAlgorithm::Crossover(predatorA.gene, predatorB.gene);
                newPredators.push_back(new Predator(NUM_EYES));
                //           newPredators[i] = sortedPredators[i];
                newPredators[i]->brain.SetWeights(children.gene1.weights);
                if ((i + 1) < sortedPredators.size())
                {
                    newPredators.push_back(new Predator(NUM_EYES));
                    //              newPredators[i] = sortedPredators[i];
                    newPredators[i + 1]->brain.SetWeights(children.gene2.weights);
                }
            }
            //Update existing brains with the new values
            for (int i = 0; i < newPredators.size(); i++)
            {
                for (int predator_i = 0; predator_i < destPredator.size(); predator_i++)
                {

                    destPredator[predator_i]->fitness = 0;
                    destPredator[predator_i]->brain.SetWeights(newPredators[i]->brain.GetWeights());

                }
            }


            cout<<"predator updated";



            current_env_index = 0;
            preyTable.clear();
            predatorTable.clear();
            sortedPrey.clear();
            sortedPredators.clear();
            newPrey.clear();
            newPredators.clear();

            bOver = false;

            InitializeTest();
        }

    }
    
};
#endif