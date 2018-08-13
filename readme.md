# ofxUndo

undo/redo manager for openFrameworks

## Usage

### ofxUndoSimple

ofxUndoSimple directly stores data into history by equal(=) operator.  
Declare ofxUndoSimple with typename like `ofxUndoSimple<ofVec2f>` or `ofxUndoSimple<MyStruct>`.  
That's all you have to do to use this.  
__NOTICE : It doesn't do anything like deep-copying. Be careful when you use it for pointers or structs that has pointers.__  

### ofxUndoFile

ofxUndoFile provides interfaces for file I/O.  
Extend ofxUndoFile and implement `save/load` functions.  

### ofxUndoJson

ofxUndoJson makes it easier to store history in `ofJson` format.  
Declare ofxUndoJson with typename like `ofxUndoJson<MyStruct>`.  
Then implement `toJson/loadJson` in `MyStruct`.  

__I strongly recommend to use this class with [@2bbb](https://github.com/2bbb)'s [ofxJsonUtils](https://github.com/2bbb/ofxJsonUtils)__

### ofxUndoCommandManager

ofxUndoCommandManager stores history as command data such as diffs or operations.  
Implement undo/redo members in ofxUndoCommand and pass it to Manager.  
Since the Manager expects commands as pointers, you can use any class by extending ofxUndoCommand.  

## Special Thanks

- [@2bbb](https://github.com/2bbb)

## License
MIT License.