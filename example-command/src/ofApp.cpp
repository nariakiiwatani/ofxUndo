#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	glm::vec2 center = ofGetWindowRect().getCenter();
	float radius = 100;
	int div = 5;
	for(int i = 0; i < div; ++i) {
		glm::vec2 pos = glm::rotate(glm::vec2(radius,0), ofDegToRad(360)/(float)div*i);
		polyline_.addVertex(glm::vec3(center+pos,0));
	}
	polyline_.close();
	
	operation_.target = &polyline_;
	operation_.vertex_index = -1;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	polyline_.draw();
	ofPushStyle();
	for(int i = 0, num = polyline_.size(); i < num; ++i) {
		i == operation_.vertex_index ? ofFill() : ofNoFill();
		ofDrawCircle(polyline_[i], 10);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case OF_KEY_RETURN:
			polyline_.clear();
			undo_.clear();
			setup();
			break;
		case OF_KEY_LEFT:
			undo_.undo();
			break;
		case OF_KEY_RIGHT:
			undo_.redo();
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
	if(operation_.vertex_index >= 0)  {
		(*operation_.target)[operation_.vertex_index] = glm::vec3(x,y,0);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for(int i = 0, num = polyline_.size(); i < num; ++i) {
		if(glm::distance(polyline_[i], glm::vec3(x,y,0)) < 10) {
			operation_.pos_from = polyline_[i];
			operation_.vertex_index = i;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if(operation_.vertex_index >= 0) {
		operation_.pos_to = polyline_[operation_.vertex_index];
		undo_.clearRedo();
		undo_.store(operation_.make_command());
	}
	operation_.vertex_index = -1;
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
