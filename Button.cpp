#include "Button.h"


Button::Button()
{

}

Button::Button(std::string text, int charSize, sf::Vector2f size, sf::Color bgColor, sf::Color textColor)
{
    // Initialize text
    this->text.setString(text);
    this->text.setFillColor(textColor);
    this->text.setCharacterSize(charSize);
    // Initialize button (box)
    button.setSize(size);
    button.setFillColor(bgColor);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(1);
}

void Button::setBgColor(sf::Color color)
{
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
    text.setFillColor(color);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
}

void Button::setTextFont(sf::Font &font)
{
    text.setFont(font);
}

void Button::setSize(sf::Vector2f size)
{
    button.setSize(size);
}

void Button::setPos(sf::Vector2f pos)
{
    button.setPosition(pos);

    float tx = (pos.x + button.getLocalBounds().width / 3) - (text.getLocalBounds().width / 3);
    float ty = (pos.y + button.getLocalBounds().height / 3) - (text.getLocalBounds().height / 3);

    text.setPosition(tx, ty);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
    float mousePosX = sf::Mouse::getPosition(window).x;
    float mousePosY = sf::Mouse::getPosition(window).y;

    float btnLPosX = button.getPosition().x;
    float btnDPosY = button.getPosition().y;

    float btnRPosX = btnLPosX + button.getLocalBounds().width;
    float btnUPosY = btnDPosY + button.getLocalBounds().height;

    if (mousePosX > btnLPosX && mousePosX < btnRPosX && mousePosY > btnDPosY && mousePosY < btnUPosY) return true;
    else return false;
}

