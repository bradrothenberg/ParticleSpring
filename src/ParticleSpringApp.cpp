#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "ParticleSystem.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticleSpringApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	ParticleSystem mParticleSystem;
	Vec2f mLeftCorner, mRightCorner;
	int mRows, mCols;
};

void ParticleSpringApp::setup()
{
	mLeftCorner = Vec2f{ 50.0f, 50.0f };
	mRightCorner = Vec2f{ getWindowWidth() - 50.0f, 50.0f };
	mRows = 5;
	mCols = 4;

	auto gap = (mRightCorner.x - mLeftCorner.x) / (mRows - 1);

	auto count = 0;
	for (auto i = 0; i < mRows; ++i){
		for (auto j = 0; j < mCols; ++j){
			auto x = mLeftCorner.x + (gap*i);
			auto y = mLeftCorner.y + (gap*j);

			auto* particle = new Particle(Vec2f{ x, y }, 5.0f, 5.0f, .95f);
			particle->setIsFixed(false);
			mParticleSystem.addParticle(particle);
			if ( j!=0){
				auto partA = mParticleSystem.getParticles()[count];
				auto partB = mParticleSystem.getParticles()[count-1];
				auto rest = partA->getPosition().distance(partB->getPosition());
				auto* spring = new Spring{ partA, partB, rest, 1.0f };
				mParticleSystem.addSpring(spring);

			}
			count++;
		}
	}


	for (auto i = 0; i < mRows-1; ++i){
		for (auto j = 0; j < mCols; ++j){
			auto indexA = i*mCols + j;
			auto indexB = i*mCols + j+mCols;

			auto partA = mParticleSystem.getParticles()[indexA];
			auto partB = mParticleSystem.getParticles()[indexB];

			auto rest = partA->getPosition().distance(partB->getPosition());

			auto* spring = new Spring{ partA, partB, rest, 1.0f };
			mParticleSystem.addSpring(spring);
		}
	}

	mParticleSystem.getParticles()[0]->setIsFixed(true);
	mParticleSystem.getParticles()[(mRows-1) * mCols]->setIsFixed(true);
}

void ParticleSpringApp::mouseDown( MouseEvent event )
{
// 	auto particleA = mParticleSystem.getParticles()[randInt(mParticleSystem.getParticles().size())];
// 	auto particleB = particleA;
// 
// 	while (particleB == particleA){
// 		particleB = mParticleSystem.getParticles()[randInt(mParticleSystem.getParticles().size())];
// 	}
// 
// 	auto rest = randFloat(100.0f, 200.0f);
// 	auto strength = 1.0f;
// 
// 	Spring* spring = new Spring(particleA, particleB, rest, strength);
// 	mParticleSystem.addSpring(spring);
}

void ParticleSpringApp::update()
{
	mParticleSystem.update();

	auto gravity = Vec2f{ 0.0f, 1.0f };
	for (auto p : mParticleSystem.getParticles()){
		p->addForce(gravity);
	}


}

void ParticleSpringApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::setMatricesWindow(getWindowWidth(), getWindowHeight());
	mParticleSystem.draw();
}

CINDER_APP_NATIVE( ParticleSpringApp, RendererGl )
