#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <Windows.h>
#include <vector>
#include <fstream>
#include "Button.h"
#include "Game.h"

using namespace std;

int main()
{
    int size = 64;
    int state = 0;
    //string fileName; // used when saving new models
    sf::Font arial;
    arial.loadFromFile("..\\arial.ttf");
    vector <thread> games;
    vector <Button*> buttons;

    //Text labels
    sf::Text sizeLabel;
    sizeLabel.setFont(arial);
    sizeLabel.setString("Size");
    sizeLabel.setCharacterSize(25);
    sizeLabel.setFillColor(sf::Color::Black);
    sizeLabel.setPosition({950, 180});
    sf::Text modelsLabel;
    modelsLabel.setFont(arial);
    modelsLabel.setString("Pre-generated models");
    modelsLabel.setCharacterSize(25);
    modelsLabel.setFillColor(sf::Color::Black);
    modelsLabel.setPosition({870, 250});

    // Initialize app window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Game of Life", sf::Style::Titlebar | sf::Style::Close);
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
    Button *size16Button = new Button("16x16", 20, {80, 30}, sf::Color::Cyan, sf::Color::Black);
    size16Button->setTextFont(arial);
    size16Button->setPos({850, 210});
    buttons.push_back(size16Button);
    Button *size32Button = new Button("32x32", 20, {80, 30}, sf::Color::White, sf::Color::Black);
    size32Button->setTextFont(arial);
    size32Button->setPos({950, 210});
    buttons.push_back(size32Button);
    Button *size64Button = new Button("64x64", 20, {80, 30}, sf::Color::White, sf::Color::Black);
    size64Button->setTextFont(arial);
    size64Button->setPos({1050, 210});
    buttons.push_back(size64Button);
    // Button useed to save new models, only to be used by programmer
/*    Button *saveModel = new Button("save", 20, {80, 30}, sf::Color::White, sf::Color::Black);
    saveModel->setTextFont(arial);
    saveModel->setPos({950, 380});*/
    // Model buttons
    Button *testModel = new Button("test", 20, {80, 30}, sf::Color::White, sf::Color::Black);
    testModel->setTextFont(arial);
    testModel->setPos({5, 10});
    Button *gliderModel = new Button("Glider", 20, {80,30}, sf::Color::White, sf::Color::Black);
    gliderModel->setTextFont(arial);
    gliderModel->setPos({950, 290});
    Button *gunModel = new Button("Glider Gun", 20, {120, 30}, sf::Color::White, sf::Color::Black);
    gunModel->setTextFont(arial);
    gunModel->setPos({1050, 290});
    Button *pulsarModel = new Button("Pulsar", 20, {80,30}, sf::Color::White, sf::Color::Black);
    pulsarModel->setTextFont(arial);
    pulsarModel->setPos({850, 290});
    Button *pentaModel = new Button("Pentadecathlon", 20, {145,30}, sf::Color::White, sf::Color::Black);
    pentaModel->setTextFont(arial);
    pentaModel->setPos({1025, 330});
    Button *methuselahModel = new Button("Methuselah386", 20, {145,30}, sf::Color::White, sf::Color::Black);
    methuselahModel->setTextFont(arial);
    methuselahModel->setPos({850, 330});

    // Initialize arrays
    // Create neighbours array
    int **livingNeighbours;
    livingNeighbours = new int*[size];
    for (int i = 0; i < size; i++)
    {
        livingNeighbours[i] = new int[size];
    }
    // Create cell map
    Cell **cellMap;
    cellMap = new Cell*[size];
    for (int i = 0; i < size; i++)
    {
        cellMap[i] = new Cell[size];
    }
    // Initialize game map with cells
    InitializeMap(size, cellMap, 16);
    size = 16;


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
                    else if (size16Button->isMouseOver(window) && state == 0)
                        size16Button->setBgColor(sf::Color::Cyan);
                    else if (size32Button->isMouseOver(window) && state == 0)
                        size32Button->setBgColor(sf::Color::Cyan);
                    else if (size64Button->isMouseOver(window) && state == 0)
                        size64Button->setBgColor(sf::Color::Cyan);
                    else if (gliderModel->isMouseOver(window) && state == 0)
                        gliderModel->setBgColor(sf::Color::Cyan);
                    else if (gunModel->isMouseOver(window) && state == 0)
                        gunModel->setBgColor(sf::Color::Cyan);
                    else if (pulsarModel->isMouseOver(window) && state == 0)
                        pulsarModel->setBgColor(sf::Color::Cyan);
                    else if (pentaModel->isMouseOver(window) && state == 0)
                        pentaModel->setBgColor(sf::Color::Cyan);
                    else if (methuselahModel->isMouseOver(window) && state == 0)
                        methuselahModel->setBgColor(sf::Color::Cyan);
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        for (int y = 0; y < size; y++) {
                            for (int x = 0; x < size; x++) {
                                if (cellMap[y][x].isMouseOver(window) && state != 1 && !cellMap[y][x].modified)
                                {
                                    cellMap[y][x].modified = true;
                                    if (cellMap[y][x].isAlive()) {
                                        cellMap[y][x].Kill();
                                        // Change neighbours of adjacent cells
                                        if ((y - 1) >= 0) {
                                            if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() -= 1;
                                            cellMap[y - 1][x].Neighbours() -= 1;
                                            if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() -= 1;
                                        }
                                        if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() -= 1;
                                        if ((x + 1) < size) cellMap[y][x + 1].Neighbours() -= 1;
                                        if ((y + 1) < size) {
                                            if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() -= 1;
                                            cellMap[y + 1][x].Neighbours() -= 1;
                                            if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() -= 1;
                                        }
                                        for (int y = 0; y < size; y++) {
                                            for (int x = 0; x < size; x++) {
                                                livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                            }
                                        }
                                    } else {
                                        cellMap[y][x].Born();
                                        // Change neighbours of adjacent cells
                                        if ((y - 1) >= 0) {
                                            if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                            cellMap[y - 1][x].Neighbours() += 1;
                                            if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                        }
                                        if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                        if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                        if ((y + 1) < size) {
                                            if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                            cellMap[y + 1][x].Neighbours() += 1;
                                            if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                        }
                                        for (int y = 0; y < size; y++) {
                                            for (int x = 0; x < size; x++) {
                                                livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                            }
                                        }
                                    }
                                }
                                else if (!cellMap[y][x].isMouseOver(window)) cellMap[y][x].modified = false;
                            }
                        }
                    }
                    else
                    {
                        methuselahModel->setBgColor(sf::Color::White);
                        pentaModel->setBgColor(sf::Color::White);
                        pulsarModel->setBgColor(sf::Color::White);
                        gunModel->setBgColor(sf::Color::White);
                        gliderModel->setBgColor(sf::Color::White);
                        if (state != 1) playButton->setBgColor(sf::Color::White);
                        stopButton->setBgColor(sf::Color::White);
                        if (state != 2) pauseButton->setBgColor(sf::Color::White);
                        if (size != 16) size16Button->setBgColor(sf::Color::White);
                        if (size != 32) size32Button->setBgColor(sf::Color::White);
                        if (size != 64) size64Button->setBgColor(sf::Color::White);
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
                                pauseButton->setBgColor(sf::Color::White);
                            }
                            else if (state == 0)
                            {
                                state = 1;
                                window.setActive(false);
                                thread game(Game, size, &state, livingNeighbours, cellMap, std::ref(window), std::ref(buttons));
                                games.push_back(move(game));
                            }
                        }
                        else if (stopButton->isMouseOver(window))
                        {
                            state = 0;
                            pauseButton->setBgColor(sf::Color::White);
                            playButton->setBgColor(sf::Color::White);
                            Sleep(220);
                            window.setActive(true);
                        }
                        else if (pauseButton->isMouseOver(window))
                        {
                            state = 2;
                            playButton->setBgColor(sf::Color::White);
                        }
                        else if (size16Button->isMouseOver(window) && state == 0)
                        {
                            size = 16;
                            InitializeMap(size, cellMap, size);
                            size32Button->setBgColor(sf::Color::White);
                            size64Button->setBgColor(sf::Color::White);
                        }
                        else if (size32Button->isMouseOver(window) && state == 0)
                        {
                            size = 32;
                            InitializeMap(size, cellMap, size);
                            size16Button->setBgColor(sf::Color::White);
                            size64Button->setBgColor(sf::Color::White);
                        }
                        else if (size64Button->isMouseOver(window) && state == 0)
                        {
                            size = 64;
                            InitializeMap(size, cellMap, size);
                            size16Button->setBgColor(sf::Color::White);
                            size32Button->setBgColor(sf::Color::White);
                        }
