#include "ccsoundfile.h"

#include <global/settings.h>

#include "ccsoundobjectinforeference.h"
#include <audio/include/AudioEngine.h>

namespace se = SpriterEngine;

namespace Spriter2dX
{
	CCSoundFile::CCSoundFile(std::string initialFilePath) :
		se::SoundFile(initialFilePath), path(initialFilePath.c_str())
	{
		cocos2d::AudioEngine::preload(path);
	}


	se::SoundObjectInfoReference* CCSoundFile::newSoundInfoReference()
	{
		return new CCSoundObjectInfoReference(path);
	}

}
