#pragma once
#include "SFML/Graphics.hpp"
#include <exception>

#define MAX_NUMBER_OF_ITEMS 2

class Menu
{
public:
    Menu(int width, int height) {
        if (!font.loadFromFile(R"(D:\minesweeper\assets\font.ttf)"))
        {
            throw std::invalid_argument("Wrong font");
        }

        menu[0].setFont(font);
        menu[0].setFillColor(sf::Color::Red);
        menu[0].setString("Play");
        menu[0].setPosition(sf::Vector2f(width / 2 - 30, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
        //menu[0].setScale(2., 2.);
        menu[0].setCharacterSize(70);

        /*menu[1].setFont(font);
        menu[1].setColor(sf::Color::White);
        menu[1].setString("Options");
        menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));*/

        menu[1].setFont(font);
        menu[1].setFillColor(sf::Color::Black);
        menu[1].setString("Exit");
        menu[1].setPosition(sf::Vector2f(width / 2 - 30, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
        //menu[1].setScale(2., 2.);
        menu[1].setCharacterSize(70);

        selectedItemIndex = 0;
    }


    void draw(sf::RenderWindow& window){
        for (const auto & i : menu)
        {
            window.draw(i);
        }
    }
    void MoveUp(){
        if (selectedItemIndex - 1 >= 0)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::Black);
            selectedItemIndex--;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }
    void MoveDown(){
        if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::Black);
            selectedItemIndex++;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }
    int GetPressedItem() { return selectedItemIndex; }


private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

};
