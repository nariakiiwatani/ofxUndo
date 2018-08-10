#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {
template<typename Data>
class Simple : public Manager<Data>, public Data
{
public:
	Simple() {
		getter_ = [&](Data &data) { data = *this; };
		setter_ = [&](const Data &data) { static_cast<Data&>(*this) = data; };
		Manager<Data>::storeEvent().add(getter_, OF_EVENT_ORDER_AFTER_APP);
		Manager<Data>::restoreEvent().add(setter_, OF_EVENT_ORDER_AFTER_APP);
	}
	~Simple() {
		Manager<Data>::storeEvent().remove(getter_, OF_EVENT_ORDER_AFTER_APP);
		Manager<Data>::restoreEvent().remove(setter_, OF_EVENT_ORDER_AFTER_APP);
	}
private:
	std::function<void(Data&)> getter_;
	std::function<void(const Data&)> setter_;
};
}}
template<typename Data>
using ofxUndo = ofx::undo::Simple<Data>;
