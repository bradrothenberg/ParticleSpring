#pragma once
#include "Particle.h"
#include <vector>
#include "Spring.h"

class ParticleSystem{
public:
	~ParticleSystem();

	void update();
	void draw()const;

	void addParticle(Particle* particle){ mParticles.push_back(particle); }
	void destroyParticle(Particle* particle);

	void addSpring(Spring* spring){ mSprings.push_back(spring); }
	void destroySpring(Spring* spring);

	const std::vector<Particle*>& getParticles()const{ return mParticles; }
	const std::vector<Spring*>& getSprings()const{ return mSprings; }
private:
	std::vector<Particle*> mParticles;
	std::vector<Spring*> mSprings;
};

