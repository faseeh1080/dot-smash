#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <chrono>
#include <vector>

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

    Dot(sf::Vector2i resolution) : dot(50) {
        dot.setFillColor(sf::Color::Green);
        changePosition(resolution);
    }
    
    void changePosition(sf::Vector2i resolution) {
        position.x = generateRandomNumber(0, resolution.x - radius * 2);
        position.y = generateRandomNumber(0, resolution.y - radius * 2);
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

class ScoreManager {
public:
    int totalNumberOfDots = 20;
    int dotsRemaining = totalNumberOfDots;
    std::vector<float> responseTimes; // To calculate the average response time.
    std::chrono::high_resolution_clock::time_point start; // To calculate response time.

    float calculateResponseTime() {
        float responseTime;
        if (dotsRemaining == totalNumberOfDots) {
            start = std::chrono::high_resolution_clock::now();
            responseTime = 0.0f;
        }
        else {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = end - start;
            start = end;
            responseTime = elapsed.count(); // In seconds.
        }
        dotsRemaining -= 1;
        return responseTime;
    }
};

int main() {
    // Create the window.
    sf::Vector2i resolution; // Declare the window resolution.
    resolution.x = 1280;
    resolution.y = 720;
    sf::RenderWindow window(
        sf::VideoMode(resolution.x, resolution.y),
        "Dot Smash",
        sf::Style::Close
    );

    Dot theDot(resolution); // The dot that has to be smashed.
    ScoreManager scoreManager;

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

    // Create a text object for remaining dots.
    sf::Text remaining(std::to_string(scoreManager.dotsRemaining), playfulTime, 60);
    remaining.setFillColor(sf::Color::White);
    remaining.setPosition(10, 48);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (theDot.onTop(sf::Mouse::getPosition(window))) {
                    theDot.changePosition(resolution);
                    responseTime.setString(
                        "Response Time: " +
                        std::to_string(scoreManager.calculateResponseTime())
                    );
                    remaining.setString(std::to_string(scoreManager.dotsRemaining));
                }
            }
        }

        window.clear();

        window.draw(theDot.dot);
        window.draw(responseTime);
        window.draw(remaining);

        window.display();
    }

    return 0;
}
