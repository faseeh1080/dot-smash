#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

class Dot {
public:
    sf::CircleShape dot;
    int radius = 50;
    sf::Vector2i position;

    Dot() : dot(50) {
        dot.setFillColor(sf::Color::Green);
        changePosition();
    }
    
    void changePosition() {
        position.x = generateRandomNumber(0, 1280 - radius * 2);
        position.y = generateRandomNumber(0, 720 - radius * 2);
        dot.setPosition(position.x, position.y);
	}
	
	// Returns true if 'point' is on top of the circle.
	bool onTop(sf::Vector2i point) {
        int dx = position.x + radius - point.x;
        int dy = position.y + radius - point.y;
        int distanceSquared = dx * dx + dy * dy;
        return distanceSquared <= radius * radius;
	}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Dot Smash", sf::Style::Close);

    Dot theDot; // The dot that has to be smashed.

    // Load PlayfulTime-BLBB8.ttf.
    sf::Font playfulTime;
    if (!playfulTime.loadFromFile("assets/PlayfulTime-BLBB8.ttf")) {
        std::cout << "Failed to fetch the font file." << std::endl;
        return 1;
    }

    // Create a text object for response time.
    sf::Text responseTime("Click the dot to start.", playfulTime, 30);
    responseTime.setFillColor(sf::Color::White);
    responseTime.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (theDot.onTop(sf::Mouse::getPosition(window))) {
                    theDot.changePosition();
                }
            }
        }

        window.clear();

        window.draw(theDot.dot);
        window.draw(responseTime);

        window.display();
    }

    return 0;
}
