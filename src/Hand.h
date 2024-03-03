#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


// Corrected port numbers
#define RECEIVE_PORT 9129
#define SEND_PORT 8080

class Hand {
public:
    void setup();
    void update();
    void processHandMessage(const ofxOscMessage& message);
    void draw();
    
    ofxOscReceiver receiver;
    // ofxOscSender sender; // Uncomment if you're sending messages
    // Method to get the bounding box of the hand
    std::pair<glm::vec2, glm::vec2> getBoundingBox(const std::vector<glm::vec2>& handLandmarks);

    std::vector<glm::vec2> leftHandLandmarks;
    std::vector<glm::vec2> rightHandLandmarks;
    
    float animationDuration = 0.5; // Duration of animation in seconds
};


