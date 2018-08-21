#include "ofApp.h"
#include "ofxUndo.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxRegisterUndo(position_);
	ofxRegisterUndo(position2_);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawLine(position_, position2_);
	ofDrawCircle(position_, 10);
	ofDrawCircle(position2_, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case OF_KEY_LEFT:
			ofxUndo();
			break;
		case OF_KEY_RIGHT:
			ofxRedo();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	position_.set(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	position2_.set(x,y);
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
