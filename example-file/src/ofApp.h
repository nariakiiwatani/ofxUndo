#pragma once

#include "ofMain.h"
#include "ofxUndoHistoryToFile.h"
#include "ofFileUtils.h"

class StringWithHistory : public ofxUndoFile
{
public:
	void save(const std::filesystem::path &path) const {
		ofBufferToFile(path, ofBuffer(str_.c_str(), str_.size()), false);
	}
	void load(const std::filesystem::path &path) {
		str_ = ofBufferFromFile(path, false).getText();
	}
	operator std::string&() {
		return str_;
	}
private:
	std::string str_;
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
	StringWithHistory undo_;
};
