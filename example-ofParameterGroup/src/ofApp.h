#pragma once

#include "ofMain.h"

#include "ofxUndoSimple.h"

#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void draw();
	void keyPressed(int key);

private:

	//ofParameterGroup
	ofParameterGroup params;
	ofParameterGroup paramsNested;
	ofParameter<bool> fill;
	ofParameter<float> lineWidth;
	ofParameter<ofColor> color;
	ofParameter<int> shapeType;
	ofParameter<int> numShapes;
	ofParameter<int> separation;
	ofParameter<int> shapeSide;

	ofxPanel gui;
	
	void drawScene();
	void randomizeScene();

	ofxUndoSimple<std::string> undoStringParams;
	ofXml xmlParams;
	void refreshParams();
	void storeParams();
};
