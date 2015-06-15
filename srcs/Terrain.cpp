#include <Terrain.hpp>
#include <Model.hpp>
#include <iostream>

/*******************************************
	Constructors
*******************************************/

Terrain::Terrain(Model & model) : AModule(model)
{
	this->_verticesSize = this->_model._grid * DIMENSIONS;
	this->_colorsSize = this->_model._grid * COLOR_CHANNELS;
	this->_normalsSize = this->_verticesSize;
	this->_elementsSize = this->_model._grid + (this->_model._vertexCol - 1) * (this->_model._vertexRow - 2);

	this->createVertices();
	this->inverseWeightedDistance();
	this->createColors();
	this->createNormals();
	this->createElements();
	return;
}

/*******************************************
	Destructor
*******************************************/

Terrain::~Terrain(void)
{
	if (this->_vertices)
	{
		delete [] this->_vertices;
	}
	if (this->_elements)
	{
		delete [] this->_elements;
	}
	return;
}

/*******************************************
	Member functions
*******************************************/

void				Terrain::inverseWeightedDistance(void)
{
	std::vector<glm::vec3>::iterator	it;
	float								distance, squareDistance;
	float								sum, weight;
	float								diffX, diffZ;

	for (GLuint i = 0; i < this->_verticesSize; i += DIMENSIONS)
	{
		sum = 0.0f;
		weight = 0.0f;
		for (it = this->_model._points.begin(); it != this->_model._points.end(); it++)
		{
			diffX = (*it).x - this->_vertices[i];
			diffZ = (*it).z - this->_vertices[i + 2];
			distance = sqrtf(diffX * diffX + diffZ * diffZ);
			distance = distance == 0 ? 1 : distance;
			squareDistance = pow(distance, 1.7);
			weight += (*it).y / squareDistance;
			sum += 1 / squareDistance;
		}
		this->_vertices[i + 1] = weight / sum;
	}
}

void				Terrain::createNormals(void)
{
	glm::vec3	normal, a, b, c;
	GLuint		stride = this->_model._vertexCol * DIMENSIONS;
	int			pos, diagonal;
	int			i = 0;

	this->_normals = new GLfloat[this->_verticesSize]();
	for (GLuint z = 0; z < this->_model._vertexRow; ++z)
	{
		for (GLuint x = 0; x < this->_model._vertexCol; ++x)
		{
			pos = z * this->_model._vertexCol * DIMENSIONS + x * DIMENSIONS;
			diagonal = pos + stride;
			a = glm::vec3(this->_vertices[pos], this->_vertices[pos + 1], this->_vertices[pos + 2]);		
			b = glm::vec3(this->_vertices[pos + 3], this->_vertices[pos + 4], this->_vertices[pos + 5]);
			c = glm::vec3(this->_vertices[diagonal], this->_vertices[diagonal + 1], this->_vertices[diagonal + 2]);
			normal = normalize(cross(c - a, b - a));
			this->_normals[i++] = normal.x;
			this->_normals[i++] = normal.y;
			this->_normals[i++] = normal.z;
		}
	}
}

void			Terrain::createVertices(void)
{
	int		index = 0;

	this->_vertices = new GLfloat[this->_verticesSize]();
	for (GLuint z = 0 ; z < this->_model._vertexRow; ++z)
	{
		for (GLuint x = 0; x < this->_model._vertexCol; ++x)
		{
			this->_vertices[index++] = static_cast<float>(x) * UNIT;
			this->_vertices[index++] = 0.0f;
			this->_vertices[index++] = static_cast<float>(z) * UNIT;
		}
	}
}

void			Terrain::createColors(void)
{
	int		j = 1;
	float	height = this->_model._top - this->_model._bottom;
	this->_colors = new GLfloat[this->_colorsSize]();
	for (GLuint i = 0; i < this->_colorsSize; i += COLOR_CHANNELS)
	{
		this->_colors[i] = 0.02f;
		this->_colors[i + 1] = 0.5f + 0.42f * this->_vertices[j] / height;
		this->_colors[i + 2] = 0.25f + 0.25 * this->_vertices[j] / height;
		this->_colors[i + 3] = 1.0f;

		j += DIMENSIONS;
	}
}

void			Terrain::createElements(void)
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
