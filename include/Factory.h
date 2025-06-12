#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Const.h"

template <typename T>
class Factory {
public:
	static Factory& instance()
	{
		static auto instance = Factory();
		return instance;
	}
	using FuncType = std::unique_ptr<T>(*)(const sf::Texture&, const sf::Vector2f&, float, float);

	bool registerType(ObjectType t, FuncType f)
	{
		m_map.emplace(t, f);
		return true;
	}
	std::unique_ptr<T> create(ObjectType t, const sf::Texture& texture, const sf::Vector2f& position, float width, float height) const
	{
		if (!m_map.contains(t)) return nullptr;
		return m_map.at(t)(position);
	}
private:
	Factory() = default;
	Factory(const Factory&) = delete;
	void operator=(const Factory&) = delete;

	std::unordered_map<ObjectType, FuncType> m_map;
};