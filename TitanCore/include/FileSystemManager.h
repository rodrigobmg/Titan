#ifndef _TITAN_FILESYSTEMMANAGER_HH
#define _TITAN_FILESYSTEMMANAGER_HH

#include "TitanPrerequisites.h"
#include "FileSystem.h"
#include "Singleton.h"

namespace Titan
{
	class _DllExport FileSystemManager : public Singleton<FileSystemManager>
	{
	public:
		FileSystemManager();

		~FileSystemManager();

		FileSystem*		load(const String& name, const String& type);

		void			unload(const String& name);

		void			unload(FileSystem* system);

		void	addFileSystemFactory(FileSystemFactory* factory);


		static FileSystemManager* getSingletonPtr();

		static FileSystemManager& getSingleton();

	public:
		typedef map<String, FileSystemFactory*>::type FileSystemFactoryMap;
		typedef map<String, FileSystem*>::type FileSystemMap;
	
	protected:
		FileSystemMap	mFileSystemMap;
		FileSystemFactoryMap	mFileSystemFactoryMap;
	};
}
#endif