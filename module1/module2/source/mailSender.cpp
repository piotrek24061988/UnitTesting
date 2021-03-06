#include "mailSender.hpp"
#include <iostream>

#include "connectionChecker.hpp"

mailSender::mailSender(mailDevice * md): md(md)
{
}

mailSender::~mailSender()
{
}

//Send message to email address from email account with following subject.
//Return -1 if failed.
int mailSender::send(std::string from, std::string to, std::string topic, std::string content)
{
	std::cout << "int mailSender::send(std::string, std::string, std::string, std::string)" << std::endl;

	connectionChecker cc;
	if(!cc.isInternetAvailable())
	{
		return -1;
	}

        FILE * id;
	if((id = md->openDriver()) == NULL)
	{
		return -1;
	}

	if(md->sendMail(id, from, to, topic, content) == -1)
	{
		return -1;
	}

	if(md->closeDriver(id) == -1)
	{
		return -1;
	}

	return 0;
}
