#include "D3D9HardwareBufferMgr.h"
#include "D3D9VertexBuffer.h"
#include "D3D9IndexBuffer.h"
#include "D3D9VertexDeclaration.h"

namespace Titan
{
	D3D9HardwareBufferMgr::D3D9HardwareBufferMgr()
	{

	}
	//-------------------------------------------------------------------------------//
	D3D9HardwareBufferMgr::~D3D9HardwareBufferMgr()
	{
	}
	//-------------------------------------------------------------------------------//
	VertexBufferPtr D3D9HardwareBufferMgr::createVertexBuffer(size_t vertexSize, size_t numVertices, VertexBuffer::Usage usage, bool useSystemMemory)
	{
		assert(numVertices > 0);
		D3D9VertexBuffer* buf = TITAN_NEW D3D9VertexBuffer(this, vertexSize, numVertices, usage, useSystemMemory);
		mVertexBuffers.insert(buf);
		return VertexBufferPtr(buf);
	}
	//-------------------------------------------------------------------------------//
	IndexBufferPtr D3D9HardwareBufferMgr::createIndexBuffer(size_t numIndexes, HardwareBuffer::Usage usage, bool useSystemMemory)
	{
		assert(numIndexes > 0);
		D3D9IndexBuffer* buf = TITAN_NEW D3D9IndexBuffer(this, numIndexes, usage, useSystemMemory);
		mIndexBuffers.insert(buf);
		return IndexBufferPtr(buf);
	}
	//-------------------------------------------------------------------------------//
	VertexDeclaration* D3D9HardwareBufferMgr::createVertexDeclaration()
	{
		D3D9VertexDeclaration* decl = TITAN_NEW D3D9VertexDeclaration();
		mVertexDeclarations.insert(decl);
		return decl;
	}
}