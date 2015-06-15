#ifndef AMODULE_CLASS_HPP
# define AMODULE_CLASS_HPP

#include <glfw/glfw3.h>

class Model;

class AModule
{
	public:
		AModule(Model & model);
		virtual ~AModule(void);
		virtual GLfloat *	getVertices(void) const;
		virtual GLfloat *	getColors(void) const;
		virtual GLfloat *	getNormals(void) const;
		virtual GLuint *	getElements(void) const;
		virtual GLuint		getVerticesSize(void) const;
		virtual GLuint		getColorsSize(void) const;
		virtual GLuint		getNormalsSize(void) const;
		virtual GLuint		getElementsSize(void) const;
		virtual GLfloat *	getPositions(void) const;
		virtual GLuint		getPositionsSize(void) const;
		virtual GLuint		getInstances(void) const;
		virtual GLuint		getMaxInstances(void) const;
		virtual GLuint		getBatchSize(void) const;

	private:
		AModule(void);
		virtual void		createVertices(void) = 0;
		virtual void		createElements(void) = 0;
		virtual void		createColors(void) = 0;
		virtual void		createNormals(void) = 0;

	protected:
		Model &				_model;
	
		GLuint				_verticesSize;
		GLuint				_colorsSize;
		GLuint				_normalsSize;
		GLuint				_elementsSize;
	
		GLfloat *			_vertices;
		GLfloat *			_colors;
		GLfloat *			_normals;
		GLuint *			_elements;
	
		GLfloat *			_positions;
		GLuint				_positionsSize;
		GLuint				_instances;
		GLuint				_maxInstances;
		GLuint				_batchSize;
};

#endif /* ! AMODULE_CLASS_HPP */
