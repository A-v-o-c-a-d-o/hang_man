#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(500, 700), "Hang man !!");
    Music m;
    m.openFromFile("D:\\Workspace\\Code\\SFML\\Need file\\Congratulations-sound.wav");
    m.play();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.display();
    }

    return 0;
}

//cd "d:\Workspace\Code\SFML\Code file\" ; if ($?) { g++ 0.cpp -o 0 -lsfml-graphics -lsfml-system -lsfml-window} ; if ($?) {.\0 }