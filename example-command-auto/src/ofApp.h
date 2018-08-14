#pragma once

#include "ofMain.h"
#include "ofxUndoCommand.h"

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
	ofxUndoCommandManager undo_;
	ofPolyline polyline_;
	struct PolylineOp {
		ofPolyline *target;
		int vertex_index=0;
		glm::vec3 pos_from, pos_to;
		void onStore(const std::shared_ptr<ofxUndoCommand>&) {
			pos_from = pos_to = (*target)[vertex_index];
		}
		std::shared_ptr<ofxUndoCommand> createUndo() const {
			auto ret = std::make_shared<ofxUndoCommand>();
			ofPolyline *p = target;
			int v = vertex_index;
			glm::vec3 f = pos_from, t = pos_to;
			
			ret->undo = [p,v,f]() { (*p)[v] = f; };
			ret->redo = [p,v,t]() { (*p)[v] = t; };
			return ret;
		}
		std::vector<glm::vec3> getUndoStateDescriptor() const { return target->getVertices(); }
	};
	PolylineOp operation_;
};
