#include<SFML/Graphics/Shape.hpp>
#include "RayCast.h"
#include <math.h>
#include "model.h"

using namespace sf;

class Prey
{
public:
	sf::CircleShape shape;

	Ray rays[4]; //one for left eye, one for right
	Hit hit[4]; //might be worth combining ray and hit

	float distFromDestination;

	Model brain;

	Vector2f position;


	Prey()
	{
		rays[0] = Ray();
		rays[1] = Ray();
		rays[2] = Ray();
		rays[3] = Ray();

		//starting position
		position =  Vector2f(300, 300);

		distFromDestination = pow(pow(shape.getPosition().x, 2) + pow(shape.getPosition().y, 2), 1 / 2);



		shape.setRadius(30);
		shape.setFillColor(Color(300, 300, 300));
		shape.setPosition(position);
		shape.setOrigin(Vector2f(shape.getRadius(), shape.getRadius()));
		shape.setRotation(45);	


		//brain stuff
		vector<unsigned> brain_topology;
		brain_topology.push_back(2);
		brain_topology.push_back(4);
		brain.SetTopology(brain_topology);
		brain.InitializeTopology();
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

	vector<double> GetMovementVector(vector<double> iv)
	{
		vector<double> movementVector;
		brain.getNetwork()->feedForward(iv);
		movementVector = brain.GetResult();
		return movementVector;
	}

	void Behave()
	{



		vector<double> movementVector;
		vector<double> inputVector;

		inputVector.push_back(0.2);
		inputVector.push_back(0.2);

		movementVector = GetMovementVector(inputVector);
		double movementForward = movementVector[0];
		double rotation = movementVector[1];

		double rotationSpeed = 0.1;
		double positionSpeed = 0.1;

		shape.setRotation(shape.getRotation() + rotationSpeed * (rotation));
		shape.setPosition(shape.getPosition().x + positionSpeed * movementForward * cos(shape.getRotation() * M_PI / 180), shape.getPosition().y + positionSpeed *movementForward * sin(shape.getRotation() * M_PI / 180));

	//	hit[0] = rayTrace(0 + shape.getRotation());rays[0].line.append(shape.getPosition()); rays[0].line.append(hit[0].hitPos);
		

		hit[0] = rayTrace(-65 + shape.getRotation());
		hit[1] = rayTrace(-35 + shape.getRotation());
		hit[2] = rayTrace(35 + shape.getRotation());
		hit[3] = rayTrace(65 + shape.getRotation());

//		rays[0].line.append(sf::Vertex(shape.getPosition()));
//		rays[0].line.append(sf::Vertex(hit[0].hitPos));

		for (int i = 0; i < 4; i++)
		{
			rays[i].line.clear();
			rays[i].line.setPrimitiveType(Lines);
			rays[i].line.append(shape.getPosition());
			rays[i].line.append(hit[i].hitPos);
		}


		


	}
};