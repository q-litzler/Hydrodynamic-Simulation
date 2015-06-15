#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <Model.hpp>
#include <Exceptions.hpp>

/*******************************************
	Constructors
*******************************************/

Model::Model(void) : _points(0), _top(0.0f), _bottom(0.0f)
{
	return;
}

/*******************************************
	Destructor
*******************************************/

Model::~Model(void)
{
	if (this->_terrain)
	{
		delete this->_terrain;
	}
	if (this->_borders)
	{
		delete this->_borders;
	}
	if (this->_water)
	{
		delete this->_water;
	}
	if (this->_waterBorders)
	{
		delete this->_waterBorders;
	}
	if (this->_drop)
	{
		delete this->_drop;
	}
	return;
}

/*******************************************
	Accessors - Getters
*******************************************/

GLuint					Model::getWidth(void) const
{
	return this->_width;
}

GLuint					Model::getHeight(void) const
{
	return this->_height;
}

GLuint					Model::getCol(void) const
{
	return this->_col;
}

GLuint					Model::getRow(void) const
{
	return this->_row;
}

GLfloat					Model::getTop(void) const
{
	return this->_top;
}

glm::vec3				Model::getLight(void) const
{
	return this->_light;
}

glm::mat4				Model::getMatrix(void) const
{
	return

	glm::rotate(
				glm::mat4(1.0f),
				this->_rotation,
				glm::vec3(0.0f, 1.0f, 0.0f)
			)
	*

	glm::scale(
				glm::mat4(1.0f), 
				glm::vec3(this->_scaleFactor, this->_scaleFactor, this->_scaleFactor)
			)

	*
	glm::translate(
				glm::mat4(1.0f), 
				glm::vec3(-(this->_col * UNIT / 2.0), 0.0f, -(this->_row * UNIT / 2.0))
			);

}

std::vector<glm::vec3>	Model::getPoints(void) const
{
	return this->_points;
}

e_scenarios				Model::getScenario(void) const
{
	return this->_scenario;
}

Water *					Model::getWater(void) const
{
	return this->_water;
}

Terrain *				Model::getTerrain(void) const
{
	return this->_terrain;
}

Borders *				Model::getBorders(void) const
{
	return this->_borders;
}

WaterBorders *			Model::getWaterBorders(void) const
{
	return this->_waterBorders;
}

Drop *					Model::getDrop(void) const
{
	return this->_drop;
}

/*******************************************
	Accessors - Setters
*******************************************/

void					Model::setRotation(float angle)
{
	this->_rotation += angle;
}

void					Model::setScaleFactor(float delta)
{
	this->_scaleFactor *= delta;
}

void					Model::setScenario(e_scenarios type)
{
	this->_scenario = type;
}

void					Model::setWidth(GLuint width)
{
	this->_width = width;
}

void					Model::setHeight(GLuint height)
{
	this->_height = height;
}

void					Model::setRow(GLuint row)
{
	this->_row = row;
}

void					Model::setCol(GLuint col)
{
	this->_col = col;
}



/*******************************************
	Member functions
*******************************************/

void					Model::build(void)
{
	this->setMapCorners();
	this->_rotation = 45.0f;
	this->_light = glm::vec3((this->_col / 3) * UNIT, this->_top + this->_top / 3, 0.0f);
	this->_scaleFactor = 1.0f / this->_row;
	this->_scale = glm::vec3(this->_scaleFactor, this->_scaleFactor, this->_scaleFactor);
	this->_vertexRow = this->_row + 1;
	this->_vertexCol = this->_col + 1;
	this->_stride = this->_vertexCol * DIMENSIONS;
	this->_grid = this->_vertexCol * this->_vertexRow;
	this->_terrain = new Terrain(*this);
	this->_borders = new Borders(*this);
	this->_water = new Water(*this);
	this->_waterBorders = new WaterBorders(*this);
	this->_drop = new Drop(*this);
}

void					Model::setMapCorners(void)
{
	this->addPoints(glm::vec3(0.0f, 0.0f, 0.0f), false);
	this->addPoints(glm::vec3(0.0f, 0.0f, this->_row * UNIT), false);
	this->addPoints(glm::vec3(this->_col * UNIT, 0.0f, this->_row * UNIT), false);
	this->addPoints(glm::vec3(this->_col * UNIT, 0.0f, 0.0f), false);
}

void					Model::addPoints(glm::vec3 point, bool overrideMode)
{
	std::vector<glm::vec3>::iterator	it;

	for (it = this->_points.begin(); it != this->_points.end(); ++it)
	{
		this->_top = (*it).y > this->_top ? (*it).y : this->_top;
		this->_bottom = (*it).y < this->_bottom ? (*it).y : this->_bottom;
		if (point.x == (*it).x && point.z == (*it).z)
		{
			if (overrideMode == true)
			{
				this->_points.erase(it);
				break ;
			}
			return ;
		}
	}
	if (point.x >= 0 && point.x <= this->_col * UNIT
	 	&& point.z >= 0 && point.z <= this->_row * UNIT)
	{
		this->_points.push_back(point);
	}
	else
	{
		std::cerr << CYAN << "Out of bounds vertex ignored:"
			<< " x: " << point.x / UNIT
			<< ", y: " << point.y / UNIT
			<< ", z: "<< point.z / UNIT 
			<< WHITE << std::endl;
	}
}
