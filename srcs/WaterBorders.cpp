#include <WaterBorders.hpp>
#include <Model.hpp>
#include <iostream>

/*******************************************
	Constructors
*******************************************/

WaterBorders::WaterBorders(Model & model): AModule(model), _waterBordersTop(0)
{
	this->_elementsSize = (this->_model._col + this->_model._row) * 4 + 2 + 4;
	this->_verticesSize = this->_elementsSize * DIMENSIONS;
	this->_normalsSize = this->_verticesSize;
	this->_colorsSize = this->_elementsSize * COLOR_CHANNELS;
	this->_terrainVertices = this->_model._terrain->getVertices();
	this->_waterVertices = this->_model._water->getVertices();
	this->_vertices = new GLfloat[this->_verticesSize]();
	this->_normals = new GLfloat[this->_normalsSize]();
	this->_indexVertices = 0;
	this->_indexNormals = 0;
	this->createVertices();
	this->createColors();
	return;
}

/*******************************************
	Destructor
*******************************************/

WaterBorders::~WaterBorders(void)
{
	return ;
}

/*******************************************
	Member functions
*******************************************/

void			WaterBorders::updateWaterBorders(void)
{
	this->_indexVertices = 0;
	this->_indexNormals = 0;
	this->_waterVertices = this->_model._water->getVertices();
	this->createVertices();
}

void			WaterBorders::assignVertices(GLfloat x, int y, GLfloat z)
{
	this->_vertices[this->_indexVertices++] = x;
	this->_vertices[this->_indexVertices++] = this->_terrainVertices[y];
	this->_vertices[this->_indexVertices++] = z;
	this->_vertices[this->_indexVertices++] = x;
	this->_vertices[this->_indexVertices++] = this->_waterVertices[y];
	this->_vertices[this->_indexVertices++] = z;
	this->_waterBordersTop = this->_terrainVertices[y] > this->_waterBordersTop ? this->_terrainVertices[y] : this->_waterBordersTop;
}

void			WaterBorders::assignNormals(GLfloat x, GLfloat y, GLfloat z)
{
	for (int vertex = 0; vertex < 2; ++vertex)
	{
		this->_normals[this->_indexNormals++] = x;
		this->_normals[this->_indexNormals++] = y;
		this->_normals[this->_indexNormals++] = z;
	}
}

void			WaterBorders::createVertices(void)
{
	for (GLuint i = 0; i < this->_model._col; ++i)
	{
		this->assignVertices(i * UNIT, i * DIMENSIONS + 1, 0.0f);
	}
	for (GLuint i = 0; i < this->_model._row; ++i)
	{
		this->assignVertices(this->_model._col * UNIT, (i + 1) * this->_model._vertexCol * DIMENSIONS - 2, i * UNIT);
	}
	for (int i = this->_model._col; i > 0; --i)
	{
		this->assignVertices(i * UNIT, this->_model._vertexCol * this->_model._row * DIMENSIONS + 1 + i * DIMENSIONS, this->_model._row * UNIT);
	}
	for (int i = this->_model._row; i >= 0; --i)
	{
		this->assignVertices(0.0f, this->_model._vertexCol * DIMENSIONS * i + 1, i * UNIT);
	}
}

void			WaterBorders::createColors(void)
{
	int		j = 1;

	this->_colors = new GLfloat[this->_colorsSize]();
	for (GLuint i = 0; i < this->_colorsSize; i += COLOR_CHANNELS)
	{
		this->_colors[i] = 0.1f;
		this->_colors[i + 1] = 0.5f;
		this->_colors[i + 2] = 0.9f;
		this->_colors[i + 3] = 0.25f;
		j += DIMENSIONS;
	}
}

void			WaterBorders::createElements(void)
{
	
}

void			WaterBorders::createNormals(void)
{
	
}
