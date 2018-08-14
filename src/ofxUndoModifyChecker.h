#pragma once

namespace ofx { namespace undo {
class ModifyChecker_
{
public:
	virtual ~ModifyChecker_() {
		disable();
	}
	void enable() {
		if(!is_enabled_) {
			ofAddListener(ofEvents().update, this, &ModifyChecker_::frameUpdate);
			last_checked_ = std::chrono::system_clock::now();
			is_enabled_ = true;
		}
	}
	void disable() {
		if(is_enabled_) {
			ofRemoveListener(ofEvents().update, this, &ModifyChecker_::frameUpdate);
			is_enabled_ = false;
		}
	}
	void setInterval(float seconds) { check_interval_millis_ = seconds*1000; }
	ofEvent<void>& onModified() { return modified_event_; }
	virtual void updateDescriptor()=0;
protected:
	void frameUpdate(ofEventArgs&) {
		auto now = std::chrono::system_clock::now();
		if(std::chrono::duration_cast<std::chrono::milliseconds>(now-last_checked_).count() >= check_interval_millis_) {
			if(check()) {
				modified_event_.notify();
			}
			last_checked_ = now;
		}
	}
	std::chrono::system_clock::time_point last_checked_;
	std::size_t check_interval_millis_;
	bool is_enabled_=false;
	ofEvent<void> modified_event_;
	virtual bool check()=0;
};
template<typename Context, typename Descriptor>
class ModifyChecker : public ModifyChecker_
{
public:
	ModifyChecker(Context &context):context_(context) {
		updateDescriptor();
	}
	void updateDescriptor() {
		descripter_ = context_.getUndoStateDescriptor();
	}
protected:
	bool check() {
		auto desc = context_.getUndoStateDescriptor();
		if(desc != descripter_) {
			descripter_ = desc;
			return true;
		}
		return false;
	}
	Context &context_;
	Descriptor descripter_;
};
}}
