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

	vector<Prey*> prey;
	vector<Predator*> predator;
    sf::RenderWindow* window;
    int NUM_EYES = 2;
    int timeElapsed = 0;
    int TEST_Duration = 3099;
    bool bShouldDraw = true;
    bool bOver = false;


    int num_prey = 10;
    int num_predators = 10;


    bool bAllPreyDead = false;
    bool bAllPredatorsDead = false;


    vector<Food*> foodVector;








    sf::Text Iteration_Counter;





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
            prey.push_back(new Prey(NUM_EYES));


        }

        for (int i = 0; i < num_predators; i++)
        {
            predator.push_back(new Predator(NUM_EYES));

        }

        for (int i = 0; i < num_prey; i++)
        {
            for (int j = 0; j < num_predators; j++)
                prey[i]->chasingPredator.push_back(&predator[j]->shape);

            cout << num_prey;
        }

        

        for (int i = 0; i < num_predators; i++)
        {
                predator[i]->chasedPrey = prey;
        }
    }


    void InitializeTest()
    {
        for (int i = 0; i < num_prey; i++)
        {
            prey[i]->bCaught = false;
            prey[i]->shape.setPosition(Vector2f(700, 700));
            prey[i]->fitness = 0;
        }

        for (int i = 0; i < num_predators; i++)
        {
            predator[i]->shape.setPosition(Vector2f(200, 200));
            predator[i]->fitness = 0;
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
            if (prey[i]->bCaught)
                prey[i]->Die();
        }

        for (int i = 0; i < num_prey; i++)
        {
            if (!prey[i]->bCaught) //if prey not caught, i.e. still alive
            {
                bAllPreyDead = false;
            }
        }

        for (int i = 0; i < num_predators; i++)
        {
            if (!predator[i]->bCaught) //if prey not caught, i.e. still alive
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

            for (int i = 0; i < prey.size(); i++)
                if (!prey[i]->bCaught)
                    prey[i]->fitness++;

            for (int i = 0; i < predator.size(); i++)
                 predator[i]->fitness--;

            if (timeElapsed % 300 == 0)
            {
         //       GenerateFood();
            }

            for (int prey_i = 0; prey_i < num_prey; prey_i++)
            {
                prey[prey_i]->fitness += 1; // fitness increment;

                    prey[prey_i]->Behave();

                    if (bShouldDraw)
                    {
                        window->draw(prey[prey_i]->shape);
                        for (int i = 0; i < prey[prey_i]->num_eyes; i++)
                        {
                            window->draw(prey[prey_i]->rays[i].line);
                        }
                    }

                    for (int predator_i = 0; predator_i < num_predators; predator_i++)
                    {
                        if (prey[prey_i]->shape.getGlobalBounds().intersects(predator[predator_i]->shape.getGlobalBounds()))
                        {
                    //        predator[predator_i]->fitness += 100000; //predator gets a big reward if he catches prey
                            prey[prey_i]->bCaught = true;
                            predator[predator_i]->fitness+= 50;
                            predator[predator_i]->bCaught = true;

                        }
                    }
            }

            for (int predator_i = 0; predator_i < num_predators; predator_i++)
            {
          //      predator[predator_i]->fitness -= 1; //fitness decrement
                predator[predator_i]->Behave();

                if (bShouldDraw)
                {
                    window->draw(predator[predator_i]->shape);
                    for (int i = 0; i < predator[predator_i]->num_eyes; i++)
                        window->draw(predator[predator_i]->rays[i].line);

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
        RunGeneticAlgorithm();
    }

    void RunGeneticAlgorithm()
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


        for (int i = 0; i < 1; i++) //get rid of this loop entirely
        {
            for (int prey_i = 0; prey_i < num_prey; prey_i++)
                preyTable.Add(prey[prey_i], prey[prey_i]->fitness);
            for (int predator_i = 0; predator_i < num_prey; predator_i++)
                predatorTable.Add(predator[predator_i], predator[predator_i]->fitness);


            preyTable.Sort();
            predatorTable.Sort();
            sortedPrey = preyTable.getTable();
            sortedPredators = predatorTable.getTable();



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
            //Update existing brains with the new values
            for (int i = 0; i < newPrey.size(); i++)
            {
                for (int prey_i = 0; prey_i < num_prey; prey_i++)
                {
                    prey[prey_i]->fitness = 0;
                    prey[prey_i]->brain.SetWeights(newPrey[i]->brain.GetWeights());
                }


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
                for (int predator_i = 0; predator_i < num_prey; predator_i++)
                {

                    predator[predator_i]->fitness = 0;
                    predator[predator_i]->brain.SetWeights(newPredators[i]->brain.GetWeights());

                }
            }






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