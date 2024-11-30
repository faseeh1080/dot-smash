#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Window", sf::Style::Close);

	// Game Objects
	sf::CircleShape dot(50);
	dot.setFillColor(sf::Color::Green);
    dot.setPosition(375, 275);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        window.draw(dot);
		
        window.display();
    }

    return 0;
}
