#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

void setText(Text &text, Font &font, string str, Vector2f position, int size, Color color, Vector2f scale)
{
    text.setFont(font);
    text.setString(str);
    text.setPosition(position);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setScale(scale);
}

struct Button
{
    Font font;
    Text text;
    RectangleShape shape;
    void setup(string str, Vector2f pos, int strSize, Color strColor, Vector2f shapeSize, Color shapeColor)
    {
        font.loadFromFile("D:\\Workspace\\Code\\SFML\\File_need\\font-times-new-roman.ttf");
        text.setFont(font);
        text.setString(str);
        text.setPosition(pos);
        text.setCharacterSize(strSize);
        text.setFillColor(strColor);
        shape.setFillColor(shapeColor);
        shape.setPosition(pos);
        shape.setSize(shapeSize);
    }
    void render(RenderWindow& window)
    {
        window.draw(shape);
        window.draw(text);
    }
    bool clicked(RenderWindow& window)
    {
        return  (Mouse::isButtonPressed(Mouse::Left)) &&
                (Mouse::getPosition(window).x > shape.getPosition().x) &&
                (Mouse::getPosition(window).x < shape.getPosition().x + shape.getSize().x) &&
                (Mouse::getPosition(window).y > shape.getPosition().y) &&
                (Mouse::getPosition(window).y < shape.getPosition().y + shape.getSize().y);
    }
};

struct Game
{
    Font font;
    int stage = 0;

    Text welcome;
    Button start;

    Text chooseTopic;
    Button topic[6];
    string path[6] =   {"D:\\Workspace\\Code\\SFML\\File_need\\animal.txt", "D:\\Workspace\\Code\\SFML\\File_need\\fruit.txt",
                        "D:\\Workspace\\Code\\SFML\\File_need\\landscape.txt", "D:\\Workspace\\Code\\SFML\\File_need\\plant.txt",
                        "D:\\Workspace\\Code\\SFML\\File_need\\vegetable.txt", "D:\\Workspace\\Code\\SFML\\File_need\\weather.txt"};
    Vector2f topicPos[6] = {Vector2f(50, 400), Vector2f(200, 400), Vector2f(350, 400),
                            Vector2f(50, 300), Vector2f(200, 300), Vector2f(350, 300)};
    string strTopic[6] = {"   Animal", "     Fruit", "Landscape", "    Plant", " Vegetable", "   Weather"};
    vector<string> list;

    char chGuess;
    bool suggestMode, betMode;
    int turn, intSuggest, timeSuggest;
    Text text, print, guess, heart, wrong, textTimeSuggest, getBet, textBet, getSuggest, textSuggest;
    string strPrint, strAns, strGuess, strWrong, strBet;
    Button suggest, bet;

    Text loss, win;
    Button tryAgain;

