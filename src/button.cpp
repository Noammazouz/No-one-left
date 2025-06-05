//-----include section-----
#include "Button.h"

//-----functions section------
//-----------------------------------------------------------------------------
Button::Button(char buttonName) : m_buttonType(buttonName)
{
	setSize();  //Initialize size when button is created
}

//-----------------------------------------------------------------------------
sf::Vector2f Button::getPosition() const
{
	return m_position;
}

//-----------------------------------------------------------------------------
void Button::setPosition(int place)
{
	//m_position.x = 30.f;
	m_position.x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;

	//calculate vertical starting position for centering
	float totalButtonsHeight = START_WINDOW_BUTTONS_NUM * BUTTON_HEIGHT +
		(START_WINDOW_BUTTONS_NUM - 1) * BUTTON_SPACING;
	float startingY = (WINDOW_HEIGHT - totalButtonsHeight) / 2;

	//vertical position for each button
	m_position.y = startingY + (BUTTON_HEIGHT + BUTTON_SPACING) * place;
}

//-----------------------------------------------------------------------------
sf::Vector2f Button::getSize() const
{
	return m_size;
}

//-----------------------------------------------------------------------------
void Button::setSize()
{
	m_size = sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT);
}

//-----------------------------------------------------------------------------
sf::RectangleShape Button::makeButtonRectangle() const
{
	sf::RectangleShape buttonRectangle(m_size);

	buttonRectangle.setPosition(m_position);

	//Change outline color based on hover state
	if (m_isOnIt)
	{
		buttonRectangle.setOutlineColor(sf::Color::Red); //Highlight color when hovered
		buttonRectangle.setOutlineThickness(7);         //Thicker outline when hovered
	}
	else
	{
		buttonRectangle.setOutlineColor(sf::Color::Black);
		buttonRectangle.setOutlineThickness(2.5);
	}

	buttonRectangle.setFillColor(sf::Color(0, 0, 0, 0));
	buttonRectangle.setTexture(NULL);

	return buttonRectangle;
}

//-----------------------------------------------------------------------------
//This function draw each button.
void Button::draw(sf::RenderWindow& window, char buttonType) const
{
	//create a rectangle for the button
	sf::RectangleShape button = makeButtonRectangle();


	//create text for the button
	sf::Text buttonText;
	buttonText.setFont(ResourceManager::getInstance().GetTextFont());   //Set the font
	buttonText.setString(getStartMenuButtonStringByChar(buttonType));  //Set the text
	buttonText.setCharacterSize(FONT_CHARACTERS_SIZE);                //Text size
	buttonText.setFillColor(sf::Color::Black);                       //Text color


	//center the text on the button
	sf::FloatRect textBounds = buttonText.getLocalBounds();
	sf::FloatRect buttonBounds = button.getGlobalBounds();
	buttonText.setPosition(buttonBounds.left + (buttonBounds.width - textBounds.width) / 2,
		buttonBounds.top + (buttonBounds.height - textBounds.height) / 2 - textBounds.top);


	window.draw(button);
	window.draw(buttonText);
}

//-----------------------------------------------------------------------------
const char Button::getButtonType() const
{
	return m_buttonType;
}

//-----------------------------------------------------------------------------
void Button::setIsOnIt(bool isOnIt)
{
	m_isOnIt = isOnIt;
}

//-----------------------------------------------------------------------------
bool Button::getIsOnIt() const
{
	return m_isOnIt;
}