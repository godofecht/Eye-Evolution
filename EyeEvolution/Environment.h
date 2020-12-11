#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#pragma once
#include "prey.h"
#include "predator.h"
#include <SFML/Graphics.hpp>


class Environment
{
public:



	Prey* prey;
	Predator* predator;
    sf::RenderWindow* window;
	Environment()
	{
		prey = new Prey(5); predator = new Predator(5);
		predator->chasedPrey = prey;
	}

	void Run()
	{
        window->draw(predator->shape);
        for (int i = 0; i < predator->num_eyes; i++)
            window->draw(predator->rays[i].line);

        predator->Behave();


        if (prey != NULL)
        {
            prey->Behave();
            window->draw(prey->shape);
            for (int i = 0; i < 4; i++)
            {
                window->draw(prey->rays[i].line);
            }



            if (prey->shape.getGlobalBounds().intersects(predator->shape.getGlobalBounds()))
            {
            //    preyTable.Add(*prey, prey->fitness);

                //          cout << "prey eaten";
                 //         prey = NULL;

            }
        }
	}
};





#endif