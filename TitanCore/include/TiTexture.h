#ifndef __TITAN_TEXTURE_HH
#define __TITAN_TEXTURE_HH

#include "TiPrerequisites.h"
#include "TiResource.h"
#include "TiCommon.h"
#include "TiPixelFormat.h"
#include "TiSharedPtr.h"
#include "TiHardwareBuffer.h"
#include "TiImage.h"

namespace Titan
{
	enum TexType
	{
		TT_1D	= 0,
		TT_2D	= 1,
		TT_3D	= 2,
		TT_CUBEMAP = 3,
	};
	enum TexUsage
	{
		TU_DEFAULT	= 0,
		TU_DYNAMIC	= 1,
		TU_RENDERTARGET = 2,
	};

	enum TexPool
	{
		TP_DEFAULT = 0,
		TP_MANAGED = 1,
		TP_SYSMEM  = 2,
	};


	class _DllExport Texture: public Resource
	{
	public:
		Texture(ResourceMgr* mgr,const String& name, ResourceHandle id, const String& group, bool isManual);

		~Texture();

		void		loadImage(const Image& img);

		void		setWidth(uint width){ mWidth = width; }

		uint		getWidth() const { return mWidth; }

		void		setHeight(uint height){ mHeight = height;}

		uint		getHeight() const { return mHeight; }

		//only for 3d texture
		void		setDepth(uint depth){ mDepth = depth; }

		uint		getDepth() const { return mDepth;}
		//will we need a upper limit?
		void		setMipmapLevel(uint level){ mMipmapsLevel = level;}

		uint		getMipmapLevel() const { return mMipmapsLevel; }

		void		setPixelFormat(PixelFormat format){ mPixelFormat = format; }

		PixelFormat	getPixelFormat() const { return mPixelFormat; }

		void		setTexType(TexType type){ mType = type; }

		TexType		getTexType() const { return mType; }

		void		setTexUsage(TexUsage usage){ mUsage = usage; }

		TexUsage	getTexUsage() const { return mUsage;}

		void		setTexPool(TexPool	pool){ mPool = pool;}

		TexPool		getTexPool() const { return mPool; }

		bool		hasAlpha() const;

		typedef HardwareBuffer::LockOptions LockOptions;

		virtual void		lockRect(uint level, const Box* rect,  LockOptions options, PixelBox* lockRect)  = 0;

		virtual void		unlockRect(uint level) = 0;


		void			generatePerlinNoise(float scale, int octaves, float falloff);

		virtual	void	_createCoreObject() = 0;

		//temp method?
		virtual void	save(const String& filename) = 0;

	protected:
		uint			mWidth;
		uint			mHeight;
		uint			mDepth;
		uint			mMipmapsLevel;
		PixelFormat		mPixelFormat;
		TexType			mType;
		TexUsage		mUsage;
		TexPool			mPool;

		

	protected:
		virtual	void		prepareImpl();

		virtual void		unprepareImpl();

		virtual void		_perlinNoiseImpl(float scale, int octaves, float falloff) = 0;

		virtual void		_loadImages( const ConstImagePtrList& images);

		virtual void		_loadImgsImpl(const ConstImagePtrList& images) = 0;

	};

	class _DllExport TexturePtr : public SharedPtr<Texture>
	{
	public:
		TexturePtr()
			: SharedPtr<Texture>()
		{}

		explicit TexturePtr(Texture* tex, SharedPtrFreeMethod freeMethod = SPFM_DELETE)
			: SharedPtr<Texture>(tex, freeMethod){}

		TexturePtr(const TexturePtr& r) : SharedPtr<Texture>(r) {} 
		TexturePtr(const ResourcePtr& r) : SharedPtr<Texture>()
		{
			pRep = static_cast<Texture*>(r.getPointer());
			pUseCount = r.useCountPointer();
			if (pUseCount)
			{
				++(*pUseCount);
			}

		}

		/// Operator used to convert a ResourcePtr to a TexturePtr
		TexturePtr& operator=(const ResourcePtr& r)
		{
			if (pRep == static_cast<Texture*>(r.getPointer()))
				return *this;
			release();

			pRep = static_cast<Texture*>(r.getPointer());
			pUseCount = r.useCountPointer();
			if (pUseCount)
			{
				++(*pUseCount);
			}

			return *this;
		}

	};
}
#endif
