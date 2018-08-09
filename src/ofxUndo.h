#pragma once

namespace ofx { namespace undo {

template<typename Context>
class Manager : public Context
{
public:
	void store(const Context &c) {
		if(last_action_ == REDO) {
			redo2undo();
		}
		undo_history_.push(c);
		redo_history_ = std::stack<Context>();
		last_action_ = STORE;
	}
	void clear() {
		undo_history_ = std::stack<Context>();
		redo_history_ = std::stack<Context>();
		last_action_ = CLEAR;
	}
	bool undo() {
		if(!canUndo()) return false;
		if(last_action_ == UNDO && undo_history_.size() > 1) {
			undo2redo();
		}
		notify(undo_history_.top());
		last_action_ = UNDO;
		return true;
	}
	bool redo() {
		if(!canRedo()) return false;
		if(last_action_ == REDO && redo_history_.size() > 1) {
			redo2undo();
		}
		notify(redo_history_.top());
		last_action_ = REDO;
		return true;
	}
	bool canUndo() const { return !undo_history_.empty(); }
	bool canRedo() const { return !redo_history_.empty(); }
	ofEvent<Context>& restoreEvent() { return restore_event_; }
protected:
	ofEvent<Context> restore_event_;
	std::stack<Context> undo_history_, redo_history_;
	enum Action {
		STORE,
		UNDO,
		REDO,
		CLEAR
	};
	Action last_action_=CLEAR;
	
	void undo2redo() {
		auto c = undo_history_.top();
		undo_history_.pop();
		redo_history_.push(c);
	}
	void redo2undo() {
		auto c = redo_history_.top();
		redo_history_.pop();
		undo_history_.push(c);
	}
	void notify(Context &c) {
		ofNotifyEvent(restore_event_, c);
	}
};
}}
template<typename Context>
using ofxUndo = ofx::undo::Manager<Context>;
