#include "../../include/utils/Message.hpp"
#include "../../include/utils/utils.hpp"
#include "../../include/utils/Print.hpp"
#include <sstream>

mesvec Message::comMes;

Message::Message() {}

Message::~Message() {}

bool Message::parsMessage(std::string& origin) {
	Message::comMes.clear();

	bool first = true;
	std::istringstream str;
	std::string tmp = "";

	if (origin == "\r" || origin == "\n" || origin == "\r\n") {
		comMes.push_back("");
		return true;
	}
	if (origin[origin.size() - 1] == '\r'
		|| (origin[origin.size() - 2] != '\r' && origin[origin.size() - 1] == '\n'))
		str.str(origin.substr(0, origin.size() - 1));
	else
		str.str(origin.substr(0, origin.size() - 2));

	while (std::getline(str, tmp, ' ')) {
		if (first) {
			if (tmp.empty() || chkForbiddenChar(tmp, "\r\n\0"))
				return false;
			else
				comMes.push_back(tmp);
			first = false;
		}
		else {
			if (tmp.empty()) {
				return false;
			}
			else if (tmp[0] == ':') {
				comMes.push_back(tmp.substr(1));
				break;
			}
			else {
				if (!chkForbiddenChar(tmp, "\r\n\0"))
					comMes.push_back(tmp);
				else
					return false;
			}
		}
	}

	tmp = "";
	std::getline(str, tmp);
	if (tmp != "")
		comMes[comMes.size() == 0 ? 0 : comMes.size() - 1] += " " + tmp;
	return true;
}

mesvec const& Message::getMessage() {
	return comMes;
}
