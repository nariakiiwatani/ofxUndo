#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {
template<typename T>
class Json : public Manager<ofJson>, public T
{
public:
	ofJson createUndo() const { return ((T&)*this).toJson(); }
	void loadUndo(const ofJson &data) { ((T&)*this).loadJson(data); }
};
}}

template<typename T>
using ofxUndoJson = ofx::undo::Json<T>;
