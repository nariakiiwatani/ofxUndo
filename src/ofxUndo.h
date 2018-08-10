#pragma once

#include "ofEvents.h"

namespace ofx { namespace undo {

template<typename Data>
class Manager
{
public:
	void store();
	void undo();
	void redo();
	bool canUndo() const { return getUndoLength() > (last_action_==UNDO?1:0); }
	bool canRedo() const { return getRedoLength() > (last_action_==REDO?1:0); }
	
	void clear();
	
	ofEvent<Data>& storeEvent() { return store_event_; }
	ofEvent<const Data>& restoreEvent() { return restore_event_; }

	void clearRedo();
protected:
	std::deque<Data> history_;
	std::size_t current_index_;
	enum Action {
		UNDO, REDO, OTHER
	};
	Action last_action_ = OTHER;

	ofEvent<Data> store_event_;
	ofEvent<const Data> restore_event_;
	
protected:
	int getUndoLength() const { return current_index_; }
	int getRedoLength() const { return history_.size()-current_index_; }
};
	
template<typename Data>
void Manager<Data>::store()
{
	history_.emplace_back(Data());
	store_event_.notify(history_.back());
	++current_index_;
	last_action_ = OTHER;
}

template<typename Data>
void Manager<Data>::undo()
{
	if(last_action_ == UNDO) {
		--current_index_;
	}
	restore_event_.notify(history_[current_index_-1]);
	last_action_ = UNDO;
}
template<typename Data>
void Manager<Data>::redo()
{
	if(last_action_ == REDO) {
		++current_index_;
	}
	restore_event_.notify(history_[current_index_]);
	last_action_ = REDO;
}
template<typename Data>
void Manager<Data>::clear()
{
	history_.clear();
	current_index_ = 0;
	last_action_ = OTHER;
}
template<typename Data>
void Manager<Data>::clearRedo() {
	if(last_action_ == REDO) {
		++current_index_;
	}
	history_.resize(current_index_);
	last_action_ = OTHER;
}

}}
