//
// Destructor de entidades
//
#pragma once
#ifndef _AUTODESTROYSYSTEM_H_
#define _AUTODESTROYSYSTEM_H_

#include <cocos2d.h>
#include <entityx/entityx.h>
#include "AutoDestroyDescription.h"
#include "LinkedEntityComponent.h"
#include "EntityWillDestroyEvent.h"

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
		es.each<plague::AutoDestroyDescription>([&](entityx::Entity entity, plague::AutoDestroyDescription& autodestroy) {
			autodestroy.life -= dt;
			if (autodestroy.life <= 0)
			{
				// animate and destroy
				auto entity_id = entity.id();
				auto entity = es.get(entity_id);

				if(entity.has_component<LinkedEntityCompomnent>())
				{
					auto linked = entity.component<LinkedEntityCompomnent>().get();
					auto child_entity = es.get(linked->child_id);
					// 
					child_entity.assign<AutoDestroyDescription>(autodestroy.linked_life);
					events.emit<plague::EntityWillDestroy>(linked->child_id, autodestroy.linked_life);
				}

				entity.destroy();
			}
		});
	}
};

}

#endif
