//-----include section-----
#include "GameObject.h"

//-----functions section------
//-----------------------------------------------------------------------------
GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position, 
                       float width, float height)
{
    m_pic.setTexture(texture);
    m_pic.setPosition(position);
}

//-----------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(m_pic);
}
