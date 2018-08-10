#pragma once

namespace ofx { namespace undo {
namespace history {

template<typename Context>
class Vector : std::vector<Context> {
public:
	void push(const Context &c) { std::vector<Context>::push_back(c); }
	std::size_t size() const { return std::vector<Context>::size(); }
	Context& operator[](std::size_t index) { return std::vector<Context>::operator[](index); }
	void clear() { std::vector<Context>::clear(); }
	void resize(std::size_t size) { std::vector<Context>::resize(size); }
};

}
}}
