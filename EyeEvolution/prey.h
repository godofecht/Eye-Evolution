#include<SFML/Graphics/Shape.hpp>
#include "RayCast.h"
#include <math.h>

using namespace sf;

class Prey
{
public:
	sf::CircleShape shape;

	Ray rays[2]; //one for left eye, one for right
	Hit hit[2]; //might be worth combining ray and hit

	float distFromDestination;


	Prey()
	{
		distFromDestination = pow(pow(shape.getPosition().x, 2) + pow(shape.getPosition().y, 2), 1 / 2);



		shape.setRadius(30);
		shape.setFillColor(Color(300, 300, 300));
		shape.setPosition(Vector2f(300, 300));
		for (int i = 0; i < 2; i++)
		{
			rays[i].line.append(shape.getPosition());
		}
		shape.setOrigin(Vector2f(shape.getRadius(), shape.getRadius()));
		shape.setRotation(45);	
	}

	Hit rayTrace(float angle)
	{
		double dist = 0;
		float correctedAngle;
		correctedAngle = shape.getRotation() + angle;
		sf::Vector2f rayPos(shape.getPosition().x, shape.getPosition().y);

		for (float i = 1; i <= 200; i++)//number of iterations
		{
			rayPos.x += 1 * cos(correctedAngle * M_PI/ 180);
			rayPos.y += 1 * sin(correctedAngle * M_PI / 180);
			dist += pow(pow(rayPos.x, 2) * pow(rayPos.y, 2), 1 / 2);
		//	if (thisTrack->obstacles[j].polygon.getGlobalBounds().contains(rayPos))


		}
		Hit newHitResult(false, 0, rayPos);
		return newHitResult;
	}
};