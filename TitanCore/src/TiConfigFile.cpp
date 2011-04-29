#include "TitanStableHeader.h"
#include "TiConfigFile.h"
#include "TiException.h"

namespace Titan
{
	ConfigFile::ConfigFile()
	{

	}
	//-------------------------------------------------------------------------------//
	ConfigFile::~ConfigFile()
	{
		SectionMap::iterator it = mSectionMap.begin(), itend = mSectionMap.end();
		while(it != itend)
		{
			(it->second)->clear();
			TITAN_DELETE_T(it->second, PropertyMap, MEMCATEGORY_GENERAL);
			++it;
		}
		mSectionMap.clear();
	}
	//-------------------------------------------------------------------------------//
	void ConfigFile::load(const String& name)
	{
		std::ifstream fp;

		fp.open(name.c_str(), std::ios::in | std::ios::binary );
		
		if(fp == 0)
		{
			TITAN_EXCEPT(Exception::EXCEP_ITEM_NOT_FOUND,
				" Can not find config file called: "+ name, 
				"ConfigFile::load");
			return ;
		}
		
		String line, first, second;
		PropertyMap* currentMap = 0;
		while(!fp.eof())
		{
			getline(fp, line);
			if(line.length() > 0 && line.at(0) != '#')
			{
				if(line.length() > 1&&
					(line.at(line.length() - 1) == '\n' || line.at(line.length() - 1) == '\r'))
					line.erase(line.length() - 1);
				if(line.at(0) == '[' && line.at(line.length() - 1) == ']')
				{
					String sectionName = line.substr(1, line.length() - 2);
					SectionMap::iterator it = mSectionMap.find(sectionName);
					if(it != mSectionMap.end())
					{
						TITAN_EXCEPT(Exception::EXCEP_INTERNAL_ERROR, 
							"The Section with same name has existed: " + sectionName,
							"ConfigFile::load");
						return;
					}
					currentMap = TITAN_NEW_T(PropertyMap, MEMCATEGORY_GENERAL)();
					
					mSectionMap.insert(SectionMap::value_type(sectionName, currentMap));
					continue;
				}
				
				if(line.find('=') != String::npos)
				{
					first = line.substr(0,line.find('='));
					second = line.substr(line.find('=') + 1, line.length() - line.find('=') - 1);
					if(currentMap != 0)
					{
						currentMap->insert(PropertyMap::value_type(first, second));
					}
					else
					{
						TITAN_EXCEPT(Exception::EXCEP_INTERNAL_ERROR, 
							"Property can not be created before Section ",
							"ConfigFile::load");
					}
				}
			}
		}
		fp.close();
	}
	//-------------------------------------------------------------------------------//
	ConfigFile::SectionMapIterator	ConfigFile::getSectionMapIterator()
	{
		return SectionMapIterator(mSectionMap.begin(), mSectionMap.end());
	}
	//-------------------------------------------------------------------------------//
	ConfigFile::PropertyMapIterator ConfigFile::getPropertyMapIterator(const String& sectionName)
	{
		SectionMap::iterator it = mSectionMap.find(sectionName);
		return PropertyMapIterator(it->second->begin(), it->second->end());
	}
}