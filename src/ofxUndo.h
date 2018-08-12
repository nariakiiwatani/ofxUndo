#pragma once

#include "ofEvents.h"

namespace ofx { namespace undo {

template<typename Data>
class Manager
{
public:
	void store(Data &data);
	void store();
	bool undo();
	bool redo();
	bool canUndo() const { return getUndoLength() > 0; }
	bool canRedo() const { return getRedoLength() > 0; }
	
	void clear();
	
	ofEvent<Data>& storeEvent() { return store_event_; }
	ofEvent<const Data>& restoreEvent() { return restore_event_; }

	void clearRedo();
protected:
	virtual void onStore(Data &data){}
	virtual void onRestore(const Data &data){}
	std::deque<Data> history_;
	std::size_t current_index_;
	enum Action {
		UNDO, REDO, OTHER
	};
	Action last_action_ = OTHER;

	ofEvent<Data> store_event_;
	ofEvent<const Data> restore_event_;
	
protected:
	int getUndoLength() const { return current_index_-(last_action_==UNDO?1:0); }
	int getRedoLength() const { return history_.size()-current_index_-(last_action_==REDO?1:0); }
};

template<typename Data>
void Manager<Data>::store(Data &data)
{
	history_.emplace_back(data);
	onStore(data);
	store_event_.notify(data);
	++current_index_;
	last_action_ = OTHER;
}

template<typename Data>
void Manager<Data>::store()
{
	history_.emplace_back(Data());
	auto &data = history_.back();
	onStore(data);
	store_event_.notify(data);
	++current_index_;
	last_action_ = OTHER;
}

template<typename Data>
bool Manager<Data>::undo()
{
	if(!canUndo()) return false;
	if(last_action_ == UNDO) {
		--current_index_;
	}
	auto &data = history_[current_index_-1];
	onRestore(data);
	restore_event_.notify(data);
	last_action_ = UNDO;
	return true;
}
template<typename Data>
bool Manager<Data>::redo()
{
	if(!canRedo()) return false;
	if(last_action_ == REDO) {
		++current_index_;
	}
	auto &data = history_[current_index_];
	onRestore(data);
	restore_event_.notify(data);
	last_action_ = REDO;
	return true;
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
