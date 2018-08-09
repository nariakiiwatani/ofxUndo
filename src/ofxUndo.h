#pragma once

namespace ofx { namespace undo {

template<typename Context, typename Object=Context>
class Manager
{
public:
	void store() {
		if(last_action_ == REDO) {
			redo2undo();
		}
		undo_history_.push(static_cast<Context*>(this)->createUndo());
		redo_history_ = std::stack<Object>();
		last_action_ = STORE;
	}
	void clear() {
		undo_history_ = std::stack<Object>();
		redo_history_ = std::stack<Object>();
		last_action_ = CLEAR;
	}
	bool undo() {
		if(!canUndo()) return false;
		if(last_action_ == UNDO && undo_history_.size() > 1) {
			undo2redo();
		}
		auto &o = undo_history_.top();
		static_cast<Context*>(this)->loadUndo(o);
		notify(o);
		last_action_ = UNDO;
		return true;
	}
	bool redo() {
		if(!canRedo()) return false;
		if(last_action_ == REDO && redo_history_.size() > 1) {
			redo2undo();
		}
		auto &o = redo_history_.top();
		static_cast<Context*>(this)->loadUndo(o);
		notify(o);
		last_action_ = REDO;
		return true;
	}
	bool canUndo() const { return !undo_history_.empty(); }
	bool canRedo() const { return !redo_history_.empty(); }
	ofEvent<Object>& restoreEvent() { return restore_event_; }
protected:
	ofEvent<Object> restore_event_;
	std::stack<Object> undo_history_, redo_history_;
	enum Action {
		STORE,
		UNDO,
		REDO,
		CLEAR
	};
	Action last_action_=CLEAR;
	
	void undo2redo() {
		auto o = undo_history_.top();
		undo_history_.pop();
		redo_history_.push(o);
	}
	void redo2undo() {
		auto o = redo_history_.top();
		redo_history_.pop();
		undo_history_.push(o);
	}
	void notify(Object &o) {
		ofNotifyEvent(restore_event_, o);
	}
};
}}
template<typename Context, typename Object=Context>
using ofxUndo = ofx::undo::Manager<Context, Object>;
