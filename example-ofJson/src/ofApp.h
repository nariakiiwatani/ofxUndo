#pragma once

#include "ofMain.h"
#include "ofxUndoSimple.h"
#include "ofJson.h"

class ofJsonHistory {
public:
	void push(const ofJson &json) {
		json_.push_back(json);
	}
	std::size_t size() const {
		return json_.size();
	}
	ofJson& operator[](std::size_t index) {
		return json_[index];
	}
	void clear() {
		json_.clear();
	}
	void resize(std::size_t size) {
		while(json_.size() < size) {
			json_.push_back(ofJson());
		}
		while(json_.size() > size) {
			json_.erase(json_.size()-1);
		}
	}
private:
	ofJson json_;
};

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
private:
	ofx::undo::Simple<ofJson, ofJsonHistory> undo_;
};
