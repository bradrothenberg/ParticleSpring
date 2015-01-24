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
};

void ParticleSpringApp::setup()
{
	int count = 100;

	for (auto i = 0; i < count; ++i){
		auto x = ci::randFloat(0.0f, getWindowWidth());
		auto y = ci::randFloat(0.0f, getWindowHeight());

		auto rad = ci::randFloat(5.0f, 15.0f);
		auto mass = rad; 
		auto drag = .95f;

		Particle* p = new Particle(Vec2f(x, y), rad, mass, drag);
		mParticleSystem.addParticle(p);
	}
}

void ParticleSpringApp::mouseDown( MouseEvent event )
{
	auto particleA = mParticleSystem.getParticles()[randInt(mParticleSystem.getParticles().size())];
	auto particleB = particleA;

	while (particleB == particleA){
		particleB = mParticleSystem.getParticles()[randInt(mParticleSystem.getParticles().size())];
	}

	auto rest = randFloat(100.0f, 200.0f);
	auto strength = 1.0f;

	Spring* spring = new Spring(particleA, particleB, rest, strength);
	mParticleSystem.addSpring(spring);
}

void ParticleSpringApp::update()
{
	mParticleSystem.update();
}

void ParticleSpringApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::setMatricesWindow(getWindowWidth(), getWindowHeight());
	mParticleSystem.draw();
}

CINDER_APP_NATIVE( ParticleSpringApp, RendererGl )
