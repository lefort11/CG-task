#ifndef ENGINE_H
#define ENGINE_H

#include <cmath>

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

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "LightningTechnique.h"
#include "GraphicalObject.h"


#include "Vertex.h"

#include "TangentSpace.h"

#define SHADOW_TEXTURE_UNIT GL_TEXTURE0
#define COLOR_TEXTURE_UNIT GL_TEXTURE1
#define NORMAL_TEXTURE_UNIT GL_TEXTURE2
#define SKYBOX_TEXTURE_UNIT GL_TEXTURE3







class Texture
{
	std::string m_Filename;
	GLenum m_TextureTarget;
	GLuint m_TextureObj;
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
		glGenTextures(1, &m_TextureObj);
		glBindTexture(m_TextureTarget, m_TextureObj);

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
		glBindTexture(m_TextureTarget, m_TextureObj);
	}


	~Texture()
	{
		FreeImage_Unload(m_pImage);
	}

};




class CubemapTexture
{
	std::string  m_Filenames[6];
	GLuint m_TextureObj;


public:
	CubemapTexture(std::string const& PosXFilename,
				   std::string const& NegXFilename,
				   std::string const& PosYFilename,
				   std::string const& NegYFilename,
				   std::string const& PosZFilename,
				   std::string const& NegZFilename)
	{
		m_Filenames[0] = PosXFilename;
		m_Filenames[1] = NegXFilename;
		m_Filenames[2] = PosYFilename;
		m_Filenames[3] = NegYFilename;
		m_Filenames[4] = PosZFilename;
		m_Filenames[5] = NegZFilename;
	}


	bool Load()
	{
		glGenTextures(1, &m_TextureObj);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureObj);


		FIBITMAP* bitmap = nullptr;
		int width, height;

		GLenum types[6] =
				{
						GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				};

		for(GLuint i = 0; i < 6; ++i)
		{
			bitmap = FreeImage_Load(FreeImage_GetFileType(m_Filenames[i].c_str()), m_Filenames[i].c_str());
			width = FreeImage_GetWidth(bitmap);
			height = FreeImage_GetHeight(bitmap);


			FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
			FreeImage_FlipVertical(pImage); // KEK

			glTexImage2D(types[i], 0, GL_RGBA, width, height,
						 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

			FreeImage_Unload(bitmap);
			FreeImage_Unload(pImage);

		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return true;
	}

	void Bind(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureObj);
	}

	~CubemapTexture()
	{
		glDeleteTextures(1, &m_TextureObj);
	}

};


class Skybox: public GraphicalObject
{
	CubemapTexture m_CubemapTex;

	static const Vertex skyboxVertices[];
	static const GLuint skyboxIndices[];
	static const glm::vec3 offset;

public:
	Skybox(std::string const& PosXFilename,
		   std::string const& NegXFilename,
		   std::string const& PosYFilename,
		   std::string const& NegYFilename,
		   std::string const& PosZFilename,
		   std::string const& NegZFilename):
			GraphicalObject(skyboxVertices, 8, skyboxIndices, 36, offset),
			m_CubemapTex(PosXFilename,NegXFilename, PosYFilename, NegYFilename, PosZFilename, NegZFilename)
	{
		m_CubemapTex.Load();
	}

	void Draw(OrbitalCamera const& camera)
	{
		m_CubemapTex.Bind(SKYBOX_TEXTURE_UNIT);

		GLint OldCullFaceMode;
		glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
		GLint OldDepthFuncMode;
		glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

//		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);

		glDepthMask(GL_FALSE);

		GraphicalObject::Draw(camera);

		glCullFace((GLenum)OldCullFaceMode);
		glDepthFunc((GLenum)OldDepthFuncMode);

	//	glDisable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);

	}


};




#endif //ENGINE_H
