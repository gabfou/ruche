#ifndef PROCESSOR_CLASS_H
# define PROCESSOR_CLASS_H

# include "ft_gkrellm.hpp"

/**
 * The Processor class defines processor related materials, such as the core
 * number, the processor name and Model...
 */

class Processor
{
	public:
		Processor(Processor const & inst);
		Processor(void);
		~Processor(void);

		unsigned int getActiveCoreNumber(void) const;
		std::string getProcessorModel(void) const;
		std::string getProcessorName(void) const;
		unsigned int getCoreNumber(void) const;
		std::string getName(void) const;

		void determineActiveCoreNumber(void);
		void determineProcessorModel(void);
		void determineProcessorName(void);
		void determineCoreNumber(void);

	private:
		unsigned int _activeCoreNumber;
		std::string _processorModel;
		std::string _processorName;
		unsigned int _coreNumber;
		std::string _name;
};

#endif
