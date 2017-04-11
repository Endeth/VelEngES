
#include "VGLSLShader.h"
#include <android/log.h>
namespace Vel
{
	using namespace std;

	VGLSLShader::VGLSLShader()
	{
		_totalShaders = 0;
		_shaders[VERTEX_SHADER] = 0;
		_shaders[FRAGMENT_SHADER] = 0;
		_attributeList.clear();
		_uniformLocationList.clear();
	}



	VGLSLShader::~VGLSLShader()
	{
		_attributeList.clear();
		_uniformLocationList.clear();
		glDeleteProgram(_program);
	}

	void VGLSLShader::LoadFromString(GLenum Type, const string & Source)
	{
		GLuint shader = glCreateShader(Type);

		const char* ptmp = Source.c_str();
		glShaderSource(shader, 1, &ptmp, NULL);

		GLint status;
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
			__android_log_print(ANDROID_LOG_INFO, "OpenGL", "Could not compile %s shader:\n%s\n",
								Type == GL_VERTEX_SHADER ? "vertex" : "fragment",
								infoLog);
			delete[] infoLog;
		}
		_shaders[_totalShaders++] = shader;
	}

	void VGLSLShader::LoadFromFile(GLenum Shader, const string & Filename) //TODO get resources from android
	{
		/*ifstream fp;
		fp.open(Filename.c_str(), ios_base::in);
		if (fp)
		{
			string line, buffer;
			while (getline(fp, line))
			{
				buffer.append(line);
				buffer.append("\r\n");
			}
			LoadFromString(Shader, buffer);
		}
		else
			cerr << "Error loading shader: " << Filename << endl;*/
	}

	void VGLSLShader::CreateAndLinkProgram()
	{
		_program = glCreateProgram();
		if (_shaders[VERTEX_SHADER] != 0)
		{
			glAttachShader(_program, _shaders[VERTEX_SHADER]);
		}
		if (_shaders[FRAGMENT_SHADER] != 0)
		{
			glAttachShader(_program, _shaders[FRAGMENT_SHADER]);
		}

		GLint status;
		glLinkProgram(_program);
		glGetProgramiv(_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog = new GLchar[infoLogLength];
			glGetProgramInfoLog(_program, infoLogLength, NULL, infoLog);
			__android_log_print(ANDROID_LOG_INFO, "OpenGL", "Could not link shader:\n%s\n", infoLog);
			delete[] infoLog;
		}

		glDeleteShader(_shaders[VERTEX_SHADER]);
		glDeleteShader(_shaders[FRAGMENT_SHADER]);
	}

	void VGLSLShader::Activate()
	{
		glUseProgram(_program);
	}

	void VGLSLShader::Deactivate()
	{
		glUseProgram(0);
	}

	void VGLSLShader::SetAttributes(const vector<string> &Attributes)
	{
		for (auto &Att : Attributes)
		{
			SetAttributes(Att);
		}
	}
	void VGLSLShader::SetUniforms(const vector<string>& Uniforms)
	{
		for (auto &Uni : Uniforms)
		{
			SetUniforms(Uni);
		}
	}
	void VGLSLShader::SetAttributes(const string & Attribute)
	{
		auto att = Attribute.c_str();
		_attributeList[Attribute] = glGetAttribLocation(_program, att);
	}

	void VGLSLShader::SetUniforms(const string & Uniform)
	{
		auto uni = Uniform.c_str();
		_uniformLocationList[Uniform] = glGetUniformLocation(_program, uni);
	}

	GLint VGLSLShader::GetAttribute(const string& Attribute)
	{
		return _attributeList[Attribute];
	}

	GLint VGLSLShader::GetUniform(const string& Uniform)
	{
		return _uniformLocationList[Uniform];
	}

	void VGLSLShader::DeleteShaderProgram()
	{
		glDeleteProgram(_program);
	}
}