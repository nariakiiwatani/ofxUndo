#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//define our data inside an ofParameterGroup 
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

	//customize gui colors
	ofxGuiSetDefaultHeight(20);
	ofxGuiSetBorderColor(32);
	ofxGuiSetFillColor(ofColor(48));
	ofxGuiSetTextColor(ofColor::white);
	ofxGuiSetHeaderColor(ofColor(24));

	//add to gui
	gui.setup("params");
	gui.add(params);
	gui.setPosition(50, 100);

	parameterString = params.toString();
}

//--------------------------------------------------------------
void ofApp::update() {

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
	//draw the scene related to parameters values
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

	//debug

	//display the parameters values:
	string str;
	int x = gui.getPosition().x + 15;
	int y = gui.getPosition().y + gui.getHeight() + 60;
	int pad = 20;
	int i = 0;
	str = "> ofParameterGroup\n";
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "fill       : " + ofToString(fill);
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "lineWidth  : " + ofToString(lineWidth);
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "color      : " + ofToString(color);
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "shapeType  : " + ofToString(shapeType);
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "numShapes  : " + ofToString(numShapes);
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "separation : " + ofToString(separation);
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "shapeSide  : " + ofToString(shapeSide);
	ofDrawBitmapStringHighlight(str, x, y + pad * i++); i++;

	//help info:
	str = "> KEYS";
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "SPACE      : RANDOMIZE SCENE + STORE";
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "RETURN     : STORE";
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "LEFT/RIGHT : BROWSE UNDO HISTORY";
	ofDrawBitmapStringHighlight(str, x, y + pad * i++); i++;
	//display undo history info:
	str = "> UNDO HISTORY";
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "UNDO LENGHT:" + ofToString(parameterString.getUndoLength());
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = "REDO LENGHT:" + ofToString(parameterString.getRedoLength());
	ofDrawBitmapStringHighlight(str, x, y + pad * i++); i++;
	//descriptor content
	str = "> DESCRIPTOR";
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
	str = parameterString.getUndoStateDescriptor();
	ofDrawBitmapStringHighlight(str, x, y + pad * i++);
}

//--------------------------------------------------------------
void ofApp::randomizeScene()
{
	fill = ofRandom(0, 2);
	lineWidth = ofRandom(lineWidth.getMin(), lineWidth.getMax());
	shapeType = ofRandom(shapeType.getMin(), shapeType.getMax() + 1);
	numShapes = ofRandom(numShapes.getMin(), numShapes.getMax());
	separation = ofRandom(separation.getMin(), separation.getMax());
	shapeSide = ofRandom(shapeSide.getMin(), shapeSide.getMax());
	//ofColor c;
	//c.setHue(ofRandom(255));
	//c.setSaturation(128);
	//c.setBrightness(128);
	//color = c;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {

	case OF_KEY_LEFT://previous
	{
		parameterString.undo();
		std::string str = parameterString;

		ofLog() << "--------------------------------";
		ofLogNotice(__FUNCTION__) << "UNDO: " << str;
		refreshParams();
	}
	break;

	case OF_KEY_RIGHT://next
	{
		parameterString.redo();
		std::string str = parameterString;

		ofLog() << "--------------------------------";
		ofLogNotice(__FUNCTION__) << "REDO: " << str;
		refreshParams();
	}
	break;

	case OF_KEY_BACKSPACE://clear history
	{
		parameterString.clear();
		std::string str = parameterString;

		ofLog() << "--------------------------------";
		ofLogNotice(__FUNCTION__) << "CLEAR: " << str;
	}
	break;

	case OF_KEY_RETURN://store 
	{
		storeParams();
	}
	break;

	case ' '://randomize+store
	{
		randomizeScene();//randomize scene
		storeParams();//store scene
	}
	break;

	}
}

//--------------------------------------------------------------
void ofApp::storeParams() {
	ofSerialize(parameterXml, params);
	std::string str;
	str = parameterXml.toString();
	parameterString = str;
	parameterString.store();

	ofLog() << "--------------------------------";
	ofLogNotice(__FUNCTION__) << "STORE: " << endl << str;
	ofLogNotice(__FUNCTION__) << "UNDO LENGHT: " << parameterString.getUndoLength();
	ofLogNotice(__FUNCTION__) << "REDO LENGHT: " << parameterString.getRedoLength();
}

//--------------------------------------------------------------
void ofApp::refreshParams() {
	std::string str = parameterString;
	ofLogNotice(__FUNCTION__) << "parameterString : " << endl << str;

	//deserialize
	ofXml _xml_;
	_xml_.parse(str);//fill the xml with the string 
	ofLogNotice(__FUNCTION__) << "_xml_ : " << endl << _xml_;

	ofDeserialize(_xml_, params);

	ofLogNotice(__FUNCTION__) << "params: " << endl << params.toString();
	ofLog() << "--------------------------------";
}
