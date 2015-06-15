#ifndef GLOBJECT_CLASS_HPP
# define GLOBJECT_CLASS_HPP

#include <Shader.hpp>
#include <AModule.hpp>

class GLObject
{
	public:
		GLObject(AModule const & module, Shader const & shader);
		~GLObject(void);
		void				setTerrainState(void);
		void				setDropState(void);
		void				setWaterState(void);
		void				setBordersState(void);
		void				setWaterBordersState(void);
		void				freeResources(void);

	private:	
		GLObject(void);
		GLObject(GLObject const & model);
		GLObject &			operator=(GLObject const & rhs);

		void				generateVBO(GLenum type);
		void				generateEBO(void);
		void				generateCBO(void);
		void				generateNBO(void);
		void				generatePBO(void);
		void				generateVAO(void);

		void				setVBO(void);
		void				setCBO(void);
		void				setNBO(void);
		void				setPBO(void);

		GLuint				_vao;
		GLuint				_vbo;
		GLuint				_pbo;
		GLuint				_ebo;
		GLuint				_cbo;
		GLuint				_nbo;
		AModule	const &		_module;
		Shader const &		_shader;
};

#endif /* ! GLOBJECT_CLASS_HPP */
