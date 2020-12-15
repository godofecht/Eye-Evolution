#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#pragma once
#include "prey.h"
#include "predator.h"
#include <SFML/Graphics.hpp>


class Environment
{
public:

    bool bCaught = false;
    bool bTimedOut = false;

	Prey* prey;
	Predator* predator;
    sf::RenderWindow* window;

    int NUM_EYES = 2;

    int timeElapsed = 0;

    int TEST_Duration = 10999;


	Environment()
	{
		prey = new Prey(NUM_EYES); 
        predator = new Predator(NUM_EYES);
		predator->chasedPrey = prey;
        prey->chasingPredator = &predator->shape;
	}


    void InitializeTest()
    {
        prey->shape.setPosition(Vector2f(700, 700));
        predator->shape.setPosition(Vector2f(200, 200));

        timeElapsed = 0;
        bCaught = false;
        bTimedOut = false;
    }

	void Run()
	{

        if (timeElapsed > TEST_Duration)
        {
            bTimedOut = true;
            return;
        }
        if (bTimedOut)
        {
            prey->fitness += 10000;
            return;
        }
        prey->fitness += 1; // fitness increment;
        predator->fitness -= 1; //fitness decrement

        window->draw(predator->shape);
        for (int i = 0; i < predator->num_eyes; i++)
            window->draw(predator->rays[i].line);

        predator->Behave();


        if (prey != NULL)
        {
            prey->Behave();
            window->draw(prey->shape);
            for (int i = 0; i < prey->num_eyes; i++)
            {
                window->draw(prey->rays[i].line);
            }



            if (prey->shape.getGlobalBounds().intersects(predator->shape.getGlobalBounds()))
            {
                predator->fitness += 100; //predator gets a big reward if he catches prey
                bCaught = true;
                //          cout << "prey eaten";
                 //         prey = NULL;

            }
        }
        timeElapsed++;
	}
};





#endif