#include "Moteur/Tools/Shader.h"
#include <cstdlib>
#include <fstream>

Shader::Shader(std::string_view InShaderName)
{
	static std::filesystem::path shaderDir;
	Shader::InitializeShaderDir(shaderDir, false);

	std::ifstream shaderIn(shaderDir / InShaderName, std::ios::binary);
	if (shaderIn.is_open())
	{
		shaderIn.seekg(0, std::ios::end);
		m_size = shaderIn.tellg();
		shaderIn.seekg(0, std::ios::beg);
		m_data = malloc(m_size);
		if (m_data)
		{
			shaderIn.read((char*)m_data, m_size);
		}
	}
}

Shader::~Shader()
{
	free(m_data);
}

void Shader::InitializeShaderDir(std::filesystem::path& InOutShaderDir, bool bInForceReinitialize)
{
	if (bInForceReinitialize || InOutShaderDir.empty())
	{
		//Get module nullptr (this) result in "C:/.../filepath/myexecutable.exe"
		wchar_t moduleFileName[MAX_PATH];
		GetModuleFileNameW(nullptr, moduleFileName, MAX_PATH);

		InOutShaderDir = moduleFileName;
		InOutShaderDir.remove_filename();
	}
}