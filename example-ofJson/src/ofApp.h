#pragma once

#include "ofMain.h"
#include "ofxJsonUtils.h"
#include "ofxUndoJson.h"

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
	struct MyStruct {
		ofVec2f position;
		float size;
		void loadJson(const ofJson &json) {
			ofxJsonUtils::load(json, kv(position), kv(size));
		}
		ofJson toJson() const {
			return ofxJsonUtils::create(kv(position), kv(size));
		}
	};
	ofxUndoJson<MyStruct> undo_;
};
