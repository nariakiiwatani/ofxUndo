#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {
template<typename T>
class Json : public Manager<ofJson>, public T
{
public:
	ofJson createUndo() { return ((T&)*this).createJson(); }
	void loadUndo(const ofJson &data) { ((T&)*this).loadJson(data); }
};
}}

template<typename T>
using ofxUndoJson = ofx::undo::Json<T>;
