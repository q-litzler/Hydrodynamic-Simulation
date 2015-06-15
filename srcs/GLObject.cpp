#include <iostream>

#include <Terrain.hpp>
#include <Drop.hpp>
#include <Water.hpp>
#include <Borders.hpp>
#include <WaterBorders.hpp>
#include <GLObject.hpp>

/*******************************************
	Constructors
*******************************************/

GLObject::GLObject(AModule const & module, Shader const & shader) :
_module(module), _shader(shader)
{
	this->generateVAO();
	this->generateCBO();
	this->generateNBO();
	if (dynamic_cast<const Terrain *>(&module))
	{
		this->generateVBO(GL_STATIC_DRAW);
		this->generateEBO();
	}
	else if (dynamic_cast<const Borders *>(&module))
	{
		this->generateVBO(GL_STATIC_DRAW);
	}
	else if (dynamic_cast<const Water *>(&module))
	{
		this->generateVBO(GL_DYNAMIC_DRAW);
		this->generateEBO();
	}
	else if (dynamic_cast<const WaterBorders *>(&module))
	{
		this->generateVBO(GL_DYNAMIC_DRAW);
	}
	else if (dynamic_cast<const Drop *>(&module))
	{
		this->generateVBO(GL_STATIC_DRAW);
		this->generateEBO();
		this->generatePBO();
		glVertexAttribDivisor(this->_shader.getAInstance(), 1);
	}
	return;
}

/*******************************************
	Destructor
*******************************************/

GLObject::~GLObject(void)
{
	return ;
}

/*******************************************
	Member functions
*******************************************/

void			GLObject::freeResources(void)
{
	glDeleteVertexArrays(1, &this->_vao);
	glDeleteBuffers(1, &this->_cbo);
	glDeleteBuffers(1, &this->_ebo);
	glDeleteBuffers(1, &this->_pbo);
	glDeleteBuffers(1, &this->_vbo);
	glDeleteBuffers(1, &this->_nbo);
}

void			GLObject::generateVAO(void)
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);
}

void			GLObject::generateVBO(GLenum type)
{
	glGenBuffers(1, &this->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->_module.getVerticesSize() * sizeof(GLfloat), this->_module.getVertices(), type);
}

void			GLObject::generateEBO(void)
{
	glGenBuffers(1, &this->_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_module.getElementsSize() * sizeof(GLuint), this->_module.getElements(), GL_STATIC_DRAW);
}

void			GLObject::generateCBO(void)
{
	glGenBuffers(1, &this->_cbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_cbo);
	glBufferData(GL_ARRAY_BUFFER, this->_module.getColorsSize() * sizeof(GLfloat), this->_module.getColors(), GL_STATIC_DRAW);
}

void			GLObject::generateNBO(void)
{
	glGenBuffers(1, &this->_nbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_nbo);
	glBufferData(GL_ARRAY_BUFFER, this->_module.getNormalsSize() * sizeof(GLfloat), this->_module.getNormals(), GL_STATIC_DRAW);
}

void			GLObject::generatePBO(void)
{
	glGenBuffers(1, &this->_pbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_pbo);
	glBufferData(GL_ARRAY_BUFFER, this->_module.getMaxInstances() * DIMENSIONS * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
}

void			GLObject::setVBO(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	glVertexAttribPointer(this->_shader.getAPosition(), DIMENSIONS, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->_shader.getAPosition());
}

void			GLObject::setCBO(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_cbo);
	glVertexAttribPointer(this->_shader.getAColors(), COLOR_CHANNELS, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->_shader.getAColors());
}

void			GLObject::setNBO(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_nbo);
	glVertexAttribPointer(this->_shader.getANormals(), DIMENSIONS, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->_shader.getANormals());
}

void			GLObject::setPBO(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_pbo);
	glVertexAttribPointer(this->_shader.getAInstance(), DIMENSIONS, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->_shader.getAInstance());
}

void			GLObject::setTerrainState(void)
{
	glBindVertexArray(this->_vao);
	this->setVBO();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	this->setCBO();
	this->setNBO();
}

void			GLObject::setBordersState(void)
{
	glBindVertexArray(this->_vao);
	this->setVBO();
	this->setCBO();
	this->setNBO();
}

void			GLObject::setWaterState(void)
{
	glBindVertexArray(this->_vao);
	this->setVBO();
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->_module.getVerticesSize() * sizeof(GLfloat), this->_module.getVertices());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	this->setCBO();
	this->setNBO();
}

void			GLObject::setWaterBordersState(void)
{
	glBindVertexArray(this->_vao);
	this->setVBO();
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->_module.getVerticesSize() * sizeof(GLfloat), this->_module.getVertices());
	this->setCBO();
	this->setNBO();
}

void			GLObject::setDropState(void)
{
	glBindVertexArray(this->_vao);
	this->setVBO();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	this->setPBO();
	glBufferSubData(GL_ARRAY_BUFFER, 0,  this->_module.getMaxInstances() * DIMENSIONS * sizeof(GLfloat), this->_module.getPositions());
	this->setCBO();
	this->setNBO();
}
