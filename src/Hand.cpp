#include "Hand.h"

void Hand::setup()
{
    receiver.setup(RECEIVE_PORT);
    ofLogToConsole();
    leftHandLandmarks.resize(21); // Prepare 21 landmarks for each hand
    rightHandLandmarks.resize(21);
}



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
    // No unprocessed messages are left in the queue after this point
        // Apply smoothing after processing all messages for this frame
    }

    // Example of modifying your existing particle generation code in Hand::update
    for (const auto& landmark : leftHandLandmarks) {
        glm::vec2 particlePos = glm::vec2(landmark.x * ofGetWidth(), landmark.y * ofGetHeight());
        glm::vec2 particleVel = glm::vec2(ofRandom(-0.5, 0.5), ofRandom(-1, -0.5)); // Upward and slight horizontal drift
        float particleSize = ofRandom(5, 10); // Start with a random size
        ofColor particleColor = ofColor(255, 255, 0); // Start with a bright yellow
        particles.emplace_back(particlePos, particleVel, 100, particleColor, particleSize); // 100 frames lifespan
    }

    // Example of modifying your existing particle generation code in Hand::update
    for (const auto& landmark : rightHandLandmarks) {
        glm::vec2 particlePos = glm::vec2(landmark.x * ofGetWidth(), landmark.y * ofGetHeight());
        glm::vec2 particleVel = glm::vec2(ofRandom(-0.5, 0.5), ofRandom(-1, -0.5)); // Upward and slight horizontal drift
        float particleSize = ofRandom(5, 10); // Start with a random size
        ofColor particleColor = ofColor(255, 255, 0); // Start with a bright yellow
        particles.emplace_back(particlePos, particleVel, 100, particleColor, particleSize); // 100 frames lifespan
    }



    // Update particles
    for (auto& particle : particles) {
        particle.update();
    }
    
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
    drawBox();
    displayHandSpeed();
    displayFingerNames();

    for (auto& particle : particles) {
        particle.draw();
    }
    drawLanmarks();
}

std::pair<glm::vec2, glm::vec2> Hand::getBoundingBox(const std::vector<glm::vec2>& handLandmarks) {
    if (handLandmarks.empty()) return { {0, 0}, {0, 0} };

    float minX = handLandmarks[0].x, maxX = handLandmarks[0].x;
    float minY = handLandmarks[0].y, maxY = handLandmarks[0].y;

    for (const auto& landmark : handLandmarks) {
        minX = min(minX, landmark.x);
        maxX = max(maxX, landmark.x);
        minY = min(minY, landmark.y);
        maxY = max(maxY, landmark.y);
    }

    return { {minX, minY}, {maxX, maxY} };
}

void Hand::displayHandSpeed() {
    // Assuming velocity calculation is already done in updateVelocity()
    std::string leftSpeedText = "Left Hand Speed: " + std::to_string(glm::length(leftHandVelocity));
    std::string rightSpeedText = "Right Hand Speed: " + std::to_string(glm::length(rightHandVelocity));

    ofSetColor(ofColor::white);
    ofDrawBitmapString(leftSpeedText, 20, 20);
    ofDrawBitmapString(rightSpeedText, 20, 40);
}

void Hand::displayFingerNames() {
    // Placeholder for displaying finger names or IDs
    // This is where you could loop over landmarks and draw text for each
    ofSetColor(ofColor::white);
    // Example for the left hand
    std::vector<std::string> fingerNames = { "PalmBase","Thumb", "Index", "Middle", "Ring", "Pinky" };
    for (int i = 0; i < leftHandLandmarks.size() && i < fingerNames.size() * 4; i += 4) {
        ofDrawBitmapString(fingerNames[i / 4], leftHandLandmarks[i].x * ofGetWidth(), leftHandLandmarks[i].y * ofGetHeight());
    }
    for (int i = 0; i < rightHandLandmarks.size() && i < fingerNames.size() * 4; i += 4) {
        ofDrawBitmapString(fingerNames[i / 4], rightHandLandmarks[i].x * ofGetWidth(), rightHandLandmarks[i].y * ofGetHeight());
    }
}

void Hand::drawBox() {
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

void Hand::drawLanmarks() {
    // Assuming the landmarks are normalized, we map them to the window dimensions.
    ofSetColor(ofColor::blue);
    for (const auto& landmark : leftHandLandmarks) {
        ofDrawCircle(landmark.x * ofGetWidth(), landmark.y * ofGetHeight(), 10);
    }

    ofSetColor(ofColor::red);
    for (const auto& landmark : rightHandLandmarks) {
        ofDrawCircle(landmark.x * ofGetWidth(), landmark.y * ofGetHeight(), 10);
    }
}