    void update(RenderWindow& window, Event event)
    {
        switch(stage)
        {
            case 0:
                font.loadFromFile("D:\\Workspace\\Code\\SFML\\File_need\\font-times-new-roman.ttf");
                start.setup("  Start", Vector2f(200, 400), 35, Color::White, Vector2f(100, 50), Color::Blue);
                setText(welcome, font, "WELCOME TO HANGMAN", Vector2f(70, 300), 30, Color::White, Vector2f(1, 1));
                setText(chooseTopic, font, "CHOOSE YOUR TOPIC", Vector2f(100, 200), 30, Color::White, Vector2f(1, 1));
                setText(getBet, font, "Enter your ans : ", Vector2f(50, 300), 30, Color::White, Vector2f(1, 1));
                setText(getSuggest, font, "Enter the number you want : ", Vector2f(50, 300), 25, Color::White, Vector2f(1, 1));
                tryAgain.setup(" Try again??", Vector2f(250, 500), 30, Color::White, Vector2f(170, 50), Color::Blue);
                for(int i=0; i<6; i++)
                    topic[i].setup(strTopic[i], topicPos[i], 25, Color::White, Vector2f(120, 40), Color::Red);
                if(start.clicked(window))
                    stage++;
                break;
            case 1:
                for(int i=0; i<6; i++)
                    if(topic[i].clicked(window))
                    {
                        ifstream file(path[i]);
                        while(!file.eof())
                        {
                            string a;
                            file >> a;
                            list.push_back(a);
                        }
                        srand(time(NULL));
                        strAns = list[rand() % list.size() + 1];
                        strPrint = string(strAns.length(), '-');
                        if (strAns.length() < 5)
                        {
                            turn = 7;
                            timeSuggest = 1;
                        }
                        else
                        {
                            if (strAns.length() < 7)
                            {
                                turn = 8;
                                timeSuggest = 2;
                            }
                            else
                            {
                                turn = 9;
                                timeSuggest = 3;
                            }
                        }
                        suggestMode = false;
                        betMode = false;
                        strWrong = "";
                        strBet = "";
                        setText(loss, font, "You loss !!\n Our answer : " + strAns, Vector2f(100, 200), 30, Color::White, Vector2f(1.2, 1));
                        setText(win, font, "You win !!\n Our answer : " + strAns, Vector2f(100, 200), 30, Color::White, Vector2f(1.2, 1));
                        setText(text, font, "Word : \nYour heart : \nEnter your char : \nWrong char : \nSugggestion : ", Vector2f(20, 20), 25, Color::Red, Vector2f(1, 1));
                        setText(print, font, strPrint, Vector2f(200, 20), 25, Color::White, Vector2f(1.5, 1));
                        setText(heart, font, string(1, char(turn + 48)), Vector2f(170, 48), 25, Color::White, Vector2f(1, 1));
                        setText(guess, font, strGuess, Vector2f(220, 77), 25, Color::White, Vector2f(1.5, 1));
                        setText(wrong, font, strWrong, Vector2f(170, 110), 25, Color::White, Vector2f(1, 1));
                        setText(textTimeSuggest, font, string(1, char(timeSuggest+48)), Vector2f(170, 135), 25, Color::White, Vector2f(1, 1));
                        setText(textBet, font, strBet, Vector2f(300, 300), 25, Color::White, Vector2f(1, 1));
                        setText(textSuggest, font, "", Vector2f(360, 300), 25, Color::White, Vector2f(1, 1));
                        suggest.setup("Suggest", Vector2f(10, 650), 25, Color::White, Vector2f(100, 50), Color::Blue);
                        bet.setup("I know the answer", Vector2f(250, 650), 25, Color::White, Vector2f(200, 50), Color::Blue);
                        stage++;
                        break;
                    }
                break;
            case 2:
                if(bet.clicked(window))
                    betMode = true;
                if(suggest.clicked(window) && timeSuggest > 0)
                    suggestMode = true;
                if(betMode == false && suggestMode == false)
                {
                    if(event.text.unicode != 13 && event.type == Event::TextEntered)
                    {
                        chGuess = (char)event.text.unicode;
                        guess.setString(chGuess);
                    }
                    if(event.text.unicode == 13 && event.type == Event::TextEntered)
                    {
                        int d = 0;
                        for(int i = 0; i < strAns.length(); i++)
                            if (strAns[i] == chGuess)
                            {
                                strPrint[i] = chGuess;
                                d++;
                            }
                        if (d == 0)
                        {
                            turn--;
                            strWrong += chGuess;
                        }

                        guess.setString(chGuess);
                        heart.setString(string(1, char(turn + 48)));
                        print.setString(strPrint);
                        wrong.setString(strWrong);
                    }
                }
                if(suggestMode == true && betMode == false)
                {
                    if(event.type == Event::TextEntered && event.text.unicode > '0' && event.text.unicode <= '9')
                    {
                        intSuggest = event.text.unicode - 48;
                        textSuggest.setString(string(1, char(intSuggest+48)));
                    }
                    if(event.type == Event::TextEntered && event.text.unicode == 13)
                    {
                        strPrint[intSuggest-1] = strAns[intSuggest-1];
                        print.setString(strPrint);
                        timeSuggest--;
                        textTimeSuggest.setString(string(1, char(timeSuggest+48)));
                        suggestMode = false;
                    }
                }
                if(betMode == true && suggestMode == false)
                {
                    if(event.type == Event::TextEntered && event.text.unicode != 13)
                    {
                        strBet += char(event.text.unicode);
                        textBet.setString(strBet);
                    }
                    if(event.text.unicode == 8 && event.type == Event::TextEntered)
                    {
                        strBet = "";
                        textBet.setString(strBet);
                    }
                    if(event.type == Event::TextEntered && event.text.unicode == 13)
                    {
                        if(strBet == strAns)
                        {
                            strPrint = strAns;
                        }
                        else
                        {
                            turn -= 2;
                        }

                        print.setString(strPrint);
                        heart.setString(string(1, char(turn + 48)));
                        strBet = "";
                        betMode = false;
                    }
                }
                if(strPrint == strAns || turn <= 0)
                    stage = 3;
                break;
            default:
                if(tryAgain.clicked(window))
                    stage = 0;
                break;
        }
    }
    void drawAll(RenderWindow& window)
    {
        window.clear();
        switch(stage)
        {
            case 0:
                window.draw(welcome);
                start.render(window);
                break;
            case 1:
                window.draw(chooseTopic);
                for(int i=0; i<6; i++)
                    topic[i].render(window);
                break;
            case 2:
                if(betMode == true)
                {
                    window.draw(getBet);
                    window.draw(textBet);
                }
                if(suggestMode == true)
                {
                    window.draw(getSuggest);
                    window.draw(textSuggest);
                }
                if(betMode == false && suggestMode == false)
                {
                    suggest.render(window);
                    bet.render(window);
                    window.draw(text);
                    window.draw(print);
                    window.draw(heart);
                    window.draw(guess);
                    window.draw(wrong);
                    window.draw(textTimeSuggest);
                }
                break;
            default:
                if(strPrint == strAns)
                    window.draw(win);
                if(turn <= 0)
                    window.draw(loss);
                tryAgain.render(window);
                break;
        }
    }
};

int main(){
    RenderWindow window(VideoMode(500, 700), "New hang man !!");
    Game game;

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
            game.update(window, event);
        }

        game.drawAll(window);
        window.display();
    }

    return 0;
}

// cd "d:\Workspace\Code\SFML\File_code\" ; if ($?) { g++ hang_man.cpp -o hang_man -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio} ; if ($?) { .\hang_man }