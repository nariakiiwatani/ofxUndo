# ofxUndo

undo/redo manager for openFrameworks

## usage

```
struct MyUndoObject {
	ofVec3f your;
	float cool;
	ofPolyline feature;
};
ofxUndo<MyUndoObject> obj;

// ofxUndo<MyUndoObject> extends MyUndoObject so you can edit it as usual
obj.your = ofVec3f(0,1,2);
obj.cool = 3;
obj.feature.lineTo(obj.your);
obj.setEdited();	// call setEdited everytime you end up editing.

// store for future undo-ing
obj.store();

// now you can edit them without warrying!
obj.your = ofVec3f(5,6,7);
obj.cool = 8;
obj.feature.lineTo(obj.your);
obj.setEdited();	// call setEdited everytime you end up editing.

// restore previous value
obj.undo();

```

## advanced

Histories are stored in `std::vector` by default.  
It's also possible to manage them by your own class.  
See `example-ofJson` and `example-file`.  
I will update readme for detailed information soon...