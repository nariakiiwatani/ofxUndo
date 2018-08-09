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
		if(last_action_ == UNDO) {
			undo2redo();
		}
		auto c = undo_history_.top();
		last_action_ = UNDO;
		ofNotifyEvent(undo_event_, c);
		static_cast<Context&>(*this) = c;
		return true;
	}
	bool redo() {
		if(!canRedo()) return false;
		if(last_action_ == REDO) {
			redo2undo();
		}
		auto c = redo_history_.top();
		last_action_ = REDO;
		ofNotifyEvent(redo_event_, c);
		static_cast<Context&>(*this) = c;
		return true;
	}
	bool canUndo() const {
		return undo_history_.size() > (last_action_==UNDO?1:0);
	}
	bool canRedo() const {
		return redo_history_.size() > (last_action_==REDO?1:0);
	}
	ofEvent<Context>& undoEvent() { return undo_event_; }
	ofEvent<Context>& redoEvent() { return redo_event_; }
protected:
	ofEvent<Context> undo_event_, redo_event_;
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
};
}}
template<typename Context>
using ofxUndo = ofx::undo::Manager<Context>;
