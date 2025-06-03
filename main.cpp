/*********************************************************************************
*                               Author: Pendragon                                *
*                      Creation Date: May 5, 2025 09:34 AM                       *
*                       Last Updated: May 5, 2025 09:55 AM                       *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                  Small client program for socket programming                   *
*********************************************************************************/

#include <MiniClient.hpp>

int main ( int argc, char **argv )
{
	int					servSocket;
	struct 	addrinfo	*servInfo;
	std::string			res;

	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <IP address>." << std::endl;
		return (1);
	}
	if (MiniClient::init(argv[1], servSocket, &servInfo) == false)
		return (1);
	if (connect(servSocket, servInfo->ai_addr, servInfo->ai_addrlen) < 0)
	{
		std::cerr << "Connect : " << strerror(errno) << std::endl;
		return (1);
	}
	res = MiniClient::getData(servSocket);
	std::cout << "Data :\n" <<  res<< std::endl;
	freeaddrinfo(servInfo);
	close(servSocket);
	return (0);
}