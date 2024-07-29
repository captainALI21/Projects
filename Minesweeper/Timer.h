#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>
using namespace std;
using namespace sf;

class Timer {
private:
    Text timerText;
    Clock clock;
public:
    Timer(Font& font);
    void drawtime(bool gameRunning, RenderWindow& window);
};
