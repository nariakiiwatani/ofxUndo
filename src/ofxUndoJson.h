#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {
template<typename T>
class Json : public Manager<ofJson>, public T
{
public:
	void onStore(ofJson &data) { data = ((T&)*this).createJson(); }
	void onRestore(const ofJson &data) { ((T&)*this).loadJson(data); }
};
}}

template<typename T>
using ofxUndoJson = ofx::undo::Json<T>;
