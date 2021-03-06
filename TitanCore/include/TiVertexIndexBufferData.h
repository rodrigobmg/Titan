#ifndef __TITAN_VERTEXINDEXDATA_HH
#define __TITAN_VERTEXINDEXDATA_HH

#include "TiPrerequisites.h"
#include "TiIndexBuffer.h"

namespace Titan
{
	class _DllExport VertexData : public GeneralAlloc
	{
	protected:
		VertexData(const VertexData& rhs);

		VertexData& operator=(const VertexData& rhs);

		HardwareBufferMgr* mMgr;
	public:
		VertexData(HardwareBufferMgr* mgr = 0);

		VertexData(VertexDeclaration* decl, VertexBufferBinding* binding);
		
		~VertexData();

		VertexDeclaration*		vertexDecl;
		VertexBufferBinding*	vertexBufferBinding;

		size_t vertexStart;
		/// The number of vertices used in this operation
		size_t vertexCount;

		bool mDeleteDclBinding;
	};


	class _DllExport IndexData: public  GeneralAlloc
	{
	protected:
		IndexData(const IndexData& rhs);

		IndexData& operator=(const IndexData& rhs);

	public:
		IndexData();

		~IndexData();

		IndexBufferPtr	indexBuffer;

		size_t indexStart;
		/// The number of vertices used in this operation
		size_t indexCount;

	};
}
#endif