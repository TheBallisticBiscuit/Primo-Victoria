#ifndef _PARTICLE_MANAGER_H                // Prevent multiple definitions if this 
#define _PARTICLE_MANAGER_H                // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "particle.h"
#include "constants.h"
#include "textureManager.h"

class ParticleManager
{
	private:
	Particle particles[MAX_NUMBER_PARTICLES];
	VECTOR2 velocity; //all particles created using SetVisibleNParticles() will use this velocity
	VECTOR2 position; //all particles created using SetVisibleNParticles() will use this position
	TextureManager tm;

	float ParticleManager::getVariance();// returns a number between 50% and 150% for particle variance

public:
	ParticleManager();
	~ParticleManager();
	void ParticleManager::setInvisibleAllParticles();
	void ParticleManager::setVisibleNParticles(int n, bool isBlood);
	void ParticleManager::setPosition(VECTOR2 pos) {position = pos;}
	void ParticleManager::setVelocity(VECTOR2 vel) {velocity = vel;}
	bool ParticleManager::initialize(Graphics *g, const char filename[], int width, int height, int ncols);
	void ParticleManager::setScale(float newScale);
	void ParticleManager::setFrames(int startFrame, int endFrame);
	void ParticleManager::setFrameDelay(float delay);
	void ParticleManager::setMaxTimeAlive(float t);
	void ParticleManager::setRotation(float rotation);
	void ParticleManager::setFade(float fade);
	void ParticleManager::createParticleEffect(VECTOR2 pos, VECTOR2 vel, int numParticles, bool isBlood);
	void ParticleManager::update(float frametime, bool isRotate);
	void ParticleManager::draw(bool isFade);


};







#endif _PARTICLE_MANAGER_H