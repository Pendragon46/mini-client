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

std::string	MiniClient::request = "GET / HTTP/1.1\r\n\r\n";

/********************************/
/*			Class Function 		*/
/********************************/
void	MiniClient::getIP(std::string argv, std::string &ip, std::string &port)
{
	size_t	column;

	column = argv.rfind(':');
	if (column != std::string::npos)
	{
		ip = argv.substr(0, column);
		port = argv.substr(column + 1);
	}
	else
	{
		ip = argv;
		port = "80";
	}
}


/********************************/
/*		  Static Function		*/
/********************************/


bool	MiniClient::init(char *argv, int &socketfd, struct addrinfo **addr)
{
	struct addrinfo hint;
	struct addrinfo res;
	std::string		ip, port;

	getIP(argv, ip, port);
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	if ( getaddrinfo(ip.c_str(), port.c_str(), &hint, addr) != 0 )
	{
		std::cerr << "getaddrinfo : " <<gai_strerror(errno) << std::endl;
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

bool	MiniClient::sendRequest(int &socketfd, char *requestFilename)
{
	std::ifstream	file;
	std::string		tmp;

	if (requestFilename != NULL)
	{
		request.clear();
		file.open(requestFilename);
		if (file.is_open() == false)
		{
			std::cerr << "Open ( " << requestFilename << " ) : " << strerror(errno) << std::endl;
			return (false);
		}
		while (std::getline(file, tmp))
			request += tmp + "\r\n";
		if (file.eof() != true)
		{
			std::cerr << "Error on read : " << strerror(errno) << std::endl;
			return (false);
		}
	}
	if (send(socketfd, request.c_str(), request.length(), 0) < 0)
	{
		std::cerr << "Send : " << strerror(errno) << std::endl;
		return (false);
	}
	std::cout << "Request sent successfully " << std::endl;
	return (true);
}

bool	MiniClient::getData(int &socketfd)
{
	std::string	res;
	char		tmp[DATALEN];
	int			status = DATALEN;

	while (status == DATALEN)
	{
		memset(tmp, 0, sizeof(char) * DATALEN);
		status = recv(socketfd, tmp, DATALEN, 0);
		if (status == -1)
		{
			std::cerr << "Recv : " << strerror(errno) << std::endl;
			return (false);
		}
		res += tmp;
	}
	std::cout << "Data :\n" << res << std::endl;
	return (true);
}
