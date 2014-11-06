#pragma once
#include <fstream>
#include <vector>

using namespace std;

typedef struct shaderData_t
{
public:
	~shaderData_t();

	char	*pStrName;	//User defined name of the shader
	GLchar	*pSrc;		//pointer to the source code
	GLint	 nLen;		//Length of the source code in bytes
	GLint	 nShaderID;	//OpenGL shader name
	GLint	 nProgID;	//OpenGL program name
}shaderData;

class CShaderMngr
{
protected:
	vector<std::pair<string, shaderData*>>	m_Shaders;

public:
	CShaderMngr(void);
	~CShaderMngr(void);

public:
	bool LoadShader(const char *strFileName, GLenum nShaderType, const char *strName);
	bool UseShader(const char *strName);
	void SetUniformData(const char *strShaderName, const char *strVariableName, float *pData, int nNumElements);
	void SetUniformData(const char *strShaderName, const char *strVariableName, int *pData, int nNumElements);

	shaderData* GetShaderData(const char *strProgName);

private:
	int	_loadShader(const char *strFileName, shaderData *pData);
	bool _compileShader(shaderData *pData, GLenum nShaderType);
	unsigned long _getFileLength(ifstream &inFile) const;
};

