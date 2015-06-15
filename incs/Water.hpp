#ifndef WATER_CLASS_HPP
# define WATER_CLASS_HPP

# include <glm/glm.hpp>
# include <Define.hpp>
# include <AModule.hpp>

class Water: public AModule
{
	public:
		Water(Model & model);
		~Water(void);

		void		distribute(void);
		void		waves(GLfloat coefficient);
		void		flood(GLfloat waterLevel);
		void		createVertices(void);
		
	private:
		Water(void);
		Water(Water const & model);
		Water &		operator=(Water const & rhs);

		void		createColors(void);
		void		createElements(void);
		void		createNormals(void);

		void		assignWaterLevel(GLfloat water, GLuint start, GLuint end, GLuint step);
		void		distributeGo(int adjacent[8], GLuint skip[6], GLuint pos, int flag);
		void		distributeBack(void);

		GLfloat *	_terrainVertices;
		GLfloat		_floodTop;
};

#endif /* ! WATER_CLASS_HPP */
