#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <iostream>
#include <ostream>

class Serializable
{
public:
	virtual bool serialize(std::ostream& os) = 0;
	virtual auto deserialize(std::istream is) -> std::size_t = 0;
	virtual auto serialized_size() const -> std::size_t = 0;
};

#endif

