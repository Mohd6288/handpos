#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Hand.h"

// Corrected port numbers
#define RECEIVE_PORT 9129
#define SEND_PORT 8080

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    Hand hand;
};
