#pragma once

#include "ofMain.h"
#include "ofxUndoSimple.h"
#include "ofxUndoHistoryInterface.h"
#include "ofFileUtils.h"

class StringHistoryToFile : public ofx::undo::history::Vector<std::string> {
public:
	using base_class = ofx::undo::history::Vector<std::string>;
	void setDirectory(const std::string &path) {
		directory_.open(path);
		clear();
		for(auto && f : directory_) {
			base_class::push(f.path());
		}
	}
	void push(const std::string &str) {
		std::hash<std::string> hash_fn;
		std::string filename = ofToString(hash_fn(str))+".txt";
		ofBufferToFile(ofFilePath::join(directory_.path(), filename), ofBuffer(str.c_str(), str.size()), false);
		base_class::push(filename);
	}
	std::string operator[](std::size_t index) const {
		return ofBufferFromFile(base_class::operator[](index), false).getText();
	}
private:
	ofDirectory directory_;
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
	ofx::undo::Simple<std::string, StringHistoryToFile> undo_;
};
