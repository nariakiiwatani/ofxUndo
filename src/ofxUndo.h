#pragma once

#include "ofEvents.h"

namespace ofx { namespace undo {

template<typename Data>
class Manager
{
public:
	void store(Data &data);
	void store();
	int undo(int times=1);
	int redo(int times=1);
	bool canUndo(int times=1, int *maximum=nullptr) const;
	bool canRedo(int times=1, int *maximum=nullptr) const;
	
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
int Manager<Data>::undo(int times)
{
	int maximum = 0;
	if(!canUndo(times, &maximum)) {
		return undo(maximum);
	}
	current_index_ -= times - (last_action_==UNDO?0:1);
	auto &data = history_[current_index_-1];
	onRestore(data);
	restore_event_.notify(data);
	last_action_ = UNDO;
	return times;
}
template<typename Data>
int Manager<Data>::redo(int times)
{
	int maximum = 0;
	if(!canRedo(times, &maximum)) {
		return redo(maximum);
	}
	current_index_ += times - (last_action_==REDO?0:1);
	auto &data = history_[current_index_];
	onRestore(data);
	restore_event_.notify(data);
	last_action_ = REDO;
	return times;
}

template<typename Data>
bool Manager<Data>::canUndo(int times, int *maximum) const
{
	int length = getUndoLength();
	if(maximum) *maximum = length;
	return times <= length;
}
template<typename Data>
bool Manager<Data>::canRedo(int times, int *maximum) const
{
	int length = getRedoLength();
	if(maximum) *maximum = length;
	return times <= length;
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
