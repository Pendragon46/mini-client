/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: May 5, 2025 09:34 AM                       *
*                       Last Updated: May 5, 2025 09:56 AM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                             Header for Miniclient                              *
*********************************************************************************/

#ifndef MINICLIENT_HPP
# define MINICLIENT_HPP

# include <iostream>
# include <fstream>
# include <errno.h>
# include <string>
# include <unistd.h>
# include <cstring>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>

# define DATALEN 1080

class MiniClient
{
	private:
		MiniClient();
		MiniClient( const MiniClient &toCopy );
		~MiniClient();
		MiniClient &operator=( const MiniClient &toCopy);
		
	public:
		static std::string	request;
		static void			getIP(std::string argv, std::string &ip, std::string &port);
		static bool			init(char *ip, int &socketfd, struct addrinfo **addr);
		static bool			sendRequest(int &socketfd, char *requestFilename);
		static bool			getData(int &socketfd);
};
#endif
