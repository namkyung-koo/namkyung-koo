#ifndef _COMMANDEXECUTE_HPP_
# define _COMMANDEXECUTE_HPP_

# include "./utils/utils.hpp"
# include "Client.hpp"
# include "Channel.hpp"

namespace CommandExecute {
	int chkCommand(int pass);
	void motd(Client& client, std::string const& serverHost);
	void pass(Client& client, std::string const& password, std::string const& serverHost);
	void nick(Client& client, std::string const& serverHost);
	void user(Client& client, std::string const& serverHost, std::string const& serverIp, time_t const& serverStartTime);
	void quit(Client& client);
	void ping(Client& client, std::string const& serverHost);
	void pong(Client& client, std::string const& serverHost, std::string const& token);
	void mode(Client& client, std::string const& serverHost);
	void privmsg(Client& client, std::string const& serverHost);
	void notice(Client& client);
	void part(Client& client, std::string const& serverHost);
	void join(Client& client, std::string const& serverHost);
	void kick(Client& client, std::string const& serverHost);
	void topic(Client& client, std::string const& serverHost);
	void invite(Client& client, std::string const& serverHost);
	bool oper(Client& client, std::string const& opName, std::string const& opPass, std::string const& serverHost, bool oper);
	int kill(Client& client, std::string const& serverHost, bool op);
};

#endif
