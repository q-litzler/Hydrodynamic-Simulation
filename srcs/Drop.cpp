#include <iostream>

#include <Define.hpp>
#include <Model.hpp>
#include <Drop.hpp>

/*******************************************
	Constructors
*******************************************/

Drop::Drop(Model & model): AModule(model)
{
	srand(time(nullptr));
	this->_instances = 0;
	this->_batchSize = BATCH;
	this->_maxInstances = MAX_INSTANCES;
	this->_verticesSize = 8 * DIMENSIONS;
	this->_elementsSize = 14;
	this->_colorsSize = this->_maxInstances * COLOR_CHANNELS;
	this->_normalsSize = this->_maxInstances * DIMENSIONS;
	this->_startHeight = this->_model._top * 3;
	this->_gravity = glm::vec3(0.0f, -1.0f, 0.0f);
	this->_positions = new GLfloat[this->_maxInstances * DIMENSIONS]();
	this->_water = this->_model._water->getVertices();
	this->createVertices();
	this->createElements();
	this->createColors();
	this->createNormals();
	return;
}


/*******************************************
	Destructor
*******************************************/

Drop::~Drop(void)
{
	return ;
}

/*******************************************
	Member functions
*******************************************/

void			Drop::createVertices(void)
{
	static GLfloat vertices[] = { 
		DROP_UNIT, DROP_UNIT, DROP_UNIT,
		0.0f, DROP_UNIT, DROP_UNIT,
		DROP_UNIT, DROP_UNIT, 0.0f,
		0.0f, DROP_UNIT, 0.0f,
		DROP_UNIT, 0.0f, DROP_UNIT,
		0.0f, 0.0f, DROP_UNIT,
		0.0f, 0.0f, 0.0f,
		DROP_UNIT, 0.0f, 0.0f
	};

	this->_vertices = vertices;
}

void			Drop::createElements(void)
{
	static GLuint elements [] = {
		3, 2, 6, 7, 4, 2, 0,
		3, 1, 6, 5, 4, 1, 0
	};

	this->_elements = elements;
}

void			Drop::add(void)
{
	static int	i = 0;

	if (this->_instances <= this->_maxInstances - this->_batchSize)
	{
		for (GLuint drop = 0; drop < this->_batchSize; ++drop)
		{
			this->_positions[i++] = std::rand() % (this->_model._col) * UNIT;
			this->_positions[i++] = this->_startHeight;
			this->_positions[i++] = std::rand() % (this->_model._row) * UNIT;
			++this->_instances;
		}
	}
}

void			Drop::gravity(void)
{
	int			pos;

	for (GLuint drop = 0; drop < this->_instances * DIMENSIONS; drop += DIMENSIONS)
	{
		pos = (this->_positions[drop + 2] / UNIT) * this->_model._vertexCol * DIMENSIONS + (this->_positions[drop] / UNIT) * DIMENSIONS;
		if (this->_positions[drop + 1] - UNIT * RAIN_SPEED > this->_water[pos + 1] + WATER_OFFSET)
		{
			this->_positions[drop + 1] -= (RAIN_SPEED - 2.0f) * UNIT + static_cast<GLfloat>(rand() % static_cast<int>(2.0f * UNIT));
		}
		else
		{
			this->_water[pos + 1] += RAIN_SPEED * UNIT;
			this->_positions[drop] = std::rand() % (this->_model._col) * UNIT;
			this->_positions[drop + 1] = this->_startHeight;
			this->_positions[drop + 2] = std::rand() % (this->_model._row) * UNIT;
		}
	}
}

void			Drop::createColors(void)
{
	this->_colors = new GLfloat[this->_colorsSize]();
	for (GLuint i = 0; i < this->_maxInstances; i += COLOR_CHANNELS)
	{
		this->_colors[i] = 0.1f;
		this->_colors[i + 1] = 0.5f;
		this->_colors[i + 2] = 0.9f;
		this->_colors[i + 3] = 0.3f;
	} 	
}

void			Drop::createNormals(void)
{
	this->_normals = new GLfloat[this->_normalsSize]();
	for (GLuint i = 0; i < this->_maxInstances; i += DIMENSIONS)
	{
		this->_normals[i] = 0.0f;
		this->_normals[i + 1] = 1.0f;
		this->_normals[i + 2] = 0.0f;
	}
}
