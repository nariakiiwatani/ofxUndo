#pragma once

#include "ofEvents.h"

namespace ofx { namespace undo {

template<typename Context, typename History>
class Manager
{
public:
	void setEdited();
	void store(const Context &c);
	void clear();
	Context& undo();
	Context& redo();
	bool canUndo() const;
	bool canRedo() const;
	ofEvent<Context>& restoreEvent() { return restore_event_; }
protected:
	History history_;
	std::size_t current_index_ = 0;
	ofEvent<Context> restore_event_;

	void notify(Context &c) { ofNotifyEvent(restore_event_, c); }
	int getUndoLength() const { return current_index_; }
	int getRedoLength() const { return history_.size()-current_index_; }
	enum Action {
		EDIT,
		STORE,
		UNDO,
		REDO,
		CLEAR
	};
	Action last_action_=CLEAR;
};

template<typename Context, typename History>
void Manager<Context, History>::setEdited()
{
	if(last_action_ == REDO) {
		++current_index_;
	}
	history_.resize(current_index_);
	last_action_ = EDIT;
}

template<typename Context, typename History>
void Manager<Context, History>::store(const Context &c)
{
	setEdited();
	history_.push(c);
	++current_index_;
	last_action_ = STORE;
}
template<typename Context, typename History>
void Manager<Context, History>::clear()
{
	history_.clear();
	current_index_ = 0;
	last_action_ = CLEAR;
}
template<typename Context, typename History>
Context& Manager<Context, History>::undo()
{
	if(last_action_ == UNDO) {
		--current_index_;
	}
	Context &c = history_[current_index_-1];
	notify(c);
	last_action_ = UNDO;
	return c;
}
template<typename Context, typename History>
Context& Manager<Context, History>::redo()
{
	if(last_action_ == REDO) {
		++current_index_;
	}
	Context &c = history_[current_index_];
	notify(c);
	last_action_ = REDO;
	return c;
}
template<typename Context, typename History>
bool Manager<Context, History>::canUndo() const
{
	return getUndoLength() > (last_action_==UNDO?1:0);
}
template<typename Context, typename History>
bool Manager<Context, History>::canRedo() const
{
	return getRedoLength() > (last_action_==REDO?1:0);
}
	
}}
