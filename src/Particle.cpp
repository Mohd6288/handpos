// Particle.cpp
#include "Particle.h"


Particle::Particle(glm::vec2 startPos, glm::vec2 startVel, float life, ofColor startColor, float startSize)
    : position(startPos), velocity(startVel), lifespan(life), color(startColor), size(startSize) {}

void Particle::update() {
    position += velocity;
    lifespan -= 1.0; // Decrease lifespan each frame
    size *= 0.98; // Gradually decrease size
    color = color.lerp(ofColor(255, 0, 0), 0.03); // Slowly shift color towards red
    velocity.x += ofRandom(-1, 1); // Add some horizontal drift
    velocity.y -= 0.1; // Make the particle move up
}

void Particle::draw() {
    if (lifespan > 0) {
        ofSetColor(color);
        ofDrawCircle(position.x, position.y, size);
    }
}

bool Particle::isDead() {
    return lifespan <= 0;
}
