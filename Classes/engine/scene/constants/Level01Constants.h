#ifndef _LEVEL01_CONSTANTS_
#define _LEVEL01_CONSTANTS_

#include <cocos2d.h>

namespace plague {

	namespace level01 {

		// spawn player (anchor centrado abajo)
		const cocos2d::Vec2 player(576, 1632);
		// spawn alcantarilla (anchor centrado)
		const cocos2d::Vec2 enemies(72, 276);

		// limite player izquierda
		const cocos2d::Vec2 left_limit(246, 1632);
		// limite player derecha
		const cocos2d::Vec2 right_limit(846, 1632);

		// special verticals
		int column1 = 282;
		int column2 = 414;
		int column3 = 552;
		int column4 = 684;
		int column5 = 810;

		// special horizontals
		int floor = 357;
		int ceil = 1617;
	}

}

#endif

