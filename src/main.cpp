#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <random>

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

class Dot {
public:
    sf::CircleShape dot;

    Dot() : dot(50) {
        dot.setFillColor(sf::Color::Green);
        dot.setPosition(
			generateRandomNumber(0, 1280),
			generateRandomNumber(0, 720)
		);
    }
    
    void changePosition() {
		dot.setPosition(
			generateRandomNumber(0, 1280),
			generateRandomNumber(0, 720)
		);
	}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Window", sf::Style::Close);

    Dot theDot;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
				theDot.changePosition();
			}
        }

        window.clear();

        window.draw(theDot.dot);

        window.display();
    }

    return 0;
}
