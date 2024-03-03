#include "Hand.h"

void Hand::setup()
{
    receiver.setup(RECEIVE_PORT);
    ofLogToConsole();
    leftHandLandmarks.resize(21); // Prepare 21 landmarks for each hand
    rightHandLandmarks.resize(21);
}

/*
void Hand::update()
{
    ofxOscMessage message;
    while (receiver.hasWaitingMessages()) {
        receiver.getNextMessage(message);
        if (message.getAddress() == "/lx") {
            for (int i = 0; i < 21; ++i) {
                leftHandLandmarks[i].x = message.getArgAsFloat(i);
            }
        }
        else if (message.getAddress() == "/ly") {
            for (int i = 0; i < 21; ++i) {
                leftHandLandmarks[i].y = message.getArgAsFloat(i);
            }
        }
        else if (message.getAddress() == "/rx") {
            for (int i = 0; i < 21; ++i) {
                rightHandLandmarks[i].x = message.getArgAsFloat(i);
            }
        }
        else if (message.getAddress() == "/ry") {
            for (int i = 0; i < 21; ++i) {
                rightHandLandmarks[i].y = message.getArgAsFloat(i);
            }
        }
    }
}
*/

void Hand::update()
{
    ofxOscMessage message;
    while (receiver.hasWaitingMessages()) {
        receiver.getNextMessage(message); // This call dequeues the message

        // Efficiently process each message
        if (message.getAddress() == "/lx" || message.getAddress() == "/ly" ||
            message.getAddress() == "/rx" || message.getAddress() == "/ry") {
            processHandMessage(message); // Process the message immediately
        }
        // Any other message processing can go here
    }
    // No unprocessed messages are left in the queue after this point
}

void Hand::processHandMessage(const ofxOscMessage& message)
{
    std::vector<glm::vec2>* handLandmarks = nullptr;

    // Determine which hand the message is for and select the appropriate landmark vector
    if (message.getAddress() == "/lx" || message.getAddress() == "/ly") {
        handLandmarks = &leftHandLandmarks;
    }
    else if (message.getAddress() == "/rx" || message.getAddress() == "/ry") {
        handLandmarks = &rightHandLandmarks;
    }

    if (handLandmarks) {
        for (int i = 0; i < 21; ++i) {
            // Update x or y based on the message address
            if (message.getAddress()[2] == 'x') { // Check the third character for 'x' or 'y'
                (*handLandmarks)[i].x = message.getArgAsFloat(i);
            }
            else {
                (*handLandmarks)[i].y = message.getArgAsFloat(i);
            }
        }
    }
}
void Hand::draw()
{
    // Assuming the landmarks are normalized, we map them to the window dimensions.
    ofSetColor(ofColor::blue);
    for (const auto& landmark : leftHandLandmarks) {
        ofDrawCircle(landmark.x * ofGetWidth(), landmark.y * ofGetHeight(), 10);
    }

    ofSetColor(ofColor::red);
    for (const auto& landmark : rightHandLandmarks) {
        ofDrawCircle(landmark.x * ofGetWidth(), landmark.y * ofGetHeight(), 10);
    }

    // Get bounding boxes for both hands
    auto leftHandBox = getBoundingBox(leftHandLandmarks);
    auto rightHandBox = getBoundingBox(rightHandLandmarks);

    // Draw rectangles around both hands
    ofNoFill(); // Draw only the outline of the rectangle
    ofSetLineWidth(2); // Set the line width

    // Adjusting for window size and drawing left hand box
    ofDrawRectangle(leftHandBox.first.x * ofGetWidth(), leftHandBox.first.y * ofGetHeight(),
        (leftHandBox.second.x - leftHandBox.first.x) * ofGetWidth(),
        (leftHandBox.second.y - leftHandBox.first.y) * ofGetHeight());

    // Drawing right hand box
    ofDrawRectangle(rightHandBox.first.x * ofGetWidth(), rightHandBox.first.y * ofGetHeight(),
        (rightHandBox.second.x - rightHandBox.first.x) * ofGetWidth(),
        (rightHandBox.second.y - rightHandBox.first.y) * ofGetHeight());
}

std::pair<glm::vec2, glm::vec2> Hand::getBoundingBox(const std::vector<glm::vec2>& handLandmarks) {
    if (handLandmarks.empty()) return { {0, 0}, {0, 0} };

    float minX = handLandmarks[0].x, maxX = handLandmarks[0].x;
    float minY = handLandmarks[0].y, maxY = handLandmarks[0].y;

    for (const auto& landmark : handLandmarks) {
        minX = std::min(minX, landmark.x);
        maxX = std::max(maxX, landmark.x);
        minY = std::min(minY, landmark.y);
        maxY = std::max(maxY, landmark.y);
    }

    return { {minX, minY}, {maxX, maxY} };
}
