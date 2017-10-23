#include "ECS.h"

void Entity::AddGroup(Group mGroup) noexcept
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}