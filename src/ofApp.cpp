#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(45);
    ofSetBackgroundColor(0, 0, 0);
    hand.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
   
    hand.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    //screen frame rate
    hand.draw();
}
