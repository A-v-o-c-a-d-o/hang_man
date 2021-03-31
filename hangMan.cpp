#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h>
#include <iostream>

using namespace sf;
using namespace std;

string list[] = {
    "angle", "ant", "apple", "arch", "arm", "army",
    "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
    "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
    "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
    "cake", "camera", "card", "cart", "carriage", "cat", "chain", "cheese", "chest",
    "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
    "cow", "cup", "curtain", "cushion",
    "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
    "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
    "foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
    "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
    "hospital", "house", "island", "jewel", "kettle", "key", "knee", "knife", "knot",
    "leaf", "leg", "library", "line", "lip", "lock",
    "map", "match", "monkey", "moon", "mouth", "muscle",
    "nail", "neck", "needle", "nerve", "net", "nose", "nut",
    "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
    "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
    "rail", "rat", "receipt", "ring", "rod", "roof", "root",
    "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
    "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
    "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
    "store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
    "toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
    "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm",
};

void setText(Text &text, Font &font, string str, Vector2f position, int size, Color color, Vector2f scale)
{
    text.setFont(font);
    text.setString(str);
    text.setPosition(position);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setScale(scale);
}

struct Game
{
    char chGuess;
    bool end;
    Font font;
    string strPrint, strAns, strGuess;
    int turn;
    Text text, print, ans, guess, heart, loss, win, tryAgain, bet;

    void launch()
    {
        end = false;
        font.loadFromFile("D:\\Workspace\\Code\\SFML\\Need file\\font-times-new-roman.ttf");
        srand(time(NULL));
        strAns = list[rand() % 200 + 1];
        strPrint = string(strAns.length(), '-');
        if (strAns.length() < 5)
        {
            turn = 7;
        }
        else
        {
            if (strAns.length() < 7)
            {
                turn = 8;
            }
            else
            {
                turn = 9;
            }
        }
        setText(text, font, "Word : \nYour heart : \nEnter your char : ", Vector2f(20, 20), 25, Color::White, Vector2f(1, 1));
        setText(ans, font, strAns, Vector2f(150, 200), 40, Color::White, Vector2f(1, 1));
        setText(print, font, strPrint, Vector2f(200, 20), 25, Color::White, Vector2f(1.5, 1));
        setText(guess, font, "", Vector2f(220, 77), 25, Color::White, Vector2f(1.5, 1));
        setText(heart, font, string(1, char(turn + 48)), Vector2f(170, 48), 25, Color::White, Vector2f(1, 1));
        setText(loss, font, "You loss !!\n Our answer : " + strAns, Vector2f(100, 200), 30, Color::White, Vector2f(1.2, 1));
        setText(win, font, "You win !!\n Our answer : " + strAns, Vector2f(100, 200), 30, Color::White, Vector2f(1.2, 1));
        setText(tryAgain, font, "Try again now !!", Vector2f(250, 650), 25, Color::White, Vector2f(1, 1));
        setText(bet, font, "I know the answer !!", Vector2f(250, 450), 25, Color::White, Vector2f(1, 1));
    }

    void chUpdate(/*char chGuess*/)
    {
        int d = 0;
        for (int i = 0; i < strAns.length(); i++)
        {
            if (strAns[i] == chGuess)
            {
                strPrint[i] = chGuess;
                d++;
            }
        }

        if (d == 0)
            turn--;

        guess.setString(chGuess);
        heart.setString(string(1, char(turn + 48)));
        print.setString(strPrint);
    }

    void drawAll(RenderWindow& window)
    {
        window.clear();
        if (turn != 0 && strAns != strPrint)
        {
            setText(guess, font, string(1, chGuess), Vector2f(220, 77), 25, Color::White, Vector2f(1.5, 1));
            window.draw(text);
            window.draw(print);
            window.draw(guess);
            window.draw(heart);
            //window.draw(bet);
        }
        else
        {
            if (turn == 0)
                window.draw(loss);
            if (strPrint == strAns)
                window.draw(win);
            window.draw(tryAgain);
            end = true;
        }
    }
};

int main()
{
    RenderWindow window(VideoMode(500, 700), "Hang man !!");
    Game game;

    game.launch();
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            if(event.text.unicode != 13 && event.type == Event::TextEntered && game.end == false)
            {
                game.chGuess = (char)event.text.unicode;
            }
            if(event.text.unicode == 13 && event.type == Event::TextEntered && game.end == false){
                game.chUpdate();
            }
        }

        if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition().x > 250 && Mouse::getPosition().y > 650 && game.end == true){
                game.launch();
        }

        game.drawAll(window);
        window.display();
    }

    return 0;
}

//cd "d:\Workspace\Code\SFML\Code file\" ; if ($?) { g++ hangMan.cpp -o hangMan -lsfml-graphics -lsfml-system -lsfml-window} ; if ($?) {.\hangMan }