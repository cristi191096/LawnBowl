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
	vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	unsigned int program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


unsigned int Shader::GetProgramID()
{
	return id;
}

Shader::Shader()
{
	fileName = "";
}

void Shader::Bind() const
{
	glUseProgram(id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

#pragma region UNIFORMS

int Shader::GetUniformLocation(const std::string & name)
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


void Shader::SetUniform1i(const std::string & name, int var)
{
	glUniform1i(GetUniformLocation(name), var);
}

void Shader::SetUniform1f(const std::string & name, float f)
{
	glUniform1f(GetUniformLocation(name), f);
}

void Shader::SetUniformVec2(const std::string & name, glm::vec2 InputVec)
{
	glUniform2f(GetUniformLocation(name), InputVec.x, InputVec.y);
}

void Shader::SetUniformVec3(const std::string & name, glm::vec3 InputVec)
{
	glUniform3f(GetUniformLocation(name), InputVec.x, InputVec.y, InputVec.z);
}

void Shader::SetUniformVec4(const std::string & name, glm::vec4 InputVec)
{
	glUniform4f(GetUniformLocation(name), InputVec.x, InputVec.y, InputVec.z, InputVec.w);
}

void Shader::SetUniformMat4(const std::string & name, glm::mat4 InputMat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(InputMat));
}

#pragma endregion setting the uniforms


Shader::Shader(const std::string& file)
{
	source = ReadShader(file);
	fileName = file;
	id = CreateShader(source.VertexSource, source.FragmentSource);
}


Shader::~Shader()
{
	glDeleteProgram(id);
}
