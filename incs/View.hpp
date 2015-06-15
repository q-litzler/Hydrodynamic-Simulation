#ifndef VIEW_CLASS_HPP
# define VIEW_CLASS_HPP

# include <Define.hpp>
# include <glfw/glfw3.h>
# include <glm/glm.hpp>

# include <Camera.hpp>
# include <Model.hpp>
# include <GLObject.hpp>

class View
{
	typedef void			(View::*fptr) (void);

	public:
		View(Model & model);
		~View(void);
		void				render(void);
		void				loadTerrain(void);

	private:
		View(void);
		View(View const & model);
		View &				operator=(View const & rhs);
		void				init(void);
		void				setupCamera(void);
		void				flood(void);
		void				rain(void);
		void				waves(void);
		void				drain(void);
		void				tsunami(void);

		Model &				_model;
		Shader *			_shader;
		int const			_width;
		int	const			_height;
		glm::mat4			_projection;
		Camera				_camera;
		GLFWwindow *		_window;
		bool				_tsunami;

		static View *		_GLFW;
		static void			inputHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
		static fptr			_activate[SCENARIOS];
};

#endif /* ! VIEW_CLASS_HPP */
