#ifndef _MESSAGE_HPP_
# define _MESSAGE_HPP_

#include "utils.hpp"

class Message {
private:
	Message();
	static mesvec comMes;
public:
	~Message();
	static bool parsMessage(std::string& origin);
	static mesvec const& getMessage();
};

#endif
