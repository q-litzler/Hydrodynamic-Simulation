#ifndef DROP_CLASS_HPP
# define DROP_CLASS_HPP

# include <glm/glm.hpp>
# include <Define.hpp>
# include <AModule.hpp>

class Drop: public AModule
{
	public:
		Drop(Model & model);
		~Drop(void);

		void			add(void);
		void			gravity(void);

	private:
		Drop(void);
		Drop(Drop const & model);
		Drop &			operator=(Drop const & rhs);
		void			createVertices(void);
		void			createElements(void);
		void			createColors(void);
		void			createNormals(void);
		
		GLuint			_dropBatch;
		GLfloat			_startHeight;
		glm::vec3		_gravity;
		GLfloat *		_water;
};

#endif /* ! DROP_CLASS_HPP */
