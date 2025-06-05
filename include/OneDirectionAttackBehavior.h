#pragma once

#include "AttackBehavior.h"

class OneDirectionAttackBehavior : public AttackBehavior
{
public:
	OneDirectionAttackBehavior() = default;
	virtual ~OneDirectionAttackBehavior() = default;

	// Override the attack method
	virtual void Attack() override;
};