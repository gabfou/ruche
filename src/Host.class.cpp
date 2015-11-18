#include "../inc/Host.class.hpp"

/**
 * Host:
 * constructors and destructor
 */

Host::Host(void)
{
	this->determineHostName();
	this->determineUserName();
	std::cout << "default Host constructor called" << std::endl;
}

Host::Host(Host const & inst)
{
	this->_hostName = inst.getHostName();
	this->_userName = inst.getUserName();
	this->_name = inst.getName();
	std::cout << "copy Host constructor called" << std::endl;
}

Host::~Host(void)
{
	std::cout << "Host destructor called" << std::endl;
}

/**
 * Host:
 * setters and getters
 */

std::string Host::getHostName(void) const { return (this->_hostName); }
std::string Host::getUserName(void) const { return (this->_userName); }
std::string Host::getName(void) const { return (this->_name); }

/**
 * Host:
 * member functions
 */

void Host::determineHostName(void)
{
	char s[1024];
	size_t len;

	len = 1024;
	if (sysctlbyname("kern.hostname", s, &len, NULL, 0) == -1) {
	} else {
		this->_hostName = s;
	}
}

void Host::determineUserName(void)
{
	struct passwd *passwd;
	uid_t uid;

	uid = getuid();
	if ((passwd = getpwuid(uid)))
		this->_userName = passwd->pw_name;
}
