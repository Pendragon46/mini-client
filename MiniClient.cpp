/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: May 8, 2025 09:15 AM                       *
*                       Last Updated: May 8, 2025 09:17 AM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                       Implementation of class Miniclient                       *
*********************************************************************************/

#include <MiniClient.hpp>

/********************************/
/*		Cannonical Function		*/
/********************************/

MiniClient::MiniClient(){}
MiniClient::~MiniClient(){}
MiniClient::MiniClient( const MiniClient &toCopy ){ static_cast<void>(toCopy); }
MiniClient &MiniClient::operator=( const MiniClient &toCopy)
{
	static_cast<void>(toCopy);
	return (*this);
}

/********************************/
/*		  Static Function		*/
/********************************/


bool	MiniClient::init(char *ip, int &socketfd, struct addrinfo **addr)
{
	struct addrinfo hint;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	socketfd = socket(hint.ai_family, hint.ai_socktype, hint.ai_protocol);
	if ( getaddrinfo(ip, PORT, &hint, addr) != 0 )
	{
		std::cerr << "getaddrinfo : " << gai_strerror(errno) << std::endl;
		return (false);
	}
	if ( socketfd < 0 )
	{
		std::cerr << "CreateSocket : " << strerror(errno) << std::endl;
		return (false);
	}
	return (true);
}


std::string	MiniClient::getData(int &socketfd)
{
	std::string	res;
	char		tmp[DATALEN];
	int			status = 1;

	while (status > 0)
	{
		status = recv(socketfd, tmp, DATALEN, 0);
		if (status == -1)
		{
			std::cerr << "Recv : " << strerror(errno) << std::endl;
			return ("");
		}
		res += tmp;
	}
	return (res);
}
