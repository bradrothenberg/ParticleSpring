#pragma once
#include "Particle.h"
#include "cinder/gl/gl.h"

class Spring{
public:
	Spring(Particle* A, Particle* B, float rest, float strength);

	void update();
	void draw()const;

private:
	Particle* mParticleA;
	Particle* mParticleB;
	float mStrength, mRest;
};

