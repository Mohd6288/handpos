// Particle.h
#pragma once

#include "ofMain.h"

class Particle {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    float lifespan; // Lifespan in frames
    ofColor color; // Color of the particle
    float size; // Size of the particle

    Particle(glm::vec2 startPos, glm::vec2 startVel, float life, ofColor startColor, float startSize);

    void update();
    void draw();
    bool isDead();
};
