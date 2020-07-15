#pragma once

#include "ofMain.h"

#include "ofxUndoSimple.h"

#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

private:

	ofxPanel gui;
	
	void drawScene();
	void randomizeScene();


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

	ofxUndoSimple<std::string> parameterString;
	
	ofXml parameterXml;
	void refreshParams();
	void storeParams();
};
