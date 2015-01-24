#include "Particle.h"

Particle::Particle(const ci::Vec2f& position, float radius, float mass, float drag) :
mPosition(position), mRadius(radius), mMass(mass), mDrag(drag){

	mPrevPostion = position;
	mForces = ci::Vec2f::zero();
}

void Particle::update(){
	auto temp = mPosition;
	auto vel = (mPosition - mPrevPostion)*mDrag;
	mPosition += vel + mForces / mMass;
	mPrevPostion = temp;

	mForces = ci::Vec2f::zero();
}

void Particle::draw()const{
	ci::gl::drawSolidCircle(mPosition, mRadius);
}