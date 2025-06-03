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
	struct addrinfo res;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	if ( getaddrinfo(ip, PORT, &hint, addr) != 0 )
	{
		std::cerr << gai_strerror(errno) << std::endl;
		return (false);
	}
	res = **addr;
	socketfd = socket(res.ai_family, res.ai_socktype, res.ai_protocol);
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
		memset(tmp, 0, sizeof(char) * DATALEN);
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
