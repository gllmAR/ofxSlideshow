#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    slideshow.setup(1024, 768);
    slideshow.loadDir("images");
    slideshow.setupGui();
    
    gui.setup("settings");
    gui.add(&slideshow.slideshowGui);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    slideshow.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    slideshow.draw(0,0, ofGetWidth(),ofGetHeight());
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
