#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {
template<typename Data>
class Simple : public Manager<Data>, public Data
{
protected:
	Data createUndo() const { return static_cast<Data>(*this); }
	void loadUndo(const Data &data){ static_cast<Data&>(*this) = data; }
};
}}

template<typename Data>
using ofxUndoSimple = ofx::undo::Simple<Data>;
