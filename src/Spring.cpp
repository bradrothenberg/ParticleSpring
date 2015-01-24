#include "Spring.h"

Spring::Spring(Particle* A, Particle* B, float rest, float strength):
mParticleA(A),mParticleB(B),mRest(rest),mStrength(strength){

}

void Spring::update(){

	auto delta = mParticleA->getPosition() - mParticleB->getPosition();
	auto length = delta.length();
	auto invMassA = 1.0f / mParticleA->getMass();
	auto invMassB = 1.0f / mParticleB->getMass();

	float normDist = (length - mRest) / (length*(invMassA + invMassB))*mStrength;
	mParticleA->addVelocity(-(delta*normDist*invMassA));
	mParticleB->addVelocity(delta*normDist*invMassA);
}

void Spring::draw()const{
	ci::gl::drawLine(mParticleA->getPosition(), mParticleB->getPosition());
}