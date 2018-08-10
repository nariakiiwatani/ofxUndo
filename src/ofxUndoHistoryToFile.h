#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {

class HistoryToFile : public ofx::undo::Manager<std::filesystem::path>
{
public:
	void setFileExt(const std::string &ext) { extension_ = ext; }
	void setIOEnabled(bool enabled) { is_enabled_ = enabled; }
	bool isIOEnabled() const { return is_enabled_; }
	
	void setDirectory(const std::filesystem::path &path) {
		clear();
		directory_.open(path);
		bool cache = isIOEnabled();
		setIOEnabled(false);
		for(auto &&f : directory_) {
			std::filesystem::path filename(f.getFileName());
			store(filename);
		}
		setIOEnabled(cache);
	}

protected:
	void onStore(std::filesystem::path &path) {
		path = createFileName(extension_);
		if(isIOEnabled()) {
			save(ofFilePath::join(directory_.path(), path));
		}
	}
	void onRestore(const std::filesystem::path &path) {
		if(isIOEnabled()) {
			load(ofFilePath::join(directory_.path(), path));
		}
	}
	virtual std::filesystem::path createFileName(const std::string &ext) const {
		return ofJoinString({ofGetTimestampString("%Y%m%d_%H%M_%S%i"), extension_}, ".");
	}
	virtual void save(const std::filesystem::path &path)=0;
	virtual void load(const std::filesystem::path &path)=0;
	ofDirectory directory_;
	std::string extension_ = "txt";
	bool is_enabled_=true;
};
}}

using ofxUndoFile = ofx::undo::HistoryToFile;
