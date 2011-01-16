#ifndef _TITAN_D3D9MAPPINGS_H
#define _TITAN_D3D9MAPPINGS_H

#include "D3D9Prerequisites.h"
#include "TitanCommon.h"
#include "HardwareBuffer.h"

namespace Titan
{
	class _D3D9DllExport D3D9Mappings
	{
	public:
		/// return a D3D9 equivalent for a Ogre ShadeOptions value
		static DWORD convertToD3D9(ShadeOptions so);
		/// return a D3D9 equivalent for a Ogre CillingMode value
		static DWORD convertToD3D9(CullingMode cm, bool flip);
		/// return a D3D9 equivalent for a Ogre FogMode value
		static D3DFOGMODE convertToD3D9(FogMode fm);
		/// return a D3D9 equivalent for a Ogre PolygonMode value
		static D3DFILLMODE convertToD3D9(PolygonMode level);

		static DWORD convertToD3D9(HardwareBuffer::Usage usage);

		static D3DDECLTYPE convertToD3D9(VertexElementType vType);
		/// Get vertex semantic
		static D3DDECLUSAGE convertToD3D9(VertexElementSemantic sem);

		static DWORD convertToD3D9(HardwareBuffer::LockOptions options, HardwareBuffer::Usage usage);

		static D3DXMATRIX makeD3DXMatrix( const Matrix4& mat );

		static Matrix4 convertD3DXMatrix( const D3DXMATRIX& mat );
	};
}
#endif