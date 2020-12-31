#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape button;
    sf::Text text;
public:
    Button();
    Button(std::string text, int charSize, sf::Vector2f size, sf::Color bgColor, sf::Color textColor);
    void setBgColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setTextFont(sf::Font &font);
    void setSize(sf::Vector2f size);
    void setPos(sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
    bool isMouseOver(sf::RenderWindow &window);

};


