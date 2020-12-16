// EyeEvolution.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Environment.h"
#include "FitnessTables.h"

int main()
{
    int NUM_EYES = 2; //also a property in evironment.h, you need to merge them



    vector<Prey*> sortedPrey;
    vector<Predator*> sortedPredators;

    vector<Prey*> newPrey;
    vector<Predator*> newPredators;

    Prey preyA(NUM_EYES);
    Prey preyB(NUM_EYES);
    Predator predatorA(NUM_EYES);
    Predator predatorB(NUM_EYES);

    srand((unsigned int)time(NULL)); //necessary otherwise you'll get something like 0.71717277 every time.

    PreyTable preyTable;
    PredatorTable predatorTable;
    int current_env_index = 0;

    bool bAllTestsOver;

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::Clock clock;

    const int NUM_ENVIRONMENTS = 1;

    Environment env[NUM_ENVIRONMENTS];

    Environment environd;

 /*   for (int i = 0; i < NUM_ENVIRONMENTS; i++)
    {
        env[i] = Environment();
        env[i].window = &window;
    }


*/

    environd = Environment();
    environd.window = &window;






    sf::Font font;



    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
    }


    /*

    Iteration_Counter.setPosition(100, 100);

    Iteration_Counter.setFont(font); // font is a sf::Font
//       Iteration_Counter.setString(to_string(NUM_ITERATIONS));
    Iteration_Counter.setCharacterSize(50); // in pixels, not points!
    Iteration_Counter.setFillColor(sf::Color::Blue);
    Iteration_Counter.setStyle(sf::Text::Bold | sf::Text::Underlined);
    Iteration_Counter.setString("yo");


    */









    while (window.isOpen())
    {
        //get time
        sf::Time elapsed = clock.getElapsedTime();







        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

   //     window.draw(Iteration_Counter);

        environd.Iteration_Counter.setFont(font);
        environd.Run();
        

        if (environd.bOver)
        {
            environd.InitializeTest();
        }
        

        
        
        //ASynchronous Environment run HERE!!!!!

   /*     for (int i = 0; i < NUM_ENVIRONMENTS; i++)
        {
                env[i].Run();
        }


        

        bAllTestsOver = true;
        for (int i = 0; i < NUM_ENVIRONMENTS; i++)
        {
            if (env[i].bOver == false)
                bAllTestsOver = false;
        }
        if(bAllTestsOver)
        {
            for (int i = 0; i < NUM_ENVIRONMENTS; i++)
            {
                for(int prey_i = 0;prey_i<env[i].num_prey;prey_i++)
                    preyTable.Add(env[i].prey[prey_i], env[i].prey[prey_i]->fitness);
                for (int predator_i = 0; predator_i < env[i].num_prey; predator_i++)
                    predatorTable.Add(env[i].predator[predator_i], env[i].predator[predator_i]->fitness);


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
                    for (int prey_i = 0; prey_i < env[i].num_prey; prey_i++)
                    {
                        env[i].prey[prey_i]->fitness = 0;
                        env[i].prey[prey_i]->brain.SetWeights(newPrey[i]->brain.GetWeights());
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
                    for (int predator_i = 0; predator_i < env[i].num_prey; predator_i++)
                    {

                        env[i].predator[predator_i]->fitness = 0;
                        env[i].predator[predator_i]->brain.SetWeights(newPredators[i]->brain.GetWeights());

                    }
                }






                current_env_index = 0;
                preyTable.clear();
                predatorTable.clear();
                sortedPrey.clear();
                sortedPredators.clear();
                newPrey.clear();
                newPredators.clear();

                env[i].bOver = false;

                env[i].InitializeTest();
            }
        }



        */

        


































        

/*

        //Synchronous Environment Run HERE!!!!!

        if (current_env_index < NUM_ENVIRONMENTS)
        {
            if (!env[current_env_index].bCaught && !env[current_env_index].bTimedOut)
                env[current_env_index].Run();
            else
            {
                preyTable.Add(env[current_env_index].prey, env[current_env_index].prey->fitness);
                predatorTable.Add(env[current_env_index].predator, env[current_env_index].predator->fitness);
                current_env_index++;
            }
        }
        else
        {
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
                env[i].prey->fitness = 0;
                env[i].prey->brain.SetWeights(newPrey[i]->brain.GetWeights());


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
                env[i].predator->fitness = 0;
                env[i].predator->brain.SetWeights(newPredators[i]->brain.GetWeights());


            }

            
            

            

            current_env_index = 0;
            preyTable.clear();
            predatorTable.clear();
            sortedPrey.clear();
            sortedPredators.clear();
            newPrey.clear();
            newPredators.clear();

            for (int i = 0; i < NUM_ENVIRONMENTS; i++)
                env[i].InitializeTest();



        }

        cout << preyTable.data.size()<<"\n";

        
        */


        window.display();
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
