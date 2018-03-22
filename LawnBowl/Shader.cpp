#include "Shader.h"


ShaderSource Shader::ReadShader(const std::string & filePath)
{
	std::ifstream shaderFile(filePath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream strStream[2];
	ShaderType type = ShaderType::NONE;

	while (getline(shaderFile, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				//set to vertex shader
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				//set to fragment shader
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			strStream[(int)type] << line << '\n';
		}
	}

	return { strStream[0].str(), strStream[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string source)
{
	unsigned int shaderID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);
	//Error Handling
	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) 
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, message);
		std::string shaderTypeText;
		if (type == GL_VERTEX_SHADER)
			shaderTypeText = "VERTEX";
		else if (type == GL_FRAGMENT_SHADER)
			shaderTypeText = "FRAGMENT";
		else if (type == GL_TESS_EVALUATION_SHADER)
			shaderTypeText = "TESS EVALUATION";
		else if (type == GL_GEOMETRY_SHADER)
			shaderTypeText = "GEOMETRY";
		else if (type == GL_TESS_CONTROL_SHADER)
			shaderTypeText = "TESS CONTROL";

		std::cout << "Error compiling " << shaderTypeText << " shader: " << std::endl;
		std::cout << message << std::endl;

		return 0;
	}

	return shaderID;
}

unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::GetUniformLocation(const std::string & name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
		return uniformLocationCache[name];
	}
	int location = glGetUniformLocation(id, name.c_str());

	if (location == -1) {
		std::cout << "Uniform " << name << " doesn't exist" << std::endl;
	}
	
	uniformLocationCache[name] = location;
	return location;
}

unsigned int Shader::GetProgramID()
{
	return id;
}

void Shader::Bind() const
{
	glUseProgram(id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

Shader::Shader(const std::string& file)
{
	source = ReadShader(file);

	id = CreateShader(source.VertexSource, source.FragmentSource);
}


Shader::~Shader()
{
	glDeleteProgram(id);
}
