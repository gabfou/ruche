#ifndef HOST_CLASS_H
# define HOST_CLASS_H

# include "ft_gkrellm.hpp"

/**
 * The Host class defines Host related materials, such as the hostname
 */

class Host
{
	public:
		Host(Host const & inst);
		Host(void);
		~Host(void);

		std::string getHostName(void) const;
		std::string getUserName(void) const;
		std::string getName(void) const;

		void determineHostName(void);
		void determineUserName(void);

	private:
		std::string _hostName;
		std::string _userName;
		std::string _name;
};

#endif
