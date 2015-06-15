#include <iostream>

#include <Exceptions.hpp>
#include <Shader.hpp>

/*******************************************
	Constructors
*******************************************/

Shader::Shader(void) : _vertex(glCreateShader(GL_VERTEX_SHADER)), _fragment(glCreateShader(GL_FRAGMENT_SHADER))
{
	this->compile();
	this->link();
	this->checkStatus();
	this->setVertexAttributes();
	this->setFragmentAttributes();
	return;
}

/*******************************************
	Destructor
*******************************************/

Shader::~Shader(void)
{
	return ;
}

/*******************************************
	Accessors
*******************************************/

GLint			Shader::getAPosition(void) const
{
	return this->_aPosition;
}

GLint			Shader::getAInstance(void) const
{
	return this->_aInstance;
}

GLint			Shader::getAColors(void) const
{
	return this->_aColors;
}

GLint			Shader::getANormals(void) const
{
	return this->_aNormals;
}

GLint			Shader::getUProjection(void) const
{
	return this->_uProjection;
}

GLint			Shader::getULight(void) const
{
	return this->_uLight;
}

GLint			Shader::getUModel(void) const
{
	return this->_uModel;
}

GLint			Shader::getUView(void) const
{
	return this->_uView;
}

/*******************************************
	Member functions
*******************************************/

void			Shader::freeResources(void)
{
	glDeleteProgram(this->_id);
	glDeleteShader(this->_vertex);
	glDeleteShader(this->_fragment);
}

void			Shader::compile(void)
{
	glShaderSource(this->_vertex, 1, &Shader::_vertexSource, nullptr);
	glShaderSource(this->_fragment, 1, &Shader::_fragmentSource, nullptr);
	glCompileShader(this->_vertex);
	glCompileShader(this->_fragment);
}

void			Shader::link(void)
{
	this->_id = glCreateProgram();
	glAttachShader(this->_id, this->_vertex);
	glAttachShader(this->_id, this->_fragment);
	glLinkProgram(this->_id);
	glUseProgram(this->_id);
}

void			Shader::checkStatus(void)
{
	glGetShaderiv(this->_vertex, GL_COMPILE_STATUS, &this->_vertex_status);
	glGetShaderiv(this->_fragment, GL_COMPILE_STATUS, &this->_fragment_status);
	if (this->_vertex_status != GL_TRUE || this->_fragment_status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(this->_vertex, 512, NULL, buffer);
		std::cout << buffer << std::endl;
		throw invalidShadersException();
	}
}

void			Shader::setVertexAttributes(void)
{
	this->_aPosition = glGetAttribLocation(this->_id, "position");
	this->_aColors = glGetAttribLocation(this->_id, "vertexColor");
	this->_aNormals = glGetAttribLocation(this->_id, "normal");
	this->_aInstance = glGetAttribLocation(this->_id, "instance");
	this->_uView = glGetUniformLocation(this->_id, "view");
	this->_uProjection = glGetUniformLocation(this->_id, "projection");
	this->_uModel = glGetUniformLocation(this->_id, "model");
	this->_uLight = glGetUniformLocation(this->_id, "light");
}

void			Shader::setFragmentAttributes(void)
{
	glBindFragDataLocation(this->_id, 0, "outColor");
}

GLchar const *	Shader::_vertexSource =
	"#version 410 core\n"
	"in vec3 position;"
	"in vec3 instance;"
	"in vec3 normal;"
	"in vec4 vertexColor;"
	"out vec4 fragmentColor;"
	"uniform vec3 light;"
	"uniform mat4 model;"
	"uniform mat4 view;"
	"uniform mat4 projection;"
	"void main() {"
	"   gl_Position = projection * view * model * vec4(position + instance, 1.0);"
	"	vec3 lightRay = light - position;"
	"	float brightness = 0.6 + dot(normal, lightRay) / (length(normal) * length(lightRay));"
	"	brightness = clamp(brightness, 0, 1) + 0.25;"
	"	fragmentColor = vertexColor * brightness;"
	"}";

GLchar const *	Shader::_fragmentSource =
	"#version 410 core\n"
	"in vec4 fragmentColor;"
	"out vec4 outColor;"
	"void main() {"
	"	outColor = fragmentColor;"
	"}";
