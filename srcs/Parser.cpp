# include <iostream>

# include <Parser.hpp>
# include <Model.hpp>
# include <Exceptions.hpp>

/*******************************************
	Constructors
*******************************************/

Parser::Parser(Model & model, char const * scenario, char const * path) : _model(model)
{
	this->checkScenario(scenario);
	this->checkPath(path);
	this->parse();
	this->checkBounds();
	return;
}

/*******************************************
	Destructor
*******************************************/

Parser::~Parser(void)
{
	return;
}

/*******************************************
	Member functions
*******************************************/
void			Parser::checkScenario(char const *scenario)
{
	char const *	options[SCENARIOS] = {"flood", "rain", "waves", "drain", "tsunami"};

	for (int i = 0; i < SCENARIOS; ++i)
	{
		if (std::strcmp(scenario, options[i]) == 0)
		{
			this->_model.setScenario(static_cast<e_scenarios>(i));
			return;
		}
	}
	throw invalidScenarioException();
}

void			Parser::checkPath(char const *path)
{
	std::ifstream		file;
	std::string const	pattern = ".*\\.hds$";
	
	this->_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	this->_file.open(path);
	if (std::regex_match(path, std::regex(pattern)) == false)
	{
		throw invalidFileExtensionException();
	}
}

void			Parser::checkBounds(void) const
{
	GLuint		col = this->_model.getCol();
	GLuint		row = this->_model.getRow();
	GLuint		width = this->_model.getWidth();
	GLuint		height = this->_model.getHeight();

	if (width <= MIN_WIDTH || width > MAX_WIDTH ||
		height < MIN_HEIGHT || height > MAX_HEIGHT)
	{
		throw WindowDimensionsException();
	}
	if (row < MIN_ROW || row > MAX_ROW ||
		col < MIN_COL || col > MAX_COL)
	{
		throw MapDimensionsException();
	}
}

void			Parser::parse(void)
{
	std::string			line;
	std::smatch			captured;
	std::string const	points_pattern = "^\\s*?x:(\\d+)\\s+y:(-?\\d+)\\s+z:(\\d+)$";
	std::string const	resolution_pattern = "^\\s*?width:(\\d+)\\s+height:(\\d+)$";
	std::string const	grid_pattern = "^\\s*?col:(\\d+)\\s+row:(\\d+)$";

	this->_file.exceptions(std::ifstream::badbit);
	for (int i = 0; std::getline(this->_file, line); ++i)
	{
		if (line.empty())
		{
			continue ;
		}
		if (std::regex_match(line, captured, std::regex(points_pattern)))
		{
			this->_model.addPoints(glm::vec3(
				std::atof(captured[X].str().c_str()) * UNIT,
				std::atof(captured[Y].str().c_str()) * UNIT,
				std::atof(captured[Z].str().c_str()) * UNIT
			), true);
			continue ;
		}
		if (std::regex_match(line, captured, std::regex(resolution_pattern)))
		{
			this->_model.setWidth(std::atoi(captured[WIDTH].str().c_str()));
			this->_model.setHeight(std::atoi(captured[HEIGHT].str().c_str()));
			continue ;
		}
		if (std::regex_match(line, captured, std::regex(grid_pattern)))
		{
			this->_model.setCol(std::atoi(captured[COL].str().c_str()));
			this->_model.setRow(std::atoi(captured[ROW].str().c_str()));
			continue ;
		}
		throw invalidMapException();
	}
	this->_file.close();
	if (this->_model.getPoints().empty())
	{
		throw invalidMapException();
	}
}
