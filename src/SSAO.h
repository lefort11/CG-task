#ifndef SSAO_H
#define SSAO_H

#include "FBO.h"


class GeometryPassTechnique
{
	FBO* m_pGBuffer;

public:
	GeometryPassTechnique(FBO* buffer)
	{
		m_pGBuffer = buffer;
	}

	void GeometryPassOn()
	{
		m_pGBuffer->BindForWriting();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	}


};

class SSAOTechnique
{

};

class BlurTechnique
{

};



#endif //SSAO_H
