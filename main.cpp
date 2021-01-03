#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <Windows.h>
#include <vector>
#include "Button.h"
#include "Game.h"

using namespace std;

int main()
{
    int size = 80;
    int state = 0;
    sf::Font arial;
    arial.loadFromFile("..\\arial.ttf");
    vector <thread> games;
    vector <Button*> buttons;

    sf::Text sizeLabel;
    sizeLabel.setFont(arial);
    sizeLabel.setString("Size");
    sizeLabel.setCharacterSize(25);
    sizeLabel.setFillColor(sf::Color::Black);
    sizeLabel.setPosition({950, 180});

    // Initialize app window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "GameWindow of Life", sf::Style::Titlebar | sf::Style::Close);
    sf::Context context;
    // Initialize buttons
    Button *playButton = new Button("play", 20, {80, 30}, sf::Color::White, sf::Color::Green);
    playButton->setTextFont(arial);
    playButton->setPos({850, 120});
    buttons.push_back(playButton);
    Button *stopButton = new Button("stop", 20, {80, 30}, sf::Color::White, sf::Color::Red);
    stopButton->setTextFont(arial);
    stopButton->setPos({1050, 120});
    buttons.push_back(stopButton);
    Button *pauseButton = new Button("pause", 20, {80, 30}, sf::Color::White, sf::Color::Yellow);
    pauseButton->setTextFont(arial);
    pauseButton->setPos({950, 120});
    buttons.push_back(pauseButton);
    Button *size64Button = new Button("64x64", 20, {80, 30}, sf::Color::Cyan, sf::Color::Black);
    size64Button->setTextFont(arial);
    size64Button->setPos({850, 210});
    buttons.push_back(size64Button);
    Button *size128Button = new Button("128x128", 20, {80, 30}, sf::Color::White, sf::Color::Black);
    size128Button->setTextFont(arial);
    size128Button->setPos({950, 210});
    buttons.push_back(size128Button);
    Button *size256Button = new Button("256x256", 20, {80, 30}, sf::Color::White, sf::Color::Black);
    size256Button->setTextFont(arial);
    size256Button->setPos({1050, 210});
    buttons.push_back(size256Button);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    state = 0;
                    for (auto &game: games)
                    {
                        game.join();
                    }
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    if (playButton->isMouseOver(window))
                        playButton->setBgColor(sf::Color::Cyan);
                    else if (stopButton->isMouseOver(window))
                        stopButton->setBgColor(sf::Color::Yellow);
                    else if (pauseButton->isMouseOver(window))
                        pauseButton->setBgColor(sf::Color::Blue);
                    else if (size64Button->isMouseOver(window))
                        size64Button->setBgColor(sf::Color::Cyan);
                    else if (size128Button->isMouseOver(window))
                        size128Button->setBgColor(sf::Color::Cyan);
                    else if (size256Button->isMouseOver(window))
                        size256Button->setBgColor(sf::Color::Cyan);
                    else
                    {
                        playButton->setBgColor(sf::Color::White);
                        stopButton->setBgColor(sf::Color::White);
                        pauseButton->setBgColor(sf::Color::White);
                        if (size != 80) size64Button->setBgColor(sf::Color::White);
                        if (size != 144) size128Button->setBgColor(sf::Color::White);
                        if (size != 272) size256Button->setBgColor(sf::Color::White);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (playButton->isMouseOver(window))
                        {
                            if (state == 1)
                            {
                                break;
                            }
                            else if (state == 2)
                            {
                                state = 1;
                            }
                            else if (state == 0)
                            {
                                state = 1;
                                window.setActive(false);
                                thread game(Game, size, &state, 1, std::ref(window), std::ref(buttons));
                                games.push_back(move(game));
                            }
                        }
                        else if (stopButton->isMouseOver(window))
                        {
                            state = 0;
                            // This doesn't work after the first one, no idea why
//                            for (auto &game: games)
//                            {
//                                game.join();
//                            }
                            Sleep(60);
                            window.setActive(true);
                        }
                        else if (pauseButton->isMouseOver(window))
                        {
                            state = 2;
                        }
                        else if (size64Button->isMouseOver(window))
                        {
                            size = 80;
                        }
                        else if (size128Button->isMouseOver(window))
                        {
                            size = 144;
                        }
                        else if (size256Button->isMouseOver(window))
                        {
                            size = 272;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        if (!state) {
            window.clear(sf::Color::White);
            playButton->draw(window);
            stopButton->draw(window);
            pauseButton->draw(window);
            window.draw(sizeLabel);
            size64Button->draw(window);
            size128Button->draw(window);
            size256Button->draw(window);
            window.display();
        }
    }


    return 0;
}
