#include "ccsoundobjectinforeference.h"
#include <audio/include/AudioEngine.h>

namespace Spriter2dX
{

	CCSoundObjectInfoReference::CCSoundObjectInfoReference(const char* path)
	: path(path) {}

	void CCSoundObjectInfoReference::playTrigger()
	{
		if (getTriggerCount())
		{
			// cocos2d::AudioEngine::play2d(path, false, 1.0f, float(getPanning()), float(getVolume()));
			cocos2d::AudioEngine::play2d(path, false, float(getVolume()));
		}
	}


}
