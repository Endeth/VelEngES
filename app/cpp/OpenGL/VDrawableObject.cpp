#include "VDrawableObject.h"
#include <android/log.h>
namespace Vel
{
	using namespace std;

	VBasicDrawableObject::VBasicDrawableObject()
	{
		glGenVertexArrays(1, &_vaoID);
	}

	VBasicDrawableObject::~VBasicDrawableObject()
	{

		glDeleteVertexArrays(1, &_vaoID);
	}

	void VBasicDrawableObject::Draw()
	{
		_shader->Activate();

        BindAdditionalDrawingOptions();
		glBindVertexArray(_vaoID);
        __android_log_print(ANDROID_LOG_INFO, "OpenGL", "VBasicDrawableObject::Draw():\nIndices Size: %x\n",  _indices.size());
		glDrawElements(_primitive, _indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		UnbindAdditionalDrawingOptions();
		_shader->Deactivate();
	}

	void VBasicDrawableObject::DrawWithImposedShader()
	{
		BindAdditionalDrawingOptions();
		glBindVertexArray(_vaoID);

		glDrawElements(_primitive, _indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		UnbindAdditionalDrawingOptions();
	}

	void VBasicDrawableObject::DrawVerticesWithImposedShader()
	{
		BindAdditionalDrawingOptions();
		glBindVertexArray(_vaoID);

		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());

		glBindVertexArray(0);
		UnbindAdditionalDrawingOptions();
	}

}