#pragma once
#include <cinder/gl/gl.h>
#include <cinder/Vector.h>


class Particle{
public:
	Particle(const ci::Vec2f& position, float radius, float mass, float drag);

	void update();
	void draw()const;

	void addVelocity(const ci::Vec2f& vec);
	void addForce(const ci::Vec2f& vec){ mForces += vec; }
	const ci::Vec2f& getPosition()const{ return mPosition; }
	float getMass()const{ return mMass; }
	void setIsFixed(bool isFixed){ mIsFixed = isFixed; }
private:
	ci::Vec2f mPosition, mPrevPostion;
	ci::Vec2f mForces;
	float mRadius, mMass, mDrag;

	bool mIsFixed;
};
