#ifndef MODEXCEPTIONS_CLASS_HPP
# define MODEXCEPTIONS_CLASS_HPP

#include <exception>
#include <Define.hpp>

/*******************************************
	EXCEPTIONS ABSTRACT BASE CLASS
*******************************************/

class MODExceptions : public std::exception
{
	public:
		MODExceptions(void);
		MODExceptions(MODExceptions const & model);
		virtual ~MODExceptions(void) throw();

		MODExceptions &			operator=(MODExceptions const & rhs);

		virtual char const *	what(void) const throw() = 0;
};


/*****************************************************************************/

/*******************************************
	GUI INITIALIZATION FAIL
*******************************************/

class GUIinitFail : public MODExceptions
{
	public:
		GUIinitFail(void);
		virtual char const * 	what(void) const throw();

	private:
};

/*******************************************
	INVALID FILE EXSTENTION
*******************************************/

class invalidFileExtensionException : public MODExceptions
{
	public:
		invalidFileExtensionException(void);
		virtual char const * 	what(void) const throw();

	private:
};

/*******************************************
	INVALID MAP
*******************************************/

class invalidMapException : public MODExceptions
{
	public:
		invalidMapException(void);
		virtual char const * 	what(void) const throw();

	private:
};

/*******************************************
	INVALID SCENARIO
*******************************************/

class invalidScenarioException : public MODExceptions
{
	public:
		invalidScenarioException(void);
		virtual char const * 	what(void) const throw();

	private:
};

/*******************************************
	INVALID SHADERS
*******************************************/

class invalidShadersException : public MODExceptions
{
	public:
		invalidShadersException(void);
		virtual char const * 	what(void) const throw();

	private:
};

/*******************************************
	INVALID SCENARIO FORMAT
*******************************************/

class FileExtensionException : public MODExceptions
{
	public:
		FileExtensionException(void);
		virtual char const * 	what(void) const throw();

	private:
};


/*******************************************
	MAP DIMENSIONS
*******************************************/

class MapDimensionsException : public MODExceptions
{
	public:
		MapDimensionsException(void);
		virtual char const * 	what(void) const throw();

	private:
};

/*******************************************
	WINDOW DIMENSIONS
*******************************************/

class WindowDimensionsException : public MODExceptions
{
	public:
		WindowDimensionsException(void);
		virtual char const * 	what(void) const throw();

	private:
};

#endif /* ! MODEXCEPTIONS_CLASS_HPP */
