#ifndef _TITAN_D3D9TEXTURE_HH
#define _TITAN_D3D9TEXTURE_HH

#include "D3D9Prerequisites.h"
#include "TitanTexture.h"

namespace Titan
{
	class _D3D9DllExport D3D9Texture : public Texture
	{
	public:
		D3D9Texture(ResourceMgr* mgr,const String& name, ResourceHandle id, const String& group);

		~D3D9Texture();

	protected:
		void	loadImpl();

		void	unloadImpl();

		void	_loadNormalTex();

		void	_loadCubeTex();

		void	_perlinNoiseImpl(float scale, int octaves, float falloff);

		void	_createCoreObject();

		void	_create2DTex();


	protected:
		IDirect3DTexture9*		m2DTexture;

	};

	void _D3D9DllExport WINAPI perlinCallback(D3DXVECTOR4* pOut, 
		const D3DXVECTOR2* pTexCoord, 
		const D3DXVECTOR2* pTexelSize, void* pData);

}
#endif