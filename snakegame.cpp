#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SIZE = 20;

struct SnakeSegment {
    int x, y;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game - SFML");
    window.setFramerateLimit(10); // Snake speed

    // Snake Initialization
    std::vector<SnakeSegment> snake = { {WIDTH / (2 * SIZE), HEIGHT / (2 * SIZE)} };
    int dx = 1, dy = 0; // Direction (right)
    
    // Food Initialization
    std::srand(std::time(nullptr));
    SnakeSegment food = { std::rand() % (WIDTH / SIZE), std::rand() % (HEIGHT / SIZE) };

    // Shapes
    sf::RectangleShape snakeRect(sf::Vector2f(SIZE - 1, SIZE - 1));
    sf::RectangleShape foodRect(sf::Vector2f(SIZE - 1, SIZE - 1));
    foodRect.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dy == 0) { dx = 0; dy = -1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dy == 0) { dx = 0; dy = 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dx == 0) { dx = -1; dy = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dx == 0) { dx = 1; dy = 0; }

        // Move Snake
        SnakeSegment newHead = { snake[0].x + dx, snake[0].y + dy };

        // Check Collision with Walls
        if (newHead.x < 0 || newHead.x >= WIDTH / SIZE || newHead.y < 0 || newHead.y >= HEIGHT / SIZE) {
            window.close(); // Game Over
        }

        // Check Collision with Itself
        for (auto& segment : snake) {
            if (segment.x == newHead.x && segment.y == newHead.y) {
                window.close(); // Game Over
            }
        }

        // Insert New Head
        snake.insert(snake.begin(), newHead);

        // Check Food
        if (newHead.x == food.x && newHead.y == food.y) {
            food = { std::rand() % (WIDTH / SIZE), std::rand() % (HEIGHT / SIZE) };
        } else {
            snake.pop_back(); // Remove tail
        }

        // Draw
        window.clear(sf::Color::Black);

        // Draw Snake
        for (auto& segment : snake) {
            snakeRect.setPosition(segment.x * SIZE, segment.y * SIZE);
            snakeRect.setFillColor(sf::Color::Green);
            window.draw(snakeRect);
        }

        // Draw Food
        foodRect.setPosition(food.x * SIZE, food.y * SIZE);
        window.draw(foodRect);

        window.display();
    }

    return 0;
}
