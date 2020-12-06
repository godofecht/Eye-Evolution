// EyeEvolution.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "prey.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::Clock clock;


    Prey prey;

    while (window.isOpen())
    {
        //get time
        sf::Time elapsed = clock.getElapsedTime();
     //   std::cout << elapsed.asSeconds()<<"\n";




        


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(prey.shape);
        prey.Behave();

       // SpritePopulation[i].hit[0] = SpritePopulation[i].rayTrace(0); SpritePopulation[i].rays[0].line.append(SpritePopulation[i].shape.getPosition()); SpritePopulation[i].rays[0].line.append(SpritePopulation[i].hit[0].hitPos);
        //we need to map the ray start and end to hit point

        for(int i=0;i<4;i++)
            window.draw(prey.rays[i].line);
     

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
