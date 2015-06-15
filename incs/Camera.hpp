#ifndef CAMERA_CLASS_HPP
# define CAMERA_CLASS_HPP

#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	public:
		Camera(void);
		~Camera(void);
		glm::mat4		getLookAt(void) const;
		void			setPosition(glm::vec3 position);
		void			setTarget(glm::vec3 position);
		void			move(glm::vec3 position);

	private:
		Camera(Camera const & model);
		Camera &		operator=(Camera const & rhs);

		glm::vec3		_position;
		glm::vec3		_distance;
		glm::vec3		_target;
		glm::vec3		_axis;
		glm::vec3 		_right;
		glm::vec3 		_up;
		glm::vec3 		_camDown;
		glm::mat4		_lookAt;
};

#endif /* ! CAMERA_CLASS_HPP */