/*                        else if (saveModel->isMouseOver(window) && state == 0)
                        {
                            cout << "Enter file name" << endl;
                            cin >> fileName;
                            fileName += ".txt";
                            ofstream modelFile ("..\\Assets\\" + fileName);
                            for (int y = 0; y < size; y++)
                            {
                                for (int x = 0; x < size; x++)
                                {
                                    if(cellMap[y][x].isAlive())
                                    {
                                        modelFile << x << " " << y << " ";
                                    }
                                }
                            }
                            modelFile.close();
                        }*/
                        else if (testModel->isMouseOver(window) && state == 0 && size == 16)
                        {
                            InitializeMap(64, cellMap, size);
                            ifstream modelFile;
                            modelFile.open("..\\Assets\\test.txt");
                            int y, x;
                            while(!modelFile.eof())
                            {
                                modelFile >> x;
                                modelFile >> y;
                                if (cellMap[y][x].isAlive()) continue;
                                cellMap[y][x].Born();
                                // Change neighbours of adjacent cells
                                if ((y - 1) >= 0) {
                                    if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                    cellMap[y - 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                }
                                if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                if ((y + 1) < size) {
                                    if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                    cellMap[y + 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                }
                                for (int y = 0; y < size; y++)
                                {
                                    for (int x = 0; x < size; x++)
                                    {
                                        livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                    }
                                }
                            }
                            modelFile.close();
                        }
                        else if (gunModel->isMouseOver(window) && state == 0)
                        {
                            size = 64;
                            size64Button->setBgColor(sf::Color::Cyan);
                            size16Button->setBgColor(sf::Color::White);
                            size32Button->setBgColor(sf::Color::White);
                            InitializeMap(64, cellMap, size);
                            ifstream modelFile;
                            modelFile.open("..\\Assets\\GosperGliderGun.txt");
                            int y, x;
                            while(!modelFile.eof())
                            {
                                modelFile >> x;
                                modelFile >> y;
                                if (cellMap[y][x].isAlive()) continue;
                                cellMap[y][x].Born();
                                // Change neighbours of adjacent cells
                                if ((y - 1) >= 0) {
                                    if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                    cellMap[y - 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                }
                                if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                if ((y + 1) < size) {
                                    if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                    cellMap[y + 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                }
                                for (int y = 0; y < size; y++)
                                {
                                    for (int x = 0; x < size; x++)
                                    {
                                        livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                    }
                                }
                            }
                            modelFile.close();
                        }
                        else if (pulsarModel->isMouseOver(window) && state == 0)
                        {
                            if (size == 16)
                            {
                                size = 32;
                                size32Button->setBgColor(sf::Color::Cyan);
                                size16Button->setBgColor(sf::Color::White);
                            }
                            InitializeMap(64, cellMap, size);
                            ifstream modelFile;
                            modelFile.open("..\\Assets\\Pulsar.txt");
                            int y, x;
                            while(!modelFile.eof())
                            {
                                modelFile >> x;
                                modelFile >> y;
                                if (cellMap[y][x].isAlive()) continue;
                                cellMap[y][x].Born();
                                // Change neighbours of adjacent cells
                                if ((y - 1) >= 0) {
                                    if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                    cellMap[y - 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                }
                                if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                if ((y + 1) < size) {
                                    if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                    cellMap[y + 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                }
                                for (int y = 0; y < size; y++)
                                {
                                    for (int x = 0; x < size; x++)
                                    {
                                        livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                    }
                                }
                            }
                            modelFile.close();
                        }
                        else if (gliderModel->isMouseOver(window) && state == 0)
                        {
                            InitializeMap(64, cellMap, size);
                            ifstream modelFile;
                            modelFile.open("..\\Assets\\Glider.txt");
                            int y, x;
                            while(!modelFile.eof())
                            {
                                modelFile >> x;
                                modelFile >> y;
                                if (cellMap[y][x].isAlive()) continue;
                                cellMap[y][x].Born();
                                // Change neighbours of adjacent cells
                                if ((y - 1) >= 0) {
                                    if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                    cellMap[y - 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                }
                                if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                if ((y + 1) < size) {
                                    if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                    cellMap[y + 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                }
                                for (int y = 0; y < size; y++)
                                {
                                    for (int x = 0; x < size; x++)
                                    {
                                        livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                    }
                                }
                            }
                            modelFile.close();
                        }
                        else if(methuselahModel->isMouseOver(window))
                        {
                            size = 64;
                            size64Button->setBgColor(sf::Color::Cyan);
                            size16Button->setBgColor(sf::Color::White);
                            size32Button->setBgColor(sf::Color::White);
                            InitializeMap(64, cellMap, size);
                            ifstream modelFile;
                            modelFile.open("..\\Assets\\Methuselah386.txt");
                            int y, x;
                            while(!modelFile.eof())
                            {
                                modelFile >> x;
                                modelFile >> y;
                                if (cellMap[y][x].isAlive()) continue;
                                cellMap[y][x].Born();
                                // Change neighbours of adjacent cells
                                if ((y - 1) >= 0) {
                                    if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                    cellMap[y - 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                }
                                if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                if ((y + 1) < size) {
                                    if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                    cellMap[y + 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                }
                                for (int y = 0; y < size; y++)
                                {
                                    for (int x = 0; x < size; x++)
                                    {
                                        livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                    }
                                }
                            }
                            modelFile.close();
                        }
                        else if (pentaModel->isMouseOver(window) && state == 0)
                        {
                            if (size == 16)
                            {
                                size = 32;
                                size32Button->setBgColor(sf::Color::Cyan);
                                size16Button->setBgColor(sf::Color::White);
                            }
                            InitializeMap(64, cellMap, size);
                            ifstream modelFile;
                            modelFile.open("..\\Assets\\Pentadecathlon.txt");
                            int y, x;
                            while(!modelFile.eof())
                            {
                                modelFile >> x;
                                modelFile >> y;
                                if (cellMap[y][x].isAlive()) continue;
                                cellMap[y][x].Born();
                                // Change neighbours of adjacent cells
                                if ((y - 1) >= 0) {
                                    if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                    cellMap[y - 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                }
                                if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                if ((y + 1) < size) {
                                    if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                    cellMap[y + 1][x].Neighbours() += 1;
                                    if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                }
                                for (int y = 0; y < size; y++)
                                {
                                    for (int x = 0; x < size; x++)
                                    {
                                        livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                    }
                                }
                            }
                            modelFile.close();
                        }
                        else
                        {
                            for (int y = 0; y < size; y++)
                            {
                                for (int x = 0; x <size; x++)
                                {
                                    if (cellMap[y][x].isMouseOver(window) && state != 1)
                                    {
                                        cellMap[y][x].modified = true;
                                        if (cellMap[y][x].isAlive())
                                        {
                                            cellMap[y][x].Kill();
                                            // Change neighbours of adjacent cells
                                            if ((y - 1) >= 0) {
                                                if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() -= 1;
                                                cellMap[y - 1][x].Neighbours() -= 1;
                                                if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() -= 1;
                                            }
                                            if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() -= 1;
                                            if ((x + 1) < size) cellMap[y][x + 1].Neighbours() -= 1;
                                            if ((y + 1) < size) {
                                                if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() -= 1;
                                                cellMap[y + 1][x].Neighbours() -= 1;
                                                if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() -= 1;
                                            }
                                            for (int y = 0; y < size; y++)
                                            {
                                                for (int x = 0; x < size; x++)
                                                {
                                                    livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                                }
                                            }
                                        }
                                        else
                                        {
                                            cellMap[y][x].Born();
                                            // Change neighbours of adjacent cells
                                            if ((y - 1) >= 0) {
                                                if ((x - 1) >= 0) cellMap[y - 1][x - 1].Neighbours() += 1;
                                                cellMap[y - 1][x].Neighbours() += 1;
                                                if ((x + 1) < size) cellMap[y - 1][x + 1].Neighbours() += 1;
                                            }
                                            if ((x - 1) >= 0) cellMap[y][x - 1].Neighbours() += 1;
                                            if ((x + 1) < size) cellMap[y][x + 1].Neighbours() += 1;
                                            if ((y + 1) < size) {
                                                if ((x - 1) >= 0) cellMap[y + 1][x - 1].Neighbours() += 1;
                                                cellMap[y + 1][x].Neighbours() += 1;
                                                if ((x + 1) < size) cellMap[y + 1][x + 1].Neighbours() += 1;
                                            }
                                            for (int y = 0; y < size; y++)
                                            {
                                                for (int x = 0; x < size; x++)
                                                {
                                                    livingNeighbours[y][x] = cellMap[y][x].Neighbours();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        if (!state) {
            window.clear(sf::Color::White);
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j <size; j++)
                {
                    cellMap[i][j].draw(window);
                }
            }
            playButton->draw(window);
            stopButton->draw(window);
            pauseButton->draw(window);
            window.draw(sizeLabel);
            size16Button->draw(window);
            size32Button->draw(window);
            size64Button->draw(window);
            window.draw(modelsLabel);
            //saveModel->draw(window); // can be used if necessary
            //testModel->draw(window); // still exists, just hidden
            gliderModel->draw(window);
            gunModel->draw(window);
            pulsarModel->draw(window);
            pentaModel->draw(window);
            methuselahModel->draw(window);
            window.display();
        }
    }

    // Delete arrays
    // Delete neighbours array
    for (int i = 0; i < size; i++)
    {
        delete[] livingNeighbours[i];
    }
    delete[] livingNeighbours;
    // Delete cell map
    for (int i = 0; i < size; i++)
    {
        delete[] cellMap[i];
    }
    delete[] cellMap;

    return 0;
}
