#include <Camera.hpp>

/*******************************************
	Constructors
*******************************************/

Camera::Camera(void) : _position(glm::vec3(0.0f, 0.0f, 0.0f)) 
{
	this->_distance = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_target = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_axis = glm::normalize(this->_position - this->_target);
	this->_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0, 0.0f), _axis));
	this->_up = glm::cross(_axis, _right);
	this->_lookAt = glm::mat4();
}

/*******************************************
	Destructor
*******************************************/

Camera::~Camera(void)
{
	return;
}

/*******************************************
	Accessors - getters
*******************************************/

glm::mat4		Camera::getLookAt(void) const
{
	return glm::lookAt(this->_position, this->_target, this->_up);
}

/*******************************************
	Accessors - setters
*******************************************/

void			Camera::setPosition(glm::vec3 position)
{
	this->_position = position;
	this->_axis = glm::normalize(this->_position - this->_target);
	this->_right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0, 0.0f), _axis));
	this->_up = glm::cross(_axis, _right);
}

void			Camera::setTarget(glm::vec3 target)
{
	this->_target = target;
}

/*******************************************
	Memebr Functions
*******************************************/

void			Camera::move(glm::vec3 position)
{
	this->_position -= position;
	this->setPosition(this->_position);
}
