#pragma once

#include "ofMain.h"
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
			position.set(json["position"]["x"],json["position"]["y"]);
			size = json["size"];
		}
		ofJson toJson() const {
			ofJson json;
			json["position"]["x"] = position.x;
			json["position"]["y"] = position.y;
			json["size"] = size;
			return json;
		}
	};
	ofxUndoJson<MyStruct> undo_;
};
