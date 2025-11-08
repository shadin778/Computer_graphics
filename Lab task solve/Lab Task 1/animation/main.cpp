#include <iostream>
using namespace std;

int main() {
    // Create a window
    RenderWindow window(VideoMode(800, 600), "Circle Animation");

    // Create a circle
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(100, 275); // Start position

    float speed = 150.0f; // Movement speed in pixels per second
    sf::Clock clock; // Timer

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate time elapsed
        float deltaTime = clock.restart().asSeconds();

        // Move circle horizontally
        if (circle.getPosition().x + circle.getRadius() * 2 < 800) {
            circle.move(speed * deltaTime, 0);
        }

        // Clear, draw, and display
        window.clear(sf::Color::White);
        window.draw(circle);
        window.display();
    }

    return 0;
}
