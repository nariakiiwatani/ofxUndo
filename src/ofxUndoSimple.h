#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {
template<typename Context, typename History>
class Simple : public Manager<Context, History>, public Context
{
public:
	Simple() {
		ofAddListener(Manager<Context,History>::restoreEvent(), this, &Simple::setValue);
	}
	~Simple() {
		ofRemoveListener(Manager<Context,History>::restoreEvent(), this, &Simple::setValue);
	}
private:
	void setValue(Context &c) { static_cast<Context&>(*this) = c; }
};
}}
template<typename Context, typename History=std::vector<Context>>
using ofxUndo = ofx::undo::Simple<Context, History>;
