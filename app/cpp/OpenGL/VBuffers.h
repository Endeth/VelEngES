#pragma once

#include <GLES3/gl3.h>
#include "glm/glm.hpp"
#include "VVertices.h"
#include <memory>
#include <vector>

namespace Vel
{
	template <typename BufferDataPtr>
	class VBuffer
	{
	public:
		virtual ~VBuffer()
	{	
			glDeleteBuffers(_buffersCount, _buffersID);
			delete[] _buffersID;
		}
		void BindBuffer(GLushort BufferNumber = 0)
		{
			glBindBuffer(_bufferType, _buffersID[BufferNumber]);
		}
		void UnbindBuffer()
		{
			glBindBuffer(_bufferType, 0);
		}
		virtual void FillBuffer(BufferDataPtr Data, GLushort BufferNumber = 0)
		{
			glBindBuffer(_bufferType, _buffersID[BufferNumber]);
			glBufferData(_bufferType, _buffersSize, Data, _bufferUsage);
		}
		virtual void FillBuffer(GLsizei NumberOfElements, BufferDataPtr Data, GLushort BufferNumber = 0)
		{
			_buffersSize = NumberOfElements * sizeof(Vertex);
			glBindBuffer(_bufferType, _buffersID[BufferNumber]);
			glBufferData(_bufferType, _buffersSize, Data, _bufferUsage);
		}

	protected:
		VBuffer(GLushort BuffersCount = 1)
		{
			_buffersCount = BuffersCount;
			_buffersID = new GLuint[_buffersCount];
			glGenBuffers(_buffersCount, _buffersID);
		}
		VBuffer(GLsizei NumberOfElements, GLushort BuffersCount = 1)
		{
			_buffersCount = BuffersCount;
			_buffersSize = NumberOfElements;
			_buffersID = new GLuint[_buffersCount];
			glGenBuffers(_buffersCount, _buffersID);
		}

		GLuint *_buffersID;
		GLushort _buffersCount;
		GLenum _bufferType;
		GLenum _bufferUsage;
		GLsizei _buffersSize;

	};

	class VArrayBuffer : public VBuffer<Vertex*>
	{
	public:
		VArrayBuffer(GLushort BuffersCount = 1, GLenum BufferUsage = GL_STATIC_DRAW) : VBuffer(BuffersCount)
		{
			_bufferType = GL_ARRAY_BUFFER;
			_bufferUsage = BufferUsage;
			_buffersSize = sizeof(Vertex);
		}
		VArrayBuffer(GLsizei NumberOfElements, GLushort BuffersCount = 1, GLenum BufferUsage = GL_STATIC_DRAW) : VBuffer(NumberOfElements, BuffersCount)
		{
			_bufferType = GL_ARRAY_BUFFER;
			_bufferUsage = BufferUsage;
			_buffersSize *= sizeof(Vertex);
		}
	};

	class VElementArrayBuffer : public VBuffer<GLuint*>
	{
	public:
		VElementArrayBuffer(GLushort BuffersCount = 1, GLenum BufferUsage = GL_STATIC_DRAW) : VBuffer(BuffersCount)
		{
			_bufferType = GL_ELEMENT_ARRAY_BUFFER;
			_bufferUsage = BufferUsage;
			_buffersSize = sizeof(GLuint);
		}
		VElementArrayBuffer(GLsizei NumberOfElements, GLushort BuffersCount = 1, GLenum BufferUsage = GL_STATIC_DRAW) : VBuffer(NumberOfElements, BuffersCount)
		{
			_bufferType = GL_ELEMENT_ARRAY_BUFFER;
			_bufferUsage = BufferUsage;
			_buffersSize *= sizeof(GLuint);
		}
	};
}