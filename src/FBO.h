#ifndef FBO_H
#define FBO_H

#include <GL/glew.h>



class FBO
{
	GLuint m_FBO;
	GLuint m_Texture;
	GLuint m_Depth;
	GLint m_InternalType;

public:

	FBO()
	{
		m_FBO = 0;
		m_Texture = 0;
		m_Depth = 0;
		m_InternalType = GL_NONE;
	}

	~FBO()
	{
		if(m_FBO != 0)
		{
			glDeleteFramebuffers(1, &m_FBO);
		}
		if(m_Texture != 0)
		{
			glDeleteTextures(1, &m_Texture);
		}
		if(m_Depth != 0)
		{
			glDeleteTextures(1, &m_Depth);
		}

	}

	virtual void Init(int width, int height, bool withDepth, GLenum internalType)
	{
		m_InternalType = internalType;

		GLenum format = 0, type = 0;

		switch(m_InternalType)
		{
			case GL_RGB32F:
				format = GL_RGB;
				type = GL_FLOAT;
				break;
			case GL_R32F:
				format = GL_RED;
				type = GL_FLOAT;
				break;
			case GL_NONE:
				break;
			default:
				throw 1;
		}

		//Creating FBO
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		//Creating textures
		if(m_InternalType != GL_NONE)
		{
			glGenTextures(1, &m_Texture);
			glBindTexture(GL_TEXTURE_2D, m_Texture);

			glTexImage2D(GL_TEXTURE_2D, 0, m_InternalType, width, height, 0, format, type, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

/*			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE); */

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);


			glDrawBuffer(GL_COLOR_ATTACHMENT0);
		}
		if(withDepth)
		{
			glGenTextures(1, &m_Depth);
			glBindTexture(GL_TEXTURE_2D, m_Depth);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_Depth, 0);

			//glDrawBuffer(GL_NONE);
		}


		glBindFramebuffer(GL_FRAMEBUFFER, 0);


	}

	void BindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void BindForReading(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		if (m_InternalType == GL_NONE)
		{
			glBindTexture(GL_TEXTURE_2D, m_Depth);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, m_Texture);
		}
	}



};


#endif //FBO_H
