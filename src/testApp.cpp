#include "testApp.h"

static float scaleX, scaleY;

//--------------------------------------------------------------
void testApp::setup(){
    isTracking = true;
    
    filterFactor = 0.1f;
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    hardware.setup();
    hardware.setLedOption(LED_OFF);
    hardware.setTiltAngle(12);
    
    context.setup();
    
    depthGen.setup(&context);
    imageGen.setup(&context);
    
    user.setup(&context);
	user.setSmoothing(filterFactor);
	user.setMaxNumberOfUsers(2);
    
    context.toggleRegisterViewport();
    context.toggleMirror();
    
    fluid.setup(5000);
    fluid.numParticles = 1000;
    fluid.gravity = .0002f;
    
    scaleX = ofGetWidth() / 640.0f;
    scaleY = ofGetHeight() / 480.0f;
}

//--------------------------------------------------------------
void testApp::update(){
    hardware.update();
    
    context.update();
    depthGen.update();
    imageGen.update();
    
    if (isTracking) {
        user.update();
    }
    
    fluid.scaleFactorX = 6.4;
    fluid.scaleFactorY = 6.4;
    fluid.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    //imageGen.draw(640, 0, 640, 480);
    
    if (isTracking) {
        user.draw(ofGetWidth(), ofGetHeight());
    }
    
    
    if (0 < user.getNumberOfTrackedUsers()) {
        for (int i = 1; i < user.getNumberOfTrackedUsers() + 1; ++i) {
            ofxTrackedUser *trackedUser = user.getTrackedUser(i);            
            ofxLimb leftLowerArm = trackedUser->left_lower_arm;
            
            ofVec2f leftLowerArmPos;
            leftLowerArmPos.x = leftLowerArm.position[1].X * scaleX;
            leftLowerArmPos.y = leftLowerArm.position[1].Y * scaleY;
            
            fluid.setSubstitutionOfMouse(leftLowerArmPos);
            fluid.bMouseEnabled = false;
            fluid.bUseSubstitutionOfMouse = true;
            
            ofSetColor(0, 255, 0);
            //ofCircle(leftLowerArm.position[0].X, leftLowerArm.position[0].Y, 15);
            
            ofPushMatrix();
            ofScale(scaleX, scaleY, 1);
            ofCircle(leftLowerArm.position[1].X, leftLowerArm.position[1].Y, 15);
            ofPopMatrix();
        }
    }
    
    fluid.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}