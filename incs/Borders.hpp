#ifndef BORDERS_CLASS_HPP
# define BORDERS_CLASS_HPP

# include <glm/glm.hpp>
# include <Define.hpp>
# include <AModule.hpp>

class Borders: public AModule
{
	public:
		Borders(Model & model);
		~Borders(void);

	private:
		Borders(void);
		Borders(Borders const & model);
		Borders &		operator=(Borders const & rhs);
		
		void			assignVertices(GLfloat x, int y, GLfloat z);
		void			assignNormals(GLfloat x, GLfloat y, GLfloat z);
		void			createVertices(void);
		void			createColors(void);
		void			createElements(void);
		void			createNormals(void);

		GLfloat			_bordersTop;
		GLfloat *		_terrainVertices;
		GLfloat			_thickness;
};

#endif /* ! BORDERS_CLASS_HPP */
