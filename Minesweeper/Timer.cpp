#include "Timer.h"

Timer::Timer(Font& font) {
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(Color::Black);
    timerText.setPosition(500, 100);
}

void Timer::drawtime(bool gameRunning, RenderWindow& window) {
    if (gameRunning) {
        Time elapsed = clock.getElapsedTime();
        int seconds = static_cast<int>(elapsed.asSeconds());
        int minutes = seconds / 60;
        seconds = seconds % 60;
        ostringstream oss;
        oss << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
        timerText.setString(oss.str());
    }
    window.draw(timerText);
}