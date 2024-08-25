#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <iostream>
#include <ostream>

class Serializable
{
public:

	virtual void			serialize(std::ostream& os) const = 0;
	virtual void			deserialize(std::istream& is) = 0;
};

#endif

