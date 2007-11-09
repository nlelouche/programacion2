#ifndef _Scene_H_
#define _Scene_H_

#include "Defines.h"
#include "EntityManager.h"

#define ZAK_ENTITY_QUANTITY				1600
#define ZAK_COLLISION_GROUPA_QUANTITY	300
#define ZAK_COLLISION_GROUPB_QUANTITY	300
#define ZAK_COLLISION_GROUPC_QUANTITY	300
#define ZAK_COLLISION_GROUPD_QUANTITY	300
#define ZAK_COLLISION_GROUPE_QUANTITY	300

#define ZAK_COLLISION_NONE				0
#define ZAK_COLLISION_GROUPA			1
#define ZAK_COLLISION_GROUPB			2
#define ZAK_COLLISION_GROUPC			3
#define ZAK_COLLISION_GROUPD			4
#define ZAK_COLLISION_GROUPE			5

namespace zak {

class ZAKENGINE_API Scene {
	private:
		EntityManager	_EManager;
		EntityList		_ColGroupA;
		EntityList		_ColGroupB;
		EntityList		_ColGroupC;
		EntityList		_ColGroupD;
		EntityList		_ColGroupE;

		Entity2D			*pEntityA;
		Entity2D			*pEntityB;
		Entity2D			*pEntityC;
		Entity2D			*pEntityD;
		Entity2D			*pEntityE;
		
	public:
		//bool Attach(Entity2D *pEntity, int iColGroup = 0);
		bool Attach(Entity2D *pEntity);
		bool DetachAll();
		void CheckCollision();
		bool Draw(float fTimeBetweenFrames);
		
	Scene();
};

}

#endif // _Scene_H_