#include "particleManager.h"
#include <stdlib.h>
#include <time.h>
#include "graphics.h"

ParticleManager::ParticleManager()
{
	srand(time(NULL));
}
ParticleManager::~ParticleManager()
{
}
float ParticleManager::getVariance()
{
	float foo = (rand()%100 );
	foo /= 100.0f;
	foo += 0.5f;
	return foo;
}
void ParticleManager::setInvisibleAllParticles()
{
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		particles[i].setVisible(false);
		particles[i].setActive(false);
	}
}
void ParticleManager::setVisibleNParticles(int n, bool isBlood)
{
	int activatedParticles = 0;
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		if (!particles[i].getActive()) //found an inactive particle
		{
			particles[i].setActive(true);
			if(!isBlood){
				particles[i].setMaxTimeAlive(MAX_PARTICLE_LIFETIME*getVariance());
			}
			else{
				particles[i].setMaxTimeAlive(BLOOD_ANIMATION_DELAY*4);
			}
			float newX = 4*velocity.x * getVariance(); 
			float newY = 4*velocity.y  * getVariance();
			VECTOR2 v = VECTOR2(newX,newY);
			particles[i].setX(position.x);
			particles[i].setY(position.y);
			particles[i].setVelocity(v);
			particles[i].setVisible(true);
			activatedParticles++;
			if (activatedParticles == n)
				return;
		}
	}
}

bool ParticleManager::initialize(Graphics *g, const char filename[], int width, int height, int ncols)
{
	if (!tm.initialize(g, filename))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing particle texture"));
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		if (!particles[i].initialize(g, width, height, ncols,&tm))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing particles"));
		particles[i].setActive(false);
		particles[i].setVisible(false);
		particles[i].setRotationValue(pow(-1,rand()%2)*0.05f);
	}
	return true;
}

void ParticleManager::setScale(float newScale){
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		particles[i].setScale(newScale);
	}
}

void ParticleManager::setFrames(int startFrame, int endFrame){
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		particles[i].setFrames(startFrame, endFrame);
		particles[i].setCurrentFrame(startFrame);
	}
}

void ParticleManager::setFrameDelay(float delay){
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		particles[i].setFrameDelay(delay);
	}
}

void ParticleManager::createParticleEffect(VECTOR2 pos, VECTOR2 vel, int numParticles, bool isBlood){

	setPosition(pos);
	setVelocity(vel);
	setVisibleNParticles(numParticles, isBlood);

}

void ParticleManager::setMaxTimeAlive(float t) {
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++){
		particles[i].setMaxTimeAlive(t);
	}
}

void ParticleManager::setRotation(float rotation){
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++){
		particles[i].setRotationValue(rotation);
	}
}

void ParticleManager::setFade(float fade){
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++){
		particles[i].setFadeValue(fade);
	}
}

void ParticleManager::update(float frametime, bool isRotate)
{
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++){
		if (particles[i].getActive())
			particles[i].update(frametime, isRotate);

	}
}

void ParticleManager::draw(bool isFade)
{
	if(isFade){
		byte fadeAmount;
		COLOR_ARGB color;
		for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
		{
			if (!particles[i].getActive())
				continue;
			float foo = particles[i].getMaxTimeAlive();  //MAX_PARTICLE_LIFETIME;
			float bar = particles[i].getTimeAlive();
			float foobar = (foo-bar)/foo;
			fadeAmount = 255 * foobar;
			color = D3DCOLOR_ARGB(fadeAmount,fadeAmount,fadeAmount,fadeAmount);
			particles[i].draw(color);
			if (fadeAmount <= 20)
				particles[i].resetParticle();
		}
	}
	else{
		byte fadeAmount;
		for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
		{
			if (!particles[i].getActive())
				continue;
			float foo = particles[i].getMaxTimeAlive();  //MAX_PARTICLE_LIFETIME;
			float bar = particles[i].getTimeAlive();
			float foobar = (foo-bar)/foo;
			fadeAmount = 255 * foobar;
			particles[i].draw();
			if (fadeAmount <= 20)
				particles[i].resetParticle();
		}
	}
}

void ParticleManager::onLostDevice() {
	tm.onLostDevice();
}

void ParticleManager::onResetDevice() {
	tm.onResetDevice();
}
