#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Camera.h"
using namespace std;
class Window {
private:
    sf::RenderWindow& window;
    Poligon* poligon;
    long long int Poligon_kol;
    //shape.setFillColor(sf::Color::Green);
public:
    Window(sf::RenderWindow& win) : window(win) {
        Poligon_kol= Poligon_load_test1();
    };
    long long int Poligon_load_test1() {
        poligon = new Poligon[1];
        return 1;
    }
	void Run() {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            window.display();
        }
	}
};