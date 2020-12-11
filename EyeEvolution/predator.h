#ifndef PREDATOR_H
#define PREDATOR_H

#include<SFML/Graphics/Shape.hpp>
#include "RayCast.h"
#include <math.h>
#include "model.h"
#include <SFML\Graphics\CircleShape.hpp>

using namespace sf;

class Predator
{
public:
	CircleShape shape;

	vector<Ray> rays; //one for left eye, one for right
	Hit* hit; //might be worth combining ray and hit

	float distFromDestination;

	Model brain;

	Vector2f position;

	Gene gene;

	Prey* chasedPrey;


	int num_eyes;

	double fitness = 0;

	Predator(int numEyes)
	{
		hit = new Hit[numEyes];

		num_eyes = numEyes;
		shape.setFillColor(Color::Red);
		for (int i = 0; i < numEyes; i++)
		{
			rays.push_back(Ray());
		}


		//starting position
		position = Vector2f(300, 300);

		distFromDestination = pow(pow(shape.getPosition().x, 2) + pow(shape.getPosition().y, 2), 1 / 2);



		shape.setRadius(12);
//		shape.setFillColor(Color(300, 300, 300));
		shape.setPosition(position);
		shape.setOrigin(Vector2f(shape.getRadius(), shape.getRadius()));
		shape.setRotation(45);


		//brain stuff
		vector<unsigned> brain_topology;
		brain_topology.push_back(num_eyes);
		brain_topology.push_back(7);
		brain_topology.push_back(3);
		brain.SetTopology(brain_topology);
		brain.InitializeTopology();

		//Gene stuff
		gene.InitializeRandom(num_eyes, brain.GetWeights().size());
		//put weights from gene into prey
		brain.getNetwork()->PutWeights(gene.weights);
		//place eyes accordingly

	}

	Hit rayTrace(float angle)
	{
		double dist = 0;
		float correctedAngle;
		correctedAngle = shape.getRotation() + angle;
		sf::Vector2f rayPos(shape.getPosition().x, shape.getPosition().y);
		bool b_hit = false;

		for (float i = 1; i <= 200; i++)//number of iterations
		{
			rayPos.x += 1 * cos(correctedAngle * M_PI / 180);
			rayPos.y += 1 * sin(correctedAngle * M_PI / 180);
			dist += pow(pow(rayPos.x, 2) * pow(rayPos.y, 2), 1 / 2);
			if (chasedPrey->shape.getGlobalBounds().contains(rayPos))
			{
				b_hit = true;
			}


		}
		Hit newHitResult(b_hit, 0, rayPos);
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
		inputVector.clear();


		for (int i = 0; i < num_eyes; i++)
		{
			if (hit[i].bHit)
				inputVector.push_back(1);
			else
				inputVector.push_back(0);

		}

		movementVector = GetMovementVector(inputVector);
		double movementForward = movementVector[0];
		double rotation = movementVector[1] - movementVector[2];

		double rotationSpeed = 0.1;
		double positionSpeed = 0.1;

		shape.setRotation(shape.getRotation() + rotationSpeed * (rotation));
		shape.setPosition(shape.getPosition().x + positionSpeed * movementForward * cos(shape.getRotation() * M_PI / 180), shape.getPosition().y + positionSpeed * movementForward * sin(shape.getRotation() * M_PI / 180));

		for (int i = 0; i < num_eyes; i++)
		{
			hit[i] = rayTrace(360.0f * gene.eye_positions[i] + shape.getRotation());
		}
		for (int i = 0; i < num_eyes; i++)
		{
			rays[i].line.clear();
			rays[i].line.setPrimitiveType(Lines);
			rays[i].line.append(shape.getPosition());
			rays[i].line.append(hit[i].hitPos);
		}

		
		



	}
};
#endif