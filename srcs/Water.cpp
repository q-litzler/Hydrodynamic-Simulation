#include <Water.hpp>
#include <Model.hpp>
#include <stack>
#include <iostream>

/*******************************************
	Constructors
*******************************************/

Water::Water(Model & model): AModule(model)
{
	srand(time(nullptr));
	this->_verticesSize = this->_model._grid * DIMENSIONS;
	this->_colorsSize = this->_model._grid * COLOR_CHANNELS;
	this->_normalsSize = this->_verticesSize;
	this->_elementsSize = this->_model._grid + (this->_model._vertexCol - 1) * (this->_model._vertexRow - 2);
	this->_terrainVertices = this->_model._terrain->getVertices();
	this->_floodTop = this->_model._top * 0.6f;
	this->_normals = new GLfloat[this->_normalsSize]();
	this->_vertices = new GLfloat[this->_verticesSize]();
	this->createVertices();
	this->createElements();
	this->createColors();
	this->createNormals();
	return;
}

/*******************************************
	Destructor
*******************************************/

Water::~Water(void)
{
	return;
}

/*******************************************
	Member functions
*******************************************/

void			Water::createVertices(void)
{
	for (GLuint i = 0; i < this->_verticesSize; i += DIMENSIONS)
	{
		this->_vertices[i] = this->_terrainVertices[i];
		this->_vertices[i + 1] = this->_model._scenario == DRAIN ? this->_model._top : this->_terrainVertices[i + 1] - WATER_OFFSET;
		this->_vertices[i + 2] = this->_terrainVertices[i + 2];
	}
}

void			Water::createElements(void)
{
	GLuint		count = 0;
	GLuint		i = 0;
	GLuint		backwards = this->_model._col;
	bool		offset = true;

	this->_elements = new GLuint[this->_elementsSize]();
	for (GLuint index = 0; index < this->_elementsSize; ++index)
	{
		if (count == this->_model._vertexCol + this->_model._col)
		{
			count = 0;
			offset = !offset;
			backwards = backwards == this->_model._col ? this->_model._col + 2 : this->_model._col;
		}
		this->_elements[index] = i;
		i += offset ? this->_model._vertexCol : -static_cast<int>(backwards);
		offset = !offset;
		++count;
	}
}

void			Water::createColors(void)
{
	this->_colors = new GLfloat[this->_colorsSize]();
	for (GLuint i = 0; i < this->_colorsSize; i += COLOR_CHANNELS)
	{
		this->_colors[i] = 0.1f;
		this->_colors[i + 1] = 0.5f;
		this->_colors[i + 2] = 0.9f;
		this->_colors[i + 3] = 0.25f;
	}
}

void			Water::createNormals(void)
{
	for (GLuint i = 0; i < this->_normalsSize; i += DIMENSIONS)
	{
		this->_normals[i] = 0.0f;
		this->_normals[i + 1] = glm::normalize(static_cast<GLfloat>(rand()));
		this->_normals[i + 2] = 0.0f;
	}
}

void			Water::assignWaterLevel(GLfloat water, GLuint start, GLuint end, GLuint step)
{
	for (GLuint i = start; i < end; i += step)
	{
		if (this->_vertices[i + 1] > this->_model._bottom
			&& (this->_vertices[i + 1] < this->_floodTop
			|| water < 0 ))
		{
			this->_vertices[i + 1] += water;
		}
	}
}

void			Water::flood(GLfloat waterLevel)
{
	this->assignWaterLevel(waterLevel, 0, this->_model._vertexCol * DIMENSIONS, DIMENSIONS);
	this->assignWaterLevel(waterLevel, 0, this->_verticesSize, this->_model._vertexCol * DIMENSIONS);
	this->assignWaterLevel(waterLevel, this->_model._col * DIMENSIONS, this->_verticesSize, this->_model._vertexCol * DIMENSIONS);
	this->assignWaterLevel(waterLevel, this->_verticesSize - this->_model._vertexCol * DIMENSIONS, this->_verticesSize, DIMENSIONS);
}

void			Water::waves(GLfloat coefficient)
{
	static GLfloat	x = 0.0f;
	static int		t = 0;
	GLfloat			cosinus = std::max(static_cast<double>(0), cos(x));

	if (t == 0)
	{
		x += 0.1f;
		this->assignWaterLevel(coefficient * UNIT * cosinus, 0, this->_model._vertexCol * DIMENSIONS, DIMENSIONS);
		t = 3;
	}
	--t;
}

void			Water::distribute(void)
{
	static int		adjacent[8] = {
	-(this->_model._stride + DIMENSIONS),	3,	3,
	this->_model._stride - 6,				6,
	this->_model._stride - 6,				3,	3
	};
	static GLuint	skipForth[6] = {0, 3, 5, 2, 4, 7};
	static GLuint	skipBack[6] = {2, 4, 7, 0, 3, 5};
	GLuint			back;

	for(int i = 0; i < WATER_DISTRIBUTION_RATE; ++i)
	{
		back = this->_verticesSize - DIMENSIONS;
		for (GLuint forth = 0; forth < this->_verticesSize; forth += DIMENSIONS) 
		{
			this->distributeGo(adjacent, skipForth, forth, 1);
			this->distributeGo(adjacent, skipBack, back, -1);
			back -= DIMENSIONS;
		}
	}
}

void			Water::distributeGo(int adjacent[], GLuint skip[], GLuint pos, int flag)
{
	int				tmp;
	GLuint 			src, dest;
	GLfloat			average, min, max;

	tmp = dest = src = pos;
	min = max  = this->_vertices[pos + 1];
	if (this->_vertices[pos + 1] > this->_terrainVertices[pos + 1])
	{
		for (GLuint i = 0; i < 8; i++)
		{
			tmp += adjacent[i] * flag;
			if ((pos % (this->_model._vertexCol * DIMENSIONS) == 0
				&& (i == skip[0] || i == skip[1] || i == skip[2])))
			{
				continue ;
			}
			if ((pos + 2) % (this->_model._vertexCol * DIMENSIONS) == this->_model._vertexCol * DIMENSIONS - 1
				&& (i == skip[3] || i == skip[4] || i == skip[5]))
			{
				continue ;
			}
			if (tmp >= 0 && tmp < static_cast<int>(this->_verticesSize))
			{
				if (this->_vertices[tmp + 1] < min)
				{
					dest = tmp;
					min = this->_vertices[tmp + 1];
				}
				else if (this->_vertices[tmp + 1] > max)
				{
					src = tmp;
					max = this->_vertices[tmp + 1];
				}
			}
		}
		average = (max + min) / 2.0f; 
		this->_vertices[src + 1] = average;
		this->_vertices[dest + 1] = average;
	}
}
