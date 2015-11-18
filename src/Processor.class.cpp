#include "../inc/Processor.class.hpp"

/**
 * Processor:
 * constructors and destructor
 */

Processor::Processor(void)
{
	this->determineActiveCoreNumber();
	this->determineProcessorModel();
	this->determineProcessorName();
	this->determineCoreNumber();
	std::cout << "default Processor constructor called" << std::endl;
}

Processor::Processor(Processor const & inst)
{
	this->_activeCoreNumber = inst.getActiveCoreNumber();
	this->_processorModel = inst.getProcessorModel();
	this->_processorName = inst.getProcessorName();
	this->_coreNumber = inst.getCoreNumber();
	this->_name = inst.getName();
	std::cout << "copy Processor constructor called" << std::endl;
}

Processor::~Processor(void)
{
	std::cout << "Processor destructor called" << std::endl;
}

/**
 * Processor:
 * setters and getters
 */

std::string Processor::getProcessorModel(void) const { return (this->_processorModel); }
unsigned int Processor::getActiveCoreNumber(void) const { return (this->_activeCoreNumber); }
std::string Processor::getProcessorName(void) const { return (this->_processorName); }
unsigned int Processor::getCoreNumber(void) const { return (this->_coreNumber); }
std::string Processor::getName(void) const { return (this->_name); }

/**
 * Processor:
 * member functions
 */

void Processor::determineProcessorModel(void)
{
	char s[1024];
	size_t len;

	len = 1024;
	if (sysctlbyname("hw.model", s, &len, NULL, 0) == -1) {
	} else {
		this->_processorModel = s;
	}
}

void Processor::determineProcessorName(void)
{
	char s[1024];
	size_t len;

	len = 1024;
	if (sysctlbyname("machdep.cpu.brand_string", s, &len, NULL, 0) == -1) {
	} else {
		this->_processorName = s;
	}
}

void Processor::determineCoreNumber(void)
{
	unsigned int n;
	size_t len;

	len = sizeof(unsigned int);
	if (sysctlbyname("hw.ncpu", &n, &len, NULL, 0) == -1) {
	} else {
		this->_coreNumber = n;
	}
}

void Processor::determineActiveCoreNumber(void)
{
	unsigned int n;
	size_t len;

	len = sizeof(unsigned int);
	if (sysctlbyname("hw.activecpu", &n, &len, NULL, 0) == -1) {
	} else {
		this->_activeCoreNumber = n;
	}
}
