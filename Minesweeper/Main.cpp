#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Grid.h"
#include "Timer.h"
using namespace sf;
using namespace std;

RectangleShape outerRectangle() {
    RectangleShape outerRect(Vector2f(314, 464));
    outerRect.setFillColor(Color::Transparent);
    outerRect.setOutlineColor(Color::Blue);
    outerRect.setOutlineThickness(8);
    outerRect.setPosition(30, 30);
    return outerRect;
}

void drawButtons(RenderWindow& window, Font& font) {
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    // New Game button
    RectangleShape newGameButton(Vector2f(200, 50));
    newGameButton.setFillColor(Color(52, 152, 219));
    newGameButton.setPosition(windowWidth / 2 + 60, windowHeight / 2 - 75);
    window.draw(newGameButton);

    Text newGameText;
    newGameText.setFont(font);
    newGameText.setString("New Game");
    newGameText.setCharacterSize(24);
    newGameText.setFillColor(Color::White);
    newGameText.setPosition(
        newGameButton.getPosition().x + (newGameButton.getSize().x - newGameText.getLocalBounds().width) / 2,
        newGameButton.getPosition().y + (newGameButton.getSize().y - newGameText.getLocalBounds().height) / 2 - 5
    );
    window.draw(newGameText);

    // Exit button
    RectangleShape exitButton(Vector2f(200, 50));
    exitButton.setFillColor(Color(230, 126, 34));
    exitButton.setPosition(windowWidth / 2 + 60, windowHeight / 2 + 15);
    window.draw(exitButton);

    Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(Color::White);
    exitText.setPosition(
        exitButton.getPosition().x + (exitButton.getSize().x - exitText.getLocalBounds().width) / 2,
        exitButton.getPosition().y + (exitButton.getSize().y - exitText.getLocalBounds().height) / 2 - 5
    );
    window.draw(exitText);
}

void drawState(RenderWindow& window, Font& font,int currentState) {
    if (currentState == -1) {
        RectangleShape innerRect(Vector2f(314, 464));
        innerRect.setFillColor(Color(240, 240, 240));
        innerRect.setPosition(30, 30);
        window.draw(innerRect);
        Text gameLoseText;
        gameLoseText.setFont(font);
        gameLoseText.setString("You Lost");
        gameLoseText.setCharacterSize(24);
        gameLoseText.setFillColor(Color::Blue);
        FloatRect textBounds = gameLoseText.getLocalBounds();
        float xPos = innerRect.getPosition().x + (innerRect.getSize().x / 2) - (textBounds.width / 2) - textBounds.left;
        float yPos = innerRect.getPosition().y + (innerRect.getSize().y / 2) - (textBounds.height / 2) - textBounds.top;
        gameLoseText.setPosition(xPos, yPos);
        window.draw(gameLoseText);
    } else if (currentState == 2) {
        RectangleShape innerRect(Vector2f(314, 464));
        innerRect.setFillColor(Color(240, 240, 240));
        innerRect.setPosition(30, 30);
        window.draw(innerRect);
        Text gameLoseText;
        gameLoseText.setFont(font);
        gameLoseText.setString("You Won");
        gameLoseText.setCharacterSize(24);
        gameLoseText.setFillColor(Color::Blue);
        FloatRect textBounds = gameLoseText.getLocalBounds();
        float xPos = innerRect.getPosition().x + (innerRect.getSize().x / 2) - (textBounds.width / 2) - textBounds.left;
        float yPos = innerRect.getPosition().y + (innerRect.getSize().y / 2) - (textBounds.height / 2) - textBounds.top;
        gameLoseText.setPosition(xPos, yPos);
        window.draw(gameLoseText);
    }
}

void drawCount(RenderWindow& window, Font& font, Grid& grid, int currentState) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            int count = ((grid.getCells())[i][j]).getCount();
            Cell cell = (grid.getCells())[i][j];
            if (count > 0 && !cell.getisHidden() && currentState != 2 && currentState != -1) {
                Text countText;
                countText.setFont(font);
                countText.setString(to_string(count));
                countText.setCharacterSize(16);
                countText.setFillColor(Color(80, 80, 80));
                FloatRect textBounds = countText.getLocalBounds();
                float xPos = cell.getRect().getPosition().x + (cell.getRect().getSize().x / 2) - (textBounds.width / 2) - textBounds.left;
                float yPos = cell.getRect().getPosition().y + (cell.getRect().getSize().y / 2) - (textBounds.height / 2) - textBounds.top;
                countText.setPosition(xPos, yPos);
                window.draw(countText);
            }
        }
    }
}

void startNewGame(Grid& grid, Timer& timer, Font& font, bool& gameRunning, int& currentState) {
    grid = Grid();
    timer = Timer(font);
    gameRunning = true;
    currentState = 1;
}

int main() {
    RenderWindow window(VideoMode(372 * 2, 524), "Minesweeper");
    window.setFramerateLimit(30);
    Font font;
    font.loadFromFile("OpenSans-VariableFont_wdth,wght.ttf");

    Grid grid;
    Timer timer(font);
    bool gameRunning = true;
    int currentState = 1;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (gameRunning) {
                if (event.type == Event::MouseButtonPressed) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    currentState = grid.mousePress(mousePos, event);
                    if (currentState == 2 || currentState == -1) {
                        gameRunning = false;
                    }
                }
            }
            //else { // When the game is not running
                if (event.type == Event::MouseButtonPressed) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    FloatRect newGameButtonBounds(window.getSize().x / 2 + 60, window.getSize().y / 2 - 75, 200, 50);
                    FloatRect exitButtonBounds(window.getSize().x / 2 + 60, window.getSize().y / 2 + 15, 200, 50);

                    if (newGameButtonBounds.contains(mousePos.x, mousePos.y)) {
                        startNewGame(grid, timer, font, gameRunning, currentState);
                    }
                    else if (exitButtonBounds.contains(mousePos.x, mousePos.y)) {
                        window.close();
                    }
                }
            //}
        }
        window.clear(Color(240, 240, 240));
        window.draw(outerRectangle());
        for (auto& line : grid.getCells()) {
            for (auto& box : line) {
                window.draw(box.getRect());
            }
        }
        timer.drawtime(gameRunning, window);
        drawState(window, font, currentState);
        drawButtons(window, font);
        drawCount(window, font, grid, currentState);
        window.display();
    }

    return 0;
}

