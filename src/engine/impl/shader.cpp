#include "../shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, 0L, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, 0L, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void shader_load_glsl_from_source(const char* vertex_source, 
                    const char* fragment_source, Shader& program)
{
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_source, 0L);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_source, 0L);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	program.ID = glCreateProgram();
	glAttachShader(program.ID, vertex);
	glAttachShader(program.ID, fragment);
	glLinkProgram(program.ID);
	checkCompileErrors(program.ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void shader_load_glsl(const char* vertexPath, 
                      const char* fragmentPath, 
                      Shader& program)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure &e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	
	shader_load_glsl_from_source(vShaderCode, fShaderCode, program);
}

void shader_use_program(const Shader &program)
{
	glUseProgram(program.ID);
}

void shader_upload_int(const Shader& program, const char* name, i32 v)
{
	glUniform1i(glGetUniformLocation(program.ID, name), v);
}

void shader_upload_float(const Shader& program, const char* name, f32 v)
{
	glUniform1f(glGetUniformLocation(program.ID, name), v);
}

void shader_upload_vec2(const Shader& program, const char* name, f32 x, f32 y)
{
	glUniform2f(glGetUniformLocation(program.ID, name), x, y);
}


void shader_upload_vec3(const Shader& program, 
    const char* name, f32 x, f32 y, f32 z)
{
	glUniform3f(glGetUniformLocation(program.ID, name), x, y, z);
}

void shader_upload_vec4(const Shader& program, 
	const char* name, f32 x, f32 y, f32 z, f32 w)
{
	glUniform4f(glGetUniformLocation(program.ID, name), x, y, z, w);
}


void shader_upload_color(const Shader& program,
    const char* name, const Color& color)
{
	shader_upload_vec4(program, name, color.r/255.0, color.g/255.0, color.b/255.0, color.a/255.0);
}

void shader_upload_float_array(const Shader& program, const char* name, 
	const f32* array, unsigned int size)
{
	glUniform1fv(glGetUniformLocation(program.ID, name), size, array);
}

void shader_delete_program(const Shader& program)
{
	glDeleteProgram(program.ID);
}

void shader_upload_mat4(const Shader& program, 
	const char* name, const float* mat)
{
	GLint location = glGetUniformLocation(program.ID, name);
	if (location == -1) {
		printf("Warning: Uniform '%s' not found in shader!\n", name);
		return;
  	}

	glUniformMatrix4fv(location, 1, GL_FALSE, mat);
}