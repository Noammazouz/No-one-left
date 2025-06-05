#pragma once

//-----includes section-----
#include "AttackBehavior.h"

//-----class section-----
class OneDirectionAttackBehavior : public AttackBehavior
{
public:
	OneDirectionAttackBehavior() = default;
	virtual ~OneDirectionAttackBehavior() = default;

	// Override the attack method
	virtual void Attack() override;
};