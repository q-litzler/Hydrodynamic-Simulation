#include <Model.hpp>
#include <AModule.hpp>

/*******************************************
	Constructors
*******************************************/

AModule::AModule(Model & model) : _model(model), _vertices(nullptr), _elements(nullptr)
{
	return;
}

/*******************************************
	Destructor
*******************************************/

AModule::~AModule(void)
{
	return ;
}

/*******************************************
	Accessors - getters
*******************************************/

GLfloat *		AModule::getVertices(void) const
{
	return this->_vertices;
}

GLfloat *		AModule::getColors(void) const
{
	return this->_colors;
}

GLfloat *		AModule::getNormals(void) const
{
	return this->_normals;
}

GLuint *		AModule::getElements(void) const
{
	return this->_elements;
}

GLuint			AModule::getVerticesSize(void) const
{
	return this->_verticesSize;
}

GLuint			AModule::getColorsSize(void) const
{
	return this->_colorsSize;
}

GLuint			AModule::getNormalsSize(void) const
{
	return this->_normalsSize;
}

GLuint			AModule::getElementsSize(void) const
{
	return this->_elementsSize;
}

GLuint			AModule::getInstances(void) const
{
	return this->_instances;
}

GLuint			AModule::getMaxInstances(void) const
{
	return this->_maxInstances;
}

GLfloat *		AModule::getPositions(void) const
{
	return this->_positions;
}

GLuint			AModule::getPositionsSize(void) const
{
	return this->_positionsSize;
}

GLuint			AModule::getBatchSize(void) const
{
	return this->_batchSize;
}
