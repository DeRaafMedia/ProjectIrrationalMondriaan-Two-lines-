#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    
    showInfo = false;
    showSquaresId = false;
    oscEnabled = false;
    
    displayResolutionWidth = 1280;
    displayResolutionHeight = 800;
    stripeThickness = 22;
    volumeSensitivity = 30;
    horizontalLineOffset = 0.71;
    verticalLineOffset = 0.29;
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(100);
    
    soundStream.listDevices();
    
    int bufferSize = 1024;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(displayResolutionWidth, 0.0);
  
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    fullscreenWidthOffset = (ofGetWindowWidth() * 0.5);
    fullscreenHeightOffset = (ofGetWindowHeight() * 0.5);
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    volHistory.push_back( scaledVol );
    
    if( volHistory.size() >= displayResolutionWidth ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
        ofTranslate(fullscreenWidthOffset, 0);
        // Calculate background square size
        float backGroundSquare = sqrt(pow(displayResolutionHeight, 2.0) + pow(displayResolutionHeight, 2.0)) * 0.5;
        rectangle_1.draw("background", 0, 0, backGroundSquare, backGroundSquare, 255, 255, 255, 45, false, false);
    ofPopMatrix();
    
    int stripeThickness = 22;
    int volumeSensitivity = 30;
    
    ofPushMatrix();
        ofTranslate(0, displayResolutionHeight * horizontalLineOffset);
        ofSetColor(0, 0, 0);
        ofDrawRectangle(0, 0, displayResolutionWidth, stripeThickness);
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(0, (displayResolutionHeight * horizontalLineOffset) + stripeThickness);
        ofBeginShape();
        for (unsigned int i = 0; i < volHistory.size(); i++){
            if(i == 0) ofVertex(i, 0);
            ofVertex(i, volHistory[i] * volumeSensitivity);
            if(i == volHistory.size() -1) ofVertex(i, 0);
        }
        ofEndShape(false);
    ofPopMatrix();
    
    ofPushMatrix();
        ofRotate(180);
        ofTranslate(-1280, -(displayResolutionHeight * horizontalLineOffset));
        ofBeginShape();
        for (unsigned int i = 0; i < volHistory.size(); i++){
            if(i == 0) ofVertex(i, 0);
            ofVertex(i, volHistory[i] * volumeSensitivity);
            if(i == volHistory.size() -1) ofVertex(i, 0);
        }
        ofEndShape(false);
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(((displayResolutionWidth + (displayResolutionHeight * 0.5)) * verticalLineOffset), 0);
    
        ofRotate(90);
    
        ofPushMatrix();
            ofTranslate(0, 0);
            ofSetColor(0, 0, 0);
            ofDrawRectangle(0, 0, displayResolutionWidth, stripeThickness);
        ofPopMatrix();
    
        ofPushMatrix();
            ofTranslate(0, stripeThickness);
            ofBeginShape();
                for (unsigned int i = 0; i < volHistory.size(); i++){
                    if(i == 0) ofVertex(i, 0);
                    ofVertex(i, volHistory[i] * volumeSensitivity);
                    if(i == volHistory.size() -1) ofVertex(i, 0);
                }
            ofEndShape(false);
        ofPopMatrix();
    
        ofPushMatrix();
            ofRotate(180);
            ofTranslate(-1280, 0);
            ofBeginShape();
                for (unsigned int i = 0; i < volHistory.size(); i++){
                    if(i == 0) ofVertex(i, 0);
                    ofVertex(i, volHistory[i] * volumeSensitivity);
                    if(i == volHistory.size() -1) ofVertex(i, 0);
                }
            ofEndShape(false);
        ofPopMatrix();
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    int numCounted = 0;
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i * 2] * 0.5;
        right[i]	= input[i * 2 + 1] * 0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        
        numCounted += 2;
    }
    curVol /= (float)numCounted;
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'i'){
        showInfo = !showInfo;
    }
    if(key == 's'){
        showSquaresId = !showSquaresId;
    }
    if(key == 'o'){
        oscEnabled = !oscEnabled;
    }
    
    if( key == 'x' ){
        soundStream.start();
    }
    if( key == 'y' ){
        soundStream.stop();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}