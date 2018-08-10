#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {
template<typename Data>
class Simple : public Manager<Data>, public Data
{
protected:
	void onStore(Data &data) { data = *this; }
	void onRestore(const Data &data){ static_cast<Data&>(*this) = data; }
};
}}
template<typename Data>
using ofxUndo = ofx::undo::Simple<Data>;
