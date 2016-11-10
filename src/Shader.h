#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Shader
{
	GLuint m_ProgramID;

public:
	Shader(): m_ProgramID(0) {}
	void Load(char const* vertexFilePath, char const* fragmentFilePath)
	{
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//loading vertex shader code
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertexFilePath, std::ios::in);
		if(VertexShaderStream.is_open())
		{
			std::string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}

		//loading fragment shader code
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragmentFilePath, std::ios::in);
		if(FragmentShaderStream.is_open()){
			std::string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}

		GLint result = GL_FALSE;
		GLint infoLogLength;

		//compiling vertex shader
		printf("%s compiltation\n", vertexFilePath);
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
		glCompileShader(VertexShaderID);

		//checking vertex shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if ( infoLogLength > 0 ){
			std::vector<char> VertexShaderErrorMessage(static_cast<unsigned long>(infoLogLength+1));
			glGetShaderInfoLog(VertexShaderID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
			fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
		}

		//compiling fragment shader
		printf("%s compilation\n", fragmentFilePath);
		char const* FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
		glCompileShader(FragmentShaderID);

		//checking fragment shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if ( infoLogLength > 0 ){
			std::vector<char> FragmentShaderErrorMessage(static_cast<unsigned long>(infoLogLength+1));
			glGetShaderInfoLog(FragmentShaderID, infoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
		}

		//making shader program
		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID, VertexShaderID);
		glAttachShader(m_ProgramID, FragmentShaderID);
		glLinkProgram(m_ProgramID);

		//checking shader program
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if ( infoLogLength > 0 ){
			std::vector<char> ProgramErrorMessage(static_cast<unsigned long>(infoLogLength+1));
			glGetProgramInfoLog(m_ProgramID, infoLogLength, NULL, &ProgramErrorMessage[0]);
			fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
		}

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
	}

	void DeleteProgram() const
	{
		glUseProgram(0);
		glDeleteProgram(m_ProgramID);
	}

	void UseProgram() const
	{
		glUseProgram(m_ProgramID);
	}

	GLuint Program() const
	{
		return m_ProgramID;
	}

	~Shader()
	{
		DeleteProgram();
	}
};


#endif //SHADER_H
