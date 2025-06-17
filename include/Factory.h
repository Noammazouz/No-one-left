#pragma once

//-----include section-----
#include <memory>
#include <string>
#include <unordered_map>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Const.h"

//-----class section-----
template <typename T>
class Factory 
{
public:
	static Factory& instance()
	{
		static auto instance = Factory();
		return instance;
	}
  
	using FuncType = std::unique_ptr<T>(*)(const sf::Vector2f&);

	bool registerType(ObjectType t, FuncType f)
	{
		// Returns true if registration succeeded, false if type was already registered
		return m_map.emplace(t, f).second;
		
	}
  
	std::unique_ptr<T> create(ObjectType t, const sf::Vector2f& position) const
	{
		if (!m_map.contains(t))
		{
			return nullptr;
		}
		return m_map.at(t)(position);
	}
  
private:
	Factory() = default;
	Factory(const Factory&) = delete;
	void operator=(const Factory&) = delete;
	std::unordered_map<ObjectType, FuncType> m_map;
};