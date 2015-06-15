#ifndef WATERBORDERS_CLASS_HPP
# define WATERBORDERS_CLASS_HPP

# include <glm/glm.hpp>
# include <Define.hpp>
# include <AModule.hpp>

class WaterBorders : public AModule
{
	public:
		WaterBorders(Model & model);
		~WaterBorders(void);

		void			updateWaterBorders(void);
		

	private:
		WaterBorders(WaterBorders const & model);
		WaterBorders &	operator=(WaterBorders const & rhs);

		void			assignVertices(GLfloat x, int y, GLfloat z);
		void			assignNormals(GLfloat x, GLfloat y, GLfloat z);
		void			createVertices(void);
		void			createColors(void);
		void			createElements(void);
		void			createNormals(void);

		GLfloat			_waterBordersTop;
		GLfloat *		_terrainVertices;
		GLfloat *		_waterVertices;
		GLuint			_indexVertices;
		GLuint			_indexNormals;		
};

#endif /* ! WATERBORDERS_CLASS_HPP */
