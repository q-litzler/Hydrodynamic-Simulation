#include <Exceptions.hpp>

/*******************************************
	AVM MODEXCEPTIONS ABSTRACT BASE CLASS
*******************************************/

MODExceptions::MODExceptions(void) : std::exception()
{
	return;
}

MODExceptions::MODExceptions(MODExceptions const & model) : std::exception()
{
	*this = model;
	return;
}

MODExceptions::~MODExceptions(void) throw()
{
	return;
}

MODExceptions &		MODExceptions::operator=(MODExceptions const & rhs)
{
	if (this != &rhs)
	{

	}
	return *this;
}

/*******************************************
	GUI INITIALIZATION FAIL
*******************************************/

GUIinitFail::GUIinitFail(void) : MODExceptions()
{
	return;
}

char const *	GUIinitFail::what(void) const throw()
{
	return "error while initializing Graphic User Interface";
}

/*******************************************
	INVALID FILE EXTENSION
*******************************************/

invalidFileExtensionException::invalidFileExtensionException(void) : MODExceptions()
{
	return;
}

char const *	invalidFileExtensionException::what(void) const throw()
{
	return "file must have .hds extension";
}

/*******************************************
	INVALID MAP
*******************************************/

invalidMapException::invalidMapException(void) : MODExceptions()
{
	return;
}

char const *	invalidMapException::what(void) const throw()
{
	return "map format is invalid. Should be: x:<uint> y:<int> z:<uint>";
}

/*******************************************
	INVALID SCENARIO
*******************************************/

invalidScenarioException::invalidScenarioException(void) : MODExceptions()
{
	return;
}

char const *	invalidScenarioException::what(void) const throw()
{
	return "invalid scenario";
}

/*******************************************
	INVALID SHADERS
*******************************************/

invalidShadersException::invalidShadersException(void) : MODExceptions()
{
	return;
}

char const *	invalidShadersException::what(void) const throw()
{
	return "impossible to compile shaders";
}

/*******************************************
	WINDOW DIMENSIONS
*******************************************/

WindowDimensionsException::WindowDimensionsException(void) : MODExceptions()
{
	return;
}

char const *	WindowDimensionsException::what(void) const throw()
{
	return "Window width and height should be within 100 and 1400 pixels";
}

/*******************************************
	MAP DIMENSIONS
*******************************************/

MapDimensionsException::MapDimensionsException(void) : MODExceptions()
{
	return;
}

char const *	MapDimensionsException::what(void) const throw()
{
	return "Map rows and columns values should be within 20 and 3000";
}
