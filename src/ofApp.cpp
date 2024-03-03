#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    cam.setup(ofGetWidth(), ofGetHeight()); // Set the camera resolution
    hand.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
    cam.update(); // Update the camera feed
    hand.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0); // Clear the background to black
    cam.draw(0, 0); // Draw the camera feed
    hand.draw();
}
