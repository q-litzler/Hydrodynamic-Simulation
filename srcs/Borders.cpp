#include <Borders.hpp>
#include <Model.hpp>

/*******************************************
	Constructors
*******************************************/

Borders::Borders(Model & model): AModule(model), _bordersTop(0)
{
	this->_elementsSize = (this->_model._col + this->_model._row) * 4 + 2 + 4;
	this->_verticesSize = this->_elementsSize * DIMENSIONS;
	this->_normalsSize = this->_verticesSize;
	this->_colorsSize = this->_elementsSize * COLOR_CHANNELS;
	this->_terrainVertices = this->_model._terrain->getVertices();
	this->_thickness = this->_model._bottom - this->_model._top / 10.0f;
	this->createNormals();
	this->createVertices();
	this->createColors();
	return;
}

/*******************************************
	Destructor
*******************************************/

Borders::~Borders(void)
{
	return ;
}

/*******************************************
	Member functions
*******************************************/

void			Borders::assignVertices(GLfloat x, int y, GLfloat z)
{
	static int	index = 12;
	
	this->_vertices[index++] = x;
	this->_vertices[index++] = this->_thickness;
	this->_vertices[index++] = z;
	this->_vertices[index++] = x;
	this->_vertices[index++] = this->_terrainVertices[y];
	this->_vertices[index++] = z;
	this->_bordersTop = this->_terrainVertices[y] > this->_bordersTop ? this->_terrainVertices[y] : this->_bordersTop;
}

void			Borders::assignNormals(GLfloat x, GLfloat y, GLfloat z)
{
	static int	index = 12;
	
	for (int vertex = 0; vertex < 2; ++vertex)
	{
		this->_normals[index++] = x;
		this->_normals[index++] = y;
		this->_normals[index++] = z;
	}
}

void			Borders::createVertices(void)
{
	const GLfloat		vertices[] = {
		this->_model._col * UNIT, this->_thickness, this->_model._row * UNIT,
		0.0f, this->_thickness, this->_model._row * UNIT,
		this->_model._col * UNIT, this->_thickness, 0.0f,
		0.0f, this->_thickness, 0.0f,
	};

	this->_vertices = new GLfloat[this->_verticesSize]();
	std::copy(vertices, vertices + 12, this->_vertices);
	for (GLuint i = 0; i < this->_model._col; ++i)
	{
		this->assignVertices(i * UNIT, i * DIMENSIONS + 1, 0.0f);
		this->assignNormals(0.0f, 0.0f, -1.0f);
	}
	for (GLuint i = 0; i < this->_model._row; ++i)
	{
		this->assignVertices(this->_model._col * UNIT, (i + 1) * this->_model._vertexCol * DIMENSIONS - 2, i * UNIT);
		this->assignNormals(1.0f, 0.0f, 0.0f);
	}
	for (int i = this->_model._col; i > 0; --i)
	{
		this->assignVertices(i * UNIT, this->_model._vertexCol * this->_model._row * DIMENSIONS + 1 + i * DIMENSIONS, this->_model._row * UNIT);
		this->assignNormals(0.0f, 0.0f, 1.0f);
	}
	for (int i = this->_model._row; i >= 0; --i)
	{
		this->assignVertices(0.0f, this->_model._vertexCol * DIMENSIONS * i + 1, i * UNIT);
		this->assignNormals(-1.0f, 0.0f, 0.0f);
	}
}

void			Borders::createNormals(void)
{
	int	index  = 0;

	this->_normals = new GLfloat[this->_normalsSize]();
	for (int vertex = 0; vertex < 4; ++vertex)
	{
		this->_normals[index++] = 0.0f; 
		this->_normals[index++] = -1.0f;
		this->_normals[index++] = 0.0f;
	}
}

void			Borders::createColors(void)
{
	int		j = 1;

	this->_colors = new GLfloat[this->_colorsSize]();
	for (GLuint i = 0; i < this->_colorsSize; i += COLOR_CHANNELS)
	{
		this->_colors[i] = 0.6;
		this->_colors[i + 1] = 0.45f;
		this->_colors[i + 2] = 0.3f;
		this->_colors[i + 3] = 1.0f;
		j += DIMENSIONS;
	}
}

void			Borders::createElements(void)
{
	
}
