#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// define our data inside an ofParameterGroup 
	params.setName("ofParameterGroup");
	params.add(shapeType.set("shapeType", 1, 1, 2));
	params.add(numShapes.set("numShapes", 50, 1, 100));
	params.add(separation.set("separation", 10, 1, 100));
	params.add(shapeSide.set("shapeSide", 100, 5, 500));
	paramsNested.setName("style");
	paramsNested.add(fill.set("fill", false));
	paramsNested.add(color.set("color", ofColor(0, 255), ofColor(0, 0), ofColor(255, 255)));
	paramsNested.add(lineWidth.set("lineWidth", 1, 0.1, 10));
	params.add(paramsNested);

	// add to gui
	gui.setup("ofApp");
	gui.add(params);
	gui.setPosition(50, 100);

	undoStringParams = params.toString();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(ofColor::darkBlue);
	drawScene();
	
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::drawScene()
{
	// draw the scene related to parameters values
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(500, 200);
	ofSetColor(color.get());
	ofSetLineWidth(lineWidth);
	if (fill) ofFill();
	else ofNoFill();
	for (int i = 0; i < numShapes; ++i)
	{
		if (shapeType == 1) ofDrawRectangle(0, 0, shapeSide, shapeSide);
		else if (shapeType == 2) ofDrawCircle(0, 0, shapeSide);
		ofTranslate(separation, separation);
	}
	ofPopMatrix();
	ofPopStyle();

	//--

	// debug
	std::string str = "";
	int x = gui.getPosition().x + 5;
	int y = gui.getPosition().y + gui.getHeight() + 30;
	str += "> ofParameterGroup\n";
	str += "shapeType   : " + ofToString(shapeType) + "\n";
	str += "numShapes   : " + ofToString(numShapes) + "\n";
	str += "separation  : " + ofToString(separation) + "\n";
	str += "shapeSide   : " + ofToString(shapeSide) + "\n";
	str += "fill        : " + ofToString(fill) + "\n";
	str += "color       : " + ofToString(color) + "\n\n";
	str += "lineWidth   : " + ofToString(lineWidth) + "\n";
	str += "> KEYS\n";
	str += "SPACE       : RANDOMIZE SCENE + STORE\n";
	str += "RETURN      : STORE\n";
	str += "LEFT/RIGHT  : BROWSE UNDO HISTORY\n";
	str += "BACKSPACE	: CLEAR UNDO HISTORY\n\n";
	str += "> UNDO HISTORY\n";
	str += "UNDO LENGHT : " + ofToString(undoStringParams.getUndoLength()) + "\n";
	str += "REDO LENGHT : " + ofToString(undoStringParams.getRedoLength()) + "\n\n";
	str += "> DESCRIPTOR\n";
	str += undoStringParams.getUndoStateDescriptor() + "\n";
	ofDrawBitmapStringHighlight(str, x, y);
}

//--------------------------------------------------------------
void ofApp::randomizeScene()
{
	shapeType = ofRandom(shapeType.getMin(), shapeType.getMax() + 1);
	numShapes = ofRandom(numShapes.getMin(), numShapes.getMax());
	separation = ofRandom(separation.getMin(), separation.getMax());
	shapeSide = ofRandom(shapeSide.getMin(), shapeSide.getMax());
	fill = ofRandom(0, 2);
	//ofColor c;
	//c.setHue(ofRandom(255));
	//c.setSaturation(128);
	//c.setBrightness(128);
	//color = c;
	lineWidth = ofRandom(lineWidth.getMin(), lineWidth.getMax());
}

//--------------------------------------------------------------
void ofApp::storeParams() {
	xmlParams.clear();
	ofSerialize(xmlParams, params);// fill the xml with the ofParameterGroup
	undoStringParams = xmlParams.toString();// fill the ofxUndoSimple with the xml as string
	undoStringParams.store();
}

//--------------------------------------------------------------
void ofApp::refreshParams() {
	xmlParams.clear();
	xmlParams.parse(undoStringParams);// fill the xml with the string 
	ofDeserialize(xmlParams, params);// load the ofParameterGroup
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {

	case ' ':// randomize+store
	{
		randomizeScene();// randomize scene
		storeParams();// store scene
	}
	break;

	case OF_KEY_RETURN:// store 
	{
		storeParams();
	}
	break;

	case OF_KEY_LEFT:// previous
	{
		undoStringParams.undo();
		refreshParams();
	}
	break;

	case OF_KEY_RIGHT:// next
	{
		undoStringParams.redo();
		refreshParams();
	}
	break;

	case OF_KEY_BACKSPACE:// clear history
	{
		undoStringParams.clear();
	}
	break;

	}
}
