#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <View.hpp>
#include <Camera.hpp>
#include <Exceptions.hpp>

/*******************************************
	Constructors
*******************************************/

View::View(Model & model) : _model(model), _width(model.getWidth()), _height(model.getHeight())
{
	this->_projection = glm::perspective(
		glm::radians(45.0f),
		static_cast<float>(this->_width) / static_cast<float>(this->_height),
		1.0f, 150.0f
	);
	this->_tsunami = false;
	this->init();
	std::cout << CYAN << "Use arrows to move and + - to scale" << WHITE << std::endl;
	this->_shader = new Shader();
	View::_GLFW = this;
}

/*******************************************
	Destructor
*******************************************/

View::~View(void)
{
	if (this->_shader)
	{
		delete this->_shader;
	}
	return;
}

/*******************************************
	Member functions
*******************************************/

void				View::init(void)
{
	if (!glfwInit())
	{
		throw GUIinitFail();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	this->_window = glfwCreateWindow(this->_width, this->_height, "Hydrodynamic Simulation", nullptr, nullptr);
	if (!this->_window)
	{
		glfwTerminate();
		throw GUIinitFail();
	}
	glfwMakeContextCurrent(this->_window);
	glfwSetKeyCallback(this->_window, &View::inputHandler);
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		throw GUIinitFail();
	}
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
}

void			View::setupCamera()
{
	// Set initial camera position
	View::_camera.setPosition(glm::vec3(0.0f, 9.0f, 9.0f));
	// Set Projection and model
	glUniformMatrix4fv(this->_shader->getUProjection(), 1, GL_FALSE, glm::value_ptr(this->_projection));
	glUniform3fv(this->_shader->getULight(), 1, glm::value_ptr(this->_model.getLight()));
	glUniformMatrix4fv(this->_shader->getUView(), 1, GL_FALSE, glm::value_ptr(this->_camera.getLookAt()));
	glUniformMatrix4fv(this->_shader->getUModel(), 1, GL_FALSE, glm::value_ptr(this->_model.getMatrix()));
}

void			View::flood(void)
{
	this->_model.getWater()->flood(UNIT);
}

void			View::rain(void)
{
	this->_model.getDrop()->add();
	this->_model.getDrop()->gravity();
}

void			View::waves(void)
{
	this->_model.getWater()->waves(WAVES_COEFFICIENT);
}

void			View::drain(void)
{
	this->_model.getWater()->flood(-UNIT * DRAIN_COEFFICIENT);
}

void			View::tsunami(void)
{
	if (!this->_tsunami)
	{
		this->_model.getWater()->waves(this->_model.getTop() * TSUNAMI_COEFFICIENT);
		this->_tsunami = true;
	}
}

void			View::render(void)
{
	Terrain *		terrain = this->_model.getTerrain();
	Borders *		borders = this->_model.getBorders();
	Water *			water = this->_model.getWater();
	WaterBorders *	waterBorders = this->_model.getWaterBorders();
	Drop *			drop = this->_model.getDrop();

	GLObject		GLTerrain(*terrain, *this->_shader);
	GLObject		GLBorders(*borders, *this->_shader);
	GLObject		GLWater(*water, *this->_shader);
	GLObject		GLWaterBorders(*waterBorders, *this->_shader);
	GLObject		GLDrop(*drop, *this->_shader);

	GLuint			terrainSize = terrain->getElementsSize();
	GLuint			bordersSize = borders->getElementsSize();
	GLuint			waterSize = water->getElementsSize();
	GLuint			waterBordersSize = waterBorders->getElementsSize();
	GLuint			dropSize = drop->getElementsSize();

	this->setupCamera();
	while (!glfwWindowShouldClose(this->_window))
	{
		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		(this->*_activate[this->_model.getScenario()])();
		water->distribute();
		waterBorders->updateWaterBorders();

		glEnable(GL_DEPTH_TEST);
		GLTerrain.setTerrainState();
		glDrawElements(GL_TRIANGLE_STRIP, terrainSize, GL_UNSIGNED_INT, 0);
		
		glEnable(GL_BLEND);
		GLDrop.setDropState();
		glDrawElementsInstanced(GL_TRIANGLE_STRIP, dropSize, GL_UNSIGNED_INT, 0, drop->getInstances());
		
		GLWater.setWaterState();
		glDrawElements(GL_TRIANGLE_STRIP, waterSize, GL_UNSIGNED_INT, 0);
		GLWaterBorders.setWaterBordersState();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, waterBordersSize);
		glDisable(GL_BLEND);

		glDisable(GL_DEPTH_TEST);
		GLBorders.setBordersState();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, bordersSize);

		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}
	this->_shader->freeResources();
	GLTerrain.freeResources();
}

/*******************************************
	Static Attributes and Methods
*******************************************/

View *			View::_GLFW = nullptr;

void			View::inputHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static_cast<void>(scancode);
	static_cast<void>(mods);
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_LEFT)
	{
		View::_GLFW->_model.setRotation(-0.05f);
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		View::_GLFW->_model.setRotation(0.05f);
	}
	else if (key == GLFW_KEY_UP)
	{
		View::_GLFW->_camera.move(glm::vec3(0.0f, 1.0f, .0f));
	}
	else if (key == GLFW_KEY_DOWN)
	{
		View::_GLFW->_camera.move(glm::vec3(0.0f, -1.0f, .0f));
	}
	else if (key == GLFW_KEY_EQUAL || key == GLFW_KEY_KP_ADD)
	{
		View::_GLFW->_model.setScaleFactor(1.1f);
	}
	else if (key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT)
	{
		View::_GLFW->_model.setScaleFactor(0.9f);
	}
	else if (key == GLFW_KEY_F && View::_GLFW->_model.getScenario() != RAIN)
	{
		View::_GLFW->_model.setScenario(FLOOD);
		View::_GLFW->_model.getWater()->createVertices();
	}
	else if (key == GLFW_KEY_W && View::_GLFW->_model.getScenario() != RAIN)
	{
		View::_GLFW->_model.setScenario(WAVES);
		View::_GLFW->_model.getWater()->createVertices();
	}
	else if (key == GLFW_KEY_D && View::_GLFW->_model.getScenario() != RAIN)
	{
		View::_GLFW->_model.setScenario(DRAIN);
	}
	glUniformMatrix4fv(View::_GLFW->_shader->getUModel(), 1, GL_FALSE, glm::value_ptr(View::_GLFW->_model.getMatrix()));
	glUniformMatrix4fv(View::_GLFW->_shader->getUView(), 1, GL_FALSE, glm::value_ptr(View::_GLFW->_camera.getLookAt()));
}

View::fptr		View::_activate[SCENARIOS] = {
	&View::flood,
	&View::rain,
	&View::waves,
	&View::drain,
	&View::tsunami
};