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
	
	void setHistoryLengthLimit(std::size_t length);
	void clear();
	
	ofEvent<Data>& storeEvent() { return store_event_; }
	ofEvent<const Data>& restoreEvent() { return restore_event_; }

	void clearRedo();
protected:
	virtual void onStore(Data &data){}
	virtual void onRestore(const Data &data){}
	std::deque<Data> history_;
	std::size_t history_length_limit_=0;
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
	int deleteUndo(int length) {
		int result = 0;
		while(length-->0) {
			if(history_.empty()) break;
			history_.pop_front();
			++result;
		}
		current_index_ = max<int>(0, current_index_-result);
		return result;
	}
};

template<typename Data>
void Manager<Data>::store(Data &data)
{
	if(history_.size() == history_length_limit_) deleteUndo(1);
	history_.emplace_back(data);
	onStore(data);
	store_event_.notify(data);
	current_index_ = history_.size();
	last_action_ = OTHER;
}

template<typename Data>
void Manager<Data>::store()
{
	if(history_length_limit_ > 0 && history_.size() == history_length_limit_) deleteUndo(1);
	history_.emplace_back(Data());
	auto &data = history_.back();
	onStore(data);
	store_event_.notify(data);
	current_index_ = history_.size();
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
void Manager<Data>::setHistoryLengthLimit(std::size_t length)
{
	int sub = history_.size() > length;
	if(sub) {
		deleteUndo(sub);
	}
	history_length_limit_ = length;
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
	history_.resize(current_index_+(last_action_==REDO?1:0));
	current_index_ = history_.size();
	last_action_ = OTHER;
}

}}
