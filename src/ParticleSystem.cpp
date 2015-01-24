#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem(){
	for (auto it = begin(mParticles);it!=end(mParticles);++it){
		delete *it;
	}
	mParticles.clear();
}

void ParticleSystem::update(){
	for (auto&p : mParticles){
		p->update();
	}

	for (auto&s : mSprings){
		s->update();
	}
}

void ParticleSystem::draw()const{
	for (auto&p : mParticles){
		p->draw();
	}

	for (auto&s : mSprings){
		s->draw();
	}
}


void ParticleSystem::destroyParticle(Particle* particle){
	auto it = std::find(begin(mParticles), end(mParticles), particle);

	delete *it;
	mParticles.erase(it);
}

void ParticleSystem::destroySpring(Spring* spring){
	auto it = std::find(begin(mSprings), end(mSprings), spring);

	delete *it;
	mSprings.erase(it);
}