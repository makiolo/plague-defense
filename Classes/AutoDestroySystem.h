#pragma once
#ifndef _AUTODESTROYSYSTEM_H_
#define _AUTODESTROYSYSTEM_H_

#include <cocos2d.h>
#include <entityx/entityx.h>
#include "AutoDestroy.h"

namespace plague {

struct AutoDestroySystem : public entityx::System<AutoDestroySystem> {

	explicit AutoDestroySystem()
	{
		;
	}

	virtual ~AutoDestroySystem()
	{

	}

	void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override {
		es.each<plague::AutoDestroyDescription, plague::Sprite>([&](entityx::Entity entity, plague::AutoDestroyDescription& autodestroy, plague::Sprite& sprite) {
			autodestroy.life -= dt;
			if (autodestroy.life <= 0)
			{
				// remove component
				entity.component<plague::AutoDestroyDescription>().remove();

				// animate and destroy
				auto entity_id = entity.id();
				sprite.sprite->runAction(
					cocos2d::Sequence::create(
						cocos2d::FadeOut::create(0.1f),
						cocos2d::CallFunc::create([&es, entity_id]() {
							auto entity = es.get(entity_id);
							entity.destroy();
						}),
						nullptr
					)
				);
			}
		});
	}
};

}

#endif
