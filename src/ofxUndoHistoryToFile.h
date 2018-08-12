#pragma once

#include "ofxUndo.h"

namespace ofx { namespace undo {

class HistoryToFile : public ofx::undo::Manager<std::filesystem::path>
{
public:
	void setFileExt(const std::string &ext) { extension_ = ext; }
	
	void setDirectory(const std::filesystem::path &path, bool load=true) {
		clear();
		directory_.open(path);
		directory_.sortByDate();
		if(load) {
			for(auto &&f : directory_) {
				std::filesystem::path path(ofFilePath::join(directory_.path(), f.getFileName()));
				store(path);
			}
		}
	}
protected:
	std::filesystem::path createUndo() const {
		auto path = createFileName(extension_);
		save(path);
		return path;
	}
	void loadUndo(const std::filesystem::path &path) {
		load(path);
	}
	virtual std::filesystem::path createFileName(const std::string &ext) const {
		std::string filename = ofJoinString({ofGetTimestampString("%Y%m%d_%H%M_%S%i"), extension_}, ".");
		return ofFilePath::join(directory_.path(), filename);
	}
	virtual void save(const std::filesystem::path &path) const=0;
	virtual void load(const std::filesystem::path &path)=0;
	ofDirectory directory_;
	std::string extension_ = "txt";
};
}}

using ofxUndoFile = ofx::undo::HistoryToFile;
