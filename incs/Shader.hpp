#ifndef SHADER_CLASS_HPP
# define SHADER_CLASS_HPP

# include <glfw/glfw3.h>

class Shader
{
	public:
		Shader(void);
		~Shader(void);
		GLint					getAPosition(void) const;
		GLint					getAInstance(void) const;
		GLint					getAColors(void) const;
		GLint					getANormals(void) const;
		GLint					getUProjection(void) const;
		GLint					getULight(void) const;
		GLint					getUModel(void) const;
		GLint					getUView(void) const;
		void					freeResources(void);

	private:
		Shader(Shader const & model);
		Shader &				operator=(Shader const & rhs);
		void					compile(void);
		void					link(void);
		void					checkStatus(void);
		void					setVertexAttributes(void);
		void					setFragmentAttributes(void);

		GLint					_aPosition;
		GLint					_aInstance;
		GLint					_aColors;
		GLint					_aNormals;
		GLint					_uProjection;
		GLint					_uLight;
		GLint					_uModel;
		GLint					_uView;
		GLuint					_vertex;
		GLuint					_fragment;
		GLuint 					_id;
		GLint					_vertex_status;
		GLint					_fragment_status;

		static GLchar const	*	_vertexSource;
		static GLchar const *	_fragmentSource;

};

#endif /* ! SHADER_CLASS_HPP */
