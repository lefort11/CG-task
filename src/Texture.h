#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <freeimage.h>

class Texture
{
	std::string m_Filename;
	GLenum m_TextureTarget;
	GLuint m_TextureID;
	FIBITMAP* m_pImage;

public:
	Texture(GLenum TextureTarget, const std::string& FileName)
	{
		m_TextureTarget = TextureTarget;
		m_Filename = FileName;
		m_pImage = nullptr;
	}

	void Load()
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(m_TextureTarget, m_TextureID);

		FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(m_Filename.c_str()), m_Filename.c_str());
		unsigned width = FreeImage_GetWidth(bitmap);
		unsigned height = FreeImage_GetHeight(bitmap);


		m_pImage = FreeImage_ConvertTo32Bits(bitmap);
		FreeImage_FlipVertical(m_pImage); // KEK

		glTexImage2D(m_TextureTarget, 0, GL_RGBA, width, height,
					 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(m_pImage));
//		glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glGenerateMipmap(m_TextureTarget);
		glTexParameterf(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);


		FreeImage_Unload(bitmap);
	}

	void Bind(GLenum TextureUnit) const
	{
		glActiveTexture(TextureUnit);
		glBindTexture(m_TextureTarget, m_TextureID);
	}


	~Texture()
	{
		FreeImage_Unload(m_pImage);
		glDeleteTextures(1, &m_TextureID);
	}

};

#endif //TEXTURE_H
