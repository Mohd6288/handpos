#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Particle.h"



// Corrected port numbers
#define RECEIVE_PORT 9129
#define SEND_PORT 8080

class Hand {
public:
    void setup();
    void update();
    void processHandMessage(const ofxOscMessage& message);
    void draw();
    //void updateVelocity();

    void displayHandSpeed();

    void displayFingerNames();

    void drawBox();

    void drawLanmarks();
    
    ofxOscReceiver receiver;
    // ofxOscSender sender; // Uncomment if you're sending messages
    // Method to get the bounding box of the hand
    pair<glm::vec2, glm::vec2> getBoundingBox(const std::vector<glm::vec2>& handLandmarks);

    vector<glm::vec2> leftHandLandmarks;
    vector<glm::vec2> rightHandLandmarks;
    
    float animationDuration = 0.5; // Duration of animation in seconds
    // Linear interpolation function for smooth transitions


    vector<glm::vec2> prevLeftHandLandmarks;
    vector<glm::vec2> prevRightHandLandmarks;

    glm::vec2 prevLeftHandCentroid, prevRightHandCentroid;
    glm::vec2 leftHandVelocity, rightHandVelocity;

    vector<Particle> particles;

};


