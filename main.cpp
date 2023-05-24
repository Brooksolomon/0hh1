#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>

#include <iostream>

#include <vector>

#include <string>

#include <ctime>

#include <cstdlib>

#include <iomanip>

#include <fstream>

#include "GAME4.h"

#include "GAME6.h"

#include "GAME8.h"

#include <stdio.h>

bool checkBackButton;

int SIZExSIZE = 4;

using namespace std;

int main();

sf::RectangleShape spawnblocks(float x, float y) {
    //creating the music on and off button
    sf::RectangleShape blocks;
    blocks.setPosition(x, y);
    blocks.setSize(sf::Vector2f(50.f, 50.f));
    if (!MusicOn) {
        blocks.setFillColor(sf::Color(42, 42, 42));
        blocks.setOutlineColor(sf::Color(42, 42, 42));
    } else {
        blocks.setFillColor(sf::Color(255, 213, 0));
        blocks.setOutlineColor(sf::Color(204, 170, 0));
    }
    blocks.setOutlineThickness(10.f);
    return blocks;
}
sf::RectangleShape spawnSOUNDblocks(float x, float y) {
    //generate the block for turning sound on and off in the pause menu
    sf::RectangleShape blocks;
    blocks.setPosition(x, y);
    blocks.setSize(sf::Vector2f(50.f, 50.f));
    if (!SoundOn4) {
        blocks.setFillColor(sf::Color(42, 42, 42));
        blocks.setOutlineColor(sf::Color(42, 42, 42));
    } else {
        blocks.setFillColor(sf::Color(255, 213, 0));
        blocks.setOutlineColor(sf::Color(204, 170, 0));
    }
    blocks.setOutlineThickness(10.f);
    return blocks;
}

sf::RectangleShape spawnblocks(int colorCode, float x, float y) {
    //function used to generate every row and column of the games grid
    sf::RectangleShape blocks;
    blocks.setPosition(x, y);
    blocks.setSize(sf::Vector2f(50.f, 50.f));

    if (colorCode == 0) {
        blocks.setFillColor(sf::Color(42, 42, 42));
        blocks.setOutlineColor(sf::Color(42, 42, 42));
    } else if (colorCode == 1) {
        blocks.setFillColor(sf::Color(255, 213, 0));
        blocks.setOutlineColor(sf::Color(204, 170, 0));

    } else if (colorCode == 2) {
        blocks.setFillColor(sf::Color(0, 89, 190));
        blocks.setOutlineColor(sf::Color(0, 71, 152));
    }
    blocks.setOutlineThickness(10.f);

    return blocks;
}

int soundAdjust(sf::Music & music, sf::Sound & sound,int pausetime) {
    //the pause menu window and all its settings
    sf::RenderWindow win(sf::VideoMode(600, 600), "Settings", sf::Style::Titlebar | sf::Style::Close);

    //setting a timer for how long we spent in the time menu
    clock_t start;
    start = clock();
    int seconds;

    //main game loop
    while (win.isOpen()) {
        seconds = (clock() - start) / (int) CLOCKS_PER_SEC;

        float Mousex, Mousey;

        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                win.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                Mousex = sf::Mouse::getPosition(win).x;
                Mousey = sf::Mouse::getPosition(win).y;
            }

            sf::Font font;
            if (!font.loadFromFile("BERNHC.TTF")) {
                cout << "error";
            }

            // writing the texts in the pause menu
            sf::Text MusicButton;
            MusicButton.setFont(font);
            MusicButton.setString("Music:");
            MusicButton.setCharacterSize(70);
            MusicButton.setFillColor(sf::Color::White);
            MusicButton.setPosition(30.f, 200.f);

            sf::Text SoundButton;
            SoundButton.setFont(font);
            SoundButton.setString("Sound:");
            SoundButton.setCharacterSize(70);
            SoundButton.setFillColor(sf::Color::White);
            SoundButton.setPosition(20.f, 320.f);

            sf::Text info;
            info.setFont(font);
            info.setString("backspace to get back into game");
            info.setCharacterSize(30);
            info.setFillColor(sf::Color::White);
            info.setPosition(40.f, 500.f);

            if (Mousex > 240.f && Mousey > 200.f && Mousex < 240.f + 85.f && Mousey < 200.f + 85.f) {
                //if the music button is pressed
                if (SoundOn4)
                    sound.play();
                if (MusicOn) {
                    MusicOn = false;
                    music.stop();
                } else {
                    MusicOn = true;
                    music.play();
                }
            }
            if (Mousex > 240.f && Mousey > 340.f && Mousex < 240.f + 85.f && Mousey < 340.f + 85.f) {
                //if the sound button is pressed
                if (SoundOn4)
                    sound.play();

                if (SoundOn4) {
                    SoundOn4 = false;
                } else {
                    SoundOn4 = true;
                }
            }

            Mousex = 0;
            Mousey = 0;

            win.clear(sf::Color(34, 34, 34));

            win.draw(MusicButton);
            win.draw(SoundButton);
            win.draw(info);

            win.draw(spawnblocks(240.f, 220.f));
            win.draw(spawnSOUNDblocks(240.f, 340.f));

            win.display();

        }
    }
    return pausetime + seconds;
}
void CreateGame(sf::Music & music, sf::Sound & sound) {
    //the function that gets called when they press new game
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "0h h1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    //mouse click positions
    int Mousex = -1, Mousey = -1;
    //open font file
    sf::Font font;
    if (!font.loadFromFile("BERNHC.TTF")) {
        cout << "error";
    }

    //open files of the respective grids to display the highscores
    ifstream inf;
    if (SIZExSIZE == 4)
        inf.open("High4.txt");
    else if (SIZExSIZE == 6)
        inf.open("High6.txt");
    else if (SIZExSIZE == 8)
        inf.open("High8.txt");

    int min = 0, secon;

    if (inf) {
        inf >> secon;
    }

    //turn the seconds into minutes if it is past 59
    while (secon >= 60) {
        min++;
        secon -= 60;
    }

    //prints the high score onto the screen
    string nameheader;
    if (secon < 10)
        nameheader = "High score " + to_string(min) + " : 0" + to_string(secon);
    else
        nameheader = "High score " + to_string(min) + " : " + to_string(secon);

    //high score
    sf::Text high;
    high.setFont(font);
    high.setString(nameheader);
    high.setCharacterSize(50);
    high.setFillColor(sf::Color::White);
    high.setPosition(30.f, 50.f);

    //undo button
    sf::Text undo;
    undo.setFont(font);
    undo.setString("undo");
    undo.setCharacterSize(60);
    undo.setFillColor(sf::Color::White);
    undo.setPosition(600.f, 900.f);

    //New game button
    sf::Text New;
    New.setFont(font);
    New.setString("New Game");
    New.setCharacterSize(50);
    New.setFillColor(sf::Color::White);
    New.setPosition(1400.f, 50.f);

    //reset button
    sf::Text reset;
    reset.setFont(font);
    reset.setString("Reset");
    reset.setCharacterSize(60);
    reset.setFillColor(sf::Color::White);
    reset.setPosition(1220.f, 900.f);

    //hint button
    sf::Text hint;
    hint.setFont(font);
    hint.setString("hint");
    hint.setCharacterSize(60);
    hint.setFillColor(sf::Color::White);
    hint.setPosition(900.f, 900.f);

    //save button
    sf::Text save;
    save.setFont(font);
    save.setString("Save & exit");
    save.setCharacterSize(40);
    save.setFillColor(sf::Color::White);
    save.setPosition(1700.f, 60.f);

    //array of all the tables values
    int colorCode4[4][4] = {
        0
    };

    int colorCode6[6][6] = {
        0
    };

    int colorCode8[8][8] = {
        0
    };

    //if its a new game , calls the new game generator function so that we can there will be some base blocks placed
    if (NEWGAME == true) {
        if (SIZExSIZE == 4) {
            newGameGenerator4(colorCode4, truthTable4);
        }
        if (SIZExSIZE == 6) {
            newGameGenerator6(colorCode6, truthTable6);
        }
        if (SIZExSIZE == 8) {
            newGameGenerator8(colorCode8, truthTable8);
        }

    }

    //getting the start of the clock
    clock_t start;
    start = clock();
    int starter = clock();
    int minutes = 0, seconds;
    int sec;
    int pausetime = 0;

    while (window.isOpen()) {

        //for the timer
        seconds = (clock() - start) / (int) CLOCKS_PER_SEC - (pausetime);
        if (seconds > 59) {
            minutes++;
            start = clock();
            pausetime=0;
        }
        string timer;
        if (seconds < 10)
            timer = to_string(minutes) + ":0" + to_string(seconds);
        else
            timer = to_string(minutes) + ":" + to_string(seconds);

        //printing the time
        sf::Text time;
        time.setFont(font);
        time.setString(timer);
        time.setCharacterSize(80);
        time.setFillColor(sf::Color::White);
        time.setPosition(880.f, 50.f);

        sec = ((clock() - starter) / (int) CLOCKS_PER_SEC )-pausetime;

        //for the percentage

        string percent;
        if (SIZExSIZE == 4)
            percent = to_string(check_Percentage4(colorCode4, truthTable4)) + " %";
        else if (SIZExSIZE == 6)
            percent = to_string(check_Percentage6(colorCode6, truthTable6)) + " %";
        else if (SIZExSIZE == 8)
            percent = to_string(check_Percentage8(colorCode8, truthTable8)) + " %";
        sf::Text percentile;
        percentile.setFont(font);
        percentile.setString(percent);
        percentile.setCharacterSize(60);
        percentile.setFillColor(sf::Color::White);
        percentile.setPosition(910.f, 150.f);

        //game over checker
        if (SIZExSIZE == 4)
            Gameover4(colorCode4, truthTable4, window, timer, sec);
        if (SIZExSIZE == 6)
            Gameover6(colorCode6, truthTable6, window, timer, sec);
        if (SIZExSIZE == 8)
            Gameover8(colorCode8, truthTable8, window, timer, sec);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                Mousex = sf::Mouse::getPosition(window).x;
                Mousey = sf::Mouse::getPosition(window).y;

            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            pausetime = soundAdjust(music, sound,pausetime);

        }

        window.clear(sf::Color(34, 34, 34));

        //if new game it will just call the game function but if its a reset , will call the game with the same layout as how the game started instead of a new generator
        if (SIZExSIZE == 4) {
            if (NEWGAME == true) {
                thegame4(window, Mousex, Mousey, colorCode4, truthTable4, sound, music, sec);
            } else {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        NEWGAME = true;
                        colorCode4[i][j] = colorCode4clone[i][j];
                    }
                }
                thegame4(window, Mousex, Mousey, colorCode4, truthTable4, sound, music, sec);
            }
        } else if (SIZExSIZE == 6) {
            if (NEWGAME == true) {
                thegame6(window, Mousex, Mousey, colorCode6, truthTable6, sound, music, sec);
            } else {
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 6; j++) {
                        NEWGAME = true;
                        colorCode6[i][j] = colorCode6clone[i][j];
                    }
                }
                thegame6(window, Mousex, Mousey, colorCode6, truthTable6, sound, music, sec);
            }
        } else if (SIZExSIZE == 8) {
            if (NEWGAME == true) {
                thegame8(window, Mousex, Mousey, colorCode8, truthTable8, sound, music, sec);
            } else {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        NEWGAME = true;
                        colorCode8[i][j] = colorCode8clone[i][j];
                    }
                }
                thegame8(window, Mousex, Mousey, colorCode8, truthTable8, sound, music, sec);
            }
        }

        window.draw(high);
        window.draw(undo);
        window.draw(New);
        window.draw(time);
        window.draw(percentile);
        window.draw(reset);
        window.draw(hint);
        window.draw(save);

        window.display();
    }

}
void LoadGame(sf::Music & music, sf::Sound & sound) {
    //a function for when they press continue game
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "0h h1", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    //mouse click positions
    int Mousex = -1, Mousey = -1;
    //open font file
    sf::Font font;
    if (!font.loadFromFile("BERNHC.TTF")) {
        cout << "error";
    }

    //opening the files of highscores
    ifstream inf;
    if (SIZExSIZE == 4)
        inf.open("High4.txt");
    else if (SIZExSIZE == 6)
        inf.open("High6.txt");
    else if (SIZExSIZE == 8)
        inf.open("High8.txt");

    int min = 0, secon;

    //converting seconds to minutes
    if (inf) {
        inf >> secon;
    }
    inf.close();
    while (secon >= 60) {
        min++;
        secon -= 60;
    }

    string nameheader;
    if (secon < 10)
        nameheader = "High score " + to_string(min) + " : 0" + to_string(secon);
    else
        nameheader = "High score " + to_string(min) + " : " + to_string(secon);

    //high score
    sf::Text high;
    high.setFont(font);
    high.setString(nameheader);
    high.setCharacterSize(50);
    high.setFillColor(sf::Color::White);
    high.setPosition(30.f, 50.f);

    //undo button
    sf::Text undo;
    undo.setFont(font);
    undo.setString("undo");
    undo.setCharacterSize(60);
    undo.setFillColor(sf::Color::White);
    undo.setPosition(600.f, 900.f);

    //New game button
    sf::Text New;
    New.setFont(font);
    New.setString("New Game");
    New.setCharacterSize(50);
    New.setFillColor(sf::Color::White);
    New.setPosition(1400.f, 50.f);

    //reset button
    sf::Text reset;
    reset.setFont(font);
    reset.setString("Reset");
    reset.setCharacterSize(60);
    reset.setFillColor(sf::Color::White);
    reset.setPosition(1220.f, 900.f);

    //hint button
    sf::Text hint;
    hint.setFont(font);
    hint.setString("hint");
    hint.setCharacterSize(60);
    hint.setFillColor(sf::Color::White);
    hint.setPosition(900.f, 900.f);

    //save button
    sf::Text save;
    save.setFont(font);
    save.setString("Save");
    save.setCharacterSize(50);
    save.setFillColor(sf::Color::White);
    save.setPosition(1750.f, 50.f);

    //array of all the tables values
    int colorCode4[4][4] = {
        0
    };


    //reading in the saved file for where the player saved their game and their time when they stopped so that it can resume from where they stopped
    ifstream reader;
    int holdtime;
    if (SIZExSIZE == 4) {
        reader.open("Game4SaveTable.txt");
        if (reader) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    reader >> colorCode4[i][j];
                }
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    reader >> truthTable4[i][j];
                }
            }
            reader >> holdtime;

        }
    }

    int colorCode6[6][6] = {
        0
    };
    if (SIZExSIZE == 6)

    {
        reader.open("Game6SaveTable.txt");
        if (reader) {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    reader >> colorCode6[i][j];
                }
            }
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    reader >> truthTable6[i][j];
                }
            }
            reader >> holdtime;

        }
    }

    int colorCode8[8][8] = {
        0
    };

    if (SIZExSIZE == 8)

    {
        reader.open("Game8SaveTable.txt");
        if (reader) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    reader >> colorCode8[i][j];
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    reader >> truthTable8[i][j];
                }
            }
            reader >> holdtime;

        }
    }

    reader.close();

    //getting the start of the clock
    clock_t start;
    start = clock();
    int starter = clock();
    int minutes = 0, seconds;
    int sec;
    int pausetime = 0;

    while (window.isOpen()) {

        //for the timer
        seconds = ((clock() - start) / (int) CLOCKS_PER_SEC )- (pausetime);
        seconds += holdtime;
        if (seconds > 59) {
            minutes++;
            start = clock();
            pausetime=0;
        }
        string timer;
        if (seconds < 10)
            timer = to_string(minutes) + ":0" + to_string(seconds);
        else
            timer = to_string(minutes) + ":" + to_string(seconds);

        sf::Text time;
        time.setFont(font);
        time.setString(timer);
        time.setCharacterSize(80);
        time.setFillColor(sf::Color::White);
        time.setPosition(880.f, 50.f);

        sec = ((clock() - starter) / (int) CLOCKS_PER_SEC )-pausetime;
        sec += holdtime;

        //for the percentage

        string percent;
        if (SIZExSIZE == 4)
            percent = to_string(check_Percentage4(colorCode4, truthTable4)) + " %";
        else if (SIZExSIZE == 6)
            percent = to_string(check_Percentage6(colorCode6, truthTable6)) + " %";
        else if (SIZExSIZE == 8)
            percent = to_string(check_Percentage8(colorCode8, truthTable8)) + " %";
        sf::Text percentile;
        percentile.setFont(font);
        percentile.setString(percent);
        percentile.setCharacterSize(60);
        percentile.setFillColor(sf::Color::White);
        percentile.setPosition(910.f, 150.f);

        //game over checker
        if (SIZExSIZE == 4)
            Gameover4(colorCode4, truthTable4, window, timer, sec);
        if (SIZExSIZE == 6)
            Gameover6(colorCode6, truthTable6, window, timer, sec);
        if (SIZExSIZE == 8)
            Gameover8(colorCode8, truthTable8, window, timer, sec);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                Mousex = sf::Mouse::getPosition(window).x;
                Mousey = sf::Mouse::getPosition(window).y;

            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            pausetime = soundAdjust(music, sound,pausetime);

        }

        window.clear(sf::Color(34, 34, 34));

        if (SIZExSIZE == 4) {
            thegame4(window, Mousex, Mousey, colorCode4, truthTable4, sound, music, sec);
        } else if (SIZExSIZE == 6) {
            thegame6(window, Mousex, Mousey, colorCode6, truthTable6, sound, music, sec);
        } else if (SIZExSIZE == 8) {
            thegame8(window, Mousex, Mousey, colorCode8, truthTable8, sound, music, sec);
        }

        window.draw(high);
        window.draw(undo);
        window.draw(New);
        window.draw(time);
        window.draw(percentile);
        window.draw(reset);
        window.draw(hint);
        window.draw(save);

        window.display();
    }
}

void Levels() {
    // Create the window where we pick which grid size we want
    sf::RenderWindow app(sf::VideoMode(1920, 1080), "oh no");

    sf::RectangleShape four;
    four.setPosition(sf::Vector2f(670, 420));
    four.setFillColor(sf::Color(255, 213, 0));
    four.setSize(sf::Vector2f(180.f, 180.f));
    four.setOutlineColor(sf::Color(204, 170, 0));
    four.setOutlineThickness(25.f);

    sf::RectangleShape six;
    six.setPosition(sf::Vector2f(920, 420));
    six.setFillColor(sf::Color(255, 213, 0));
    six.setSize(sf::Vector2f(180.f, 180.f));
    six.setOutlineColor(sf::Color(204, 170, 0));
    six.setOutlineThickness(25.f);

    sf::RectangleShape eight;
    eight.setPosition(sf::Vector2f(1170, 420));
    eight.setFillColor(sf::Color(255, 213, 0));
    eight.setSize(sf::Vector2f(180.f, 180.f));
    eight.setOutlineColor(sf::Color(204, 170, 0));
    eight.setOutlineThickness(25.f);

    sf::Font font;
    if (!font.loadFromFile("BERNHC.TTF")) {
        cout << "error";
    }

    sf::Text name;
    name.setFont(font);
    name.setString("oh no");
    name.setCharacterSize(150);
    name.setFillColor(sf::Color::White);
    name.setPosition(800.f, 150.f);

    sf::Text FxF;
    FxF.setFont(font);
    FxF.setString("4 x 4");
    FxF.setCharacterSize(80);
    FxF.setFillColor(sf::Color(0, 89, 190));
    FxF.setPosition(675.f, 450.f);

    sf::Text SxS;
    SxS.setFont(font);
    SxS.setString("6 x 6");
    SxS.setCharacterSize(80);
    SxS.setFillColor(sf::Color(0, 89, 190));
    SxS.setPosition(925.f, 450.f);

    sf::Text ExE;
    ExE.setFont(font);
    ExE.setString("8 x 8");
    ExE.setCharacterSize(80);
    ExE.setFillColor(sf::Color(0, 89, 190));
    ExE.setPosition(1175.f, 450.f);

    int Mx, My;

    // Start the game loop
    while (app.isOpen()) {
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed){
                app.close();
                main();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                Mx = sf::Mouse::getPosition(app).x;
                My = sf::Mouse::getPosition(app).y;
            }

        }

        if (Mx > 650.f && My > 400.f && Mx < 650.f + 200.f && My < 400.f + 200.f) {
            SIZExSIZE = 4;
            checkBackButton=true;
            app.close();
        }

        if (Mx > 900.f && My > 400.f && Mx < 900.f + 200.f && My < 400.f + 200.f) {
            SIZExSIZE = 6;
            checkBackButton=true;
            app.close();
        }

        if (Mx > 1150.f && My > 400.f && Mx < 1150.f + 200.f && My < 400.f + 200.f) {
            SIZExSIZE = 8;
            checkBackButton=true;
            app.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            app.close();
            main();
        }

        app.clear(sf::Color(34, 34, 34));

        app.draw(name);
        app.draw(four);
        app.draw(six);
        app.draw(eight);
        app.draw(FxF);
        app.draw(SxS);
        app.draw(ExE);

        app.display();
    }
}

void DisplayHighs() {
    //a function for the high scores menu to see all the top scores
    sf::RenderWindow HighMenu(sf::VideoMode(1920, 1080), "0h h1", sf::Style::Titlebar | sf::Style::Close);
    HighMenu.setFramerateLimit(60);

    //open font file
    sf::Font font;
    if (!font.loadFromFile("BERNHC.TTF")) {
        cout << "error";
    }

    //high score text
    sf::Text highmaintext;
    highmaintext.setFont(font);
    highmaintext.setString("High scores");
    highmaintext.setCharacterSize(80);
    highmaintext.setFillColor(sf::Color::White);
    highmaintext.setPosition(770.f, 50.f);

    ifstream high4("High4.txt");
    ifstream high6("High6.txt");
    ifstream high8("High8.txt");

    int min1 = 0, secon1;

    if (high4) {
        high4 >> secon1;
    }
    high4.close();
    while (secon1 >= 60) {
        min1++;
        secon1 -= 60;
    }

    //printing the 3 highscores
    string high1;
    if (secon1 >= 10)
        high1 = "4x4: " + to_string(min1) + " : " + to_string(secon1);
    else
        high1 = "4x4: " + to_string(min1) + " : 0" + to_string(secon1);

    int min2 = 0, secon2;

    if (high6) {
        high6 >> secon2;
    }
    high6.close();
    while (secon2 >= 60) {
        min2++;
        secon2 -= 60;
    }
    string high2;
    if (secon2 >= 10)
        high2 = "6x6: " + to_string(min2) + " : " + to_string(secon2);
    else
        high2 = "6x6: " + to_string(min2) + " : 0" + to_string(secon2);

    int min3 = 0, secon3;

    if (high8) {
        high8 >> secon3;
    }
    high8.close();
    while (secon3 >= 60) {
        min3++;
        secon3 -= 60;
    }

    string high3;
    if (secon3 >= 10)
        high3 = "8x8: " + to_string(min3) + " : " + to_string(secon3);
    else
        high3 = "8x8: " + to_string(min3) + " :0 " + to_string(secon3);

    //high score 1
    sf::Text highf;
    highf.setFont(font);
    highf.setString(high1);
    highf.setCharacterSize(50);
    highf.setFillColor(sf::Color::White);
    highf.setPosition(850.f, 350.f);

    //high score 2
    sf::Text highs;
    highs.setFont(font);
    highs.setString(high2);
    highs.setCharacterSize(50);
    highs.setFillColor(sf::Color::White);
    highs.setPosition(850.f, 450.f);

    //high score 3
    sf::Text highe;
    highe.setFont(font);
    highe.setString(high3);
    highe.setCharacterSize(50);
    highe.setFillColor(sf::Color::White);
    highe.setPosition(850.f, 550.f);

    //helper
    sf::Text helper;
    helper.setFont(font);
    helper.setString("Backspace to go back to main menu");
    helper.setCharacterSize(30);
    helper.setFillColor(sf::Color::White);
    helper.setPosition(750.f, 900.f);

    //decoration blocks
    sf::RectangleShape blocks1;
    blocks1.setPosition(350.f, 350.f);
    blocks1.setSize(sf::Vector2f(50.f, 50.f));
    blocks1.setFillColor(sf::Color(255, 213, 0));
    blocks1.setOutlineColor(sf::Color(204, 170, 0));
    blocks1.setOutlineThickness(10.f);

    sf::RectangleShape blocks2;
    blocks2.setPosition(350.f, 450.f);
    blocks2.setSize(sf::Vector2f(50.f, 50.f));
    blocks2.setFillColor(sf::Color(255, 213, 0));
    blocks2.setOutlineColor(sf::Color(204, 170, 0));
    blocks2.setOutlineThickness(10.f);

    sf::RectangleShape blocks3;
    blocks3.setPosition(350.f, 550.f);
    blocks3.setSize(sf::Vector2f(50.f, 50.f));
    blocks3.setFillColor(sf::Color(255, 213, 0));
    blocks3.setOutlineColor(sf::Color(204, 170, 0));
    blocks3.setOutlineThickness(10.f);

    sf::RectangleShape blocks5;
    blocks5.setPosition(1550.f, 350.f);
    blocks5.setSize(sf::Vector2f(50.f, 50.f));
    blocks5.setFillColor(sf::Color(0, 89, 190));
    blocks5.setOutlineColor(sf::Color(0, 71, 152));
    blocks5.setOutlineThickness(10.f);

    sf::RectangleShape blocks6;
    blocks6.setPosition(1550.f, 450.f);
    blocks6.setSize(sf::Vector2f(50.f, 50.f));
    blocks6.setFillColor(sf::Color(0, 89, 190));
    blocks6.setOutlineColor(sf::Color(0, 71, 152));
    blocks6.setOutlineThickness(10.f);

    sf::RectangleShape blocks7;
    blocks7.setPosition(1550.f, 550.f);
    blocks7.setSize(sf::Vector2f(50.f, 50.f));
    blocks7.setFillColor(sf::Color(0, 89, 190));
    blocks7.setOutlineColor(sf::Color(0, 71, 152));
    blocks7.setOutlineThickness(10.f);

    while (HighMenu.isOpen()) {
        sf::Event event;
        while (HighMenu.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                HighMenu.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            HighMenu.close();
            main();
        }
        HighMenu.clear(sf::Color(34, 34, 34));
        HighMenu.draw(highmaintext);
        HighMenu.draw(highf);
        HighMenu.draw(highs);
        HighMenu.draw(highe);
        HighMenu.draw(blocks1);
        HighMenu.draw(blocks2);
        HighMenu.draw(blocks3);
        HighMenu.draw(blocks5);
        HighMenu.draw(blocks6);
        HighMenu.draw(blocks7);
        HighMenu.draw(helper);
        HighMenu.display();

    }

}

int main() {
    //our main starting main menu
    sf::RenderWindow StartMenu(sf::VideoMode(1920, 1080), "0h no", sf::Style::Titlebar | sf::Style::Close);
    StartMenu.setFramerateLimit(60);
    //mouse click positions
    int Mousex = -1, Mousey = -1;

    //open font file
    sf::Font font;
    if (!font.loadFromFile("BERNHC.TTF")) {
        cout << "error";
    }

    //open background music
    sf::Music music;
    if (!music.openFromFile("main.ogg")) {
        cout << "error music did not open";
    }
    music.play();

    //open audio file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("click.wav")) {
        cout << "error didnt open click sound";
    }
    sf::Sound sound;
    sound.setBuffer(buffer);

    //Game title
    sf::Text title;
    title.setFont(font);
    title.setString("Oh h1");
    title.setCharacterSize(150);
    title.setFillColor(sf::Color::White);
    title.setPosition(650.f, 50.f);
    title.setLetterSpacing(5.f);

    //new game button
    sf::Text NG;
    NG.setFont(font);
    NG.setString("New game");
    NG.setCharacterSize(50);
    NG.setFillColor(sf::Color::White);
    NG.setPosition(850.f, 350.f);

    //continue game button
    sf::Text CG;
    CG.setFont(font);
    CG.setString("Contine game");
    CG.setCharacterSize(50);
    CG.setFillColor(sf::Color::White);
    CG.setPosition(820.f, 450.f);

    //highscores button
    sf::Text HS;
    HS.setFont(font);
    HS.setString("High scores");
    HS.setCharacterSize(50);
    HS.setFillColor(sf::Color::White);
    HS.setPosition(840.f, 550.f);

    //tip
    sf::Text tip;
    tip.setFont(font);
    tip.setString("Tip : double tap for hint");
    tip.setCharacterSize(30);
    tip.setFillColor(sf::Color::White);
    tip.setPosition(800.f, 930.f);

    //exit button
    sf::Text exitbutton;
    exitbutton.setFont(font);
    exitbutton.setString("Exit");
    exitbutton.setCharacterSize(50);
    exitbutton.setFillColor(sf::Color::White);
    exitbutton.setPosition(930.f, 650.f);

    //decoration blocks
    sf::RectangleShape blocks1;
    blocks1.setPosition(350.f, 350.f);
    blocks1.setSize(sf::Vector2f(50.f, 50.f));
    blocks1.setFillColor(sf::Color(255, 213, 0));
    blocks1.setOutlineColor(sf::Color(204, 170, 0));
    blocks1.setOutlineThickness(10.f);

    sf::RectangleShape blocks2;
    blocks2.setPosition(350.f, 450.f);
    blocks2.setSize(sf::Vector2f(50.f, 50.f));
    blocks2.setFillColor(sf::Color(255, 213, 0));
    blocks2.setOutlineColor(sf::Color(204, 170, 0));
    blocks2.setOutlineThickness(10.f);

    sf::RectangleShape blocks3;
    blocks3.setPosition(350.f, 550.f);
    blocks3.setSize(sf::Vector2f(50.f, 50.f));
    blocks3.setFillColor(sf::Color(255, 213, 0));
    blocks3.setOutlineColor(sf::Color(204, 170, 0));
    blocks3.setOutlineThickness(10.f);

    sf::RectangleShape blocks4;
    blocks4.setPosition(350.f, 650.f);
    blocks4.setSize(sf::Vector2f(50.f, 50.f));
    blocks4.setFillColor(sf::Color(255, 213, 0));
    blocks4.setOutlineColor(sf::Color(204, 170, 0));
    blocks4.setOutlineThickness(10.f);

    sf::RectangleShape blocks5;
    blocks5.setPosition(1550.f, 350.f);
    blocks5.setSize(sf::Vector2f(50.f, 50.f));
    blocks5.setFillColor(sf::Color(0, 89, 190));
    blocks5.setOutlineColor(sf::Color(0, 71, 152));
    blocks5.setOutlineThickness(10.f);

    sf::RectangleShape blocks6;
    blocks6.setPosition(1550.f, 450.f);
    blocks6.setSize(sf::Vector2f(50.f, 50.f));
    blocks6.setFillColor(sf::Color(0, 89, 190));
    blocks6.setOutlineColor(sf::Color(0, 71, 152));
    blocks6.setOutlineThickness(10.f);

    sf::RectangleShape blocks7;
    blocks7.setPosition(1550.f, 550.f);
    blocks7.setSize(sf::Vector2f(50.f, 50.f));
    blocks7.setFillColor(sf::Color(0, 89, 190));
    blocks7.setOutlineColor(sf::Color(0, 71, 152));
    blocks7.setOutlineThickness(10.f);

    sf::RectangleShape blocks8;
    blocks8.setPosition(1550.f, 650.f);
    blocks8.setSize(sf::Vector2f(50.f, 50.f));
    blocks8.setFillColor(sf::Color(0, 89, 190));
    blocks8.setOutlineColor(sf::Color(0, 71, 152));
    blocks8.setOutlineThickness(10.f);

    while (StartMenu.isOpen()) {
        sf::Event event;
        while (StartMenu.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                StartMenu.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                Mousex = sf::Mouse::getPosition(StartMenu).x;
                Mousey = sf::Mouse::getPosition(StartMenu).y;
            }

        }
        if (Mousex > 850.f && Mousey > 350.f && Mousex < 850.f + 250.f && Mousey < 350.f + 60.f) {
                //if new game is pressed
            if (SoundOn4) {
                sound.play();
            }
            StartMenu.close();
            Levels();
            if(checkBackButton)
                CreateGame(music, sound);

        }
        if (Mousex > 820.f && Mousey > 450.f && Mousex < 820.f + 250.f && Mousey < 450.f + 60.f) {
                //if continue game was pressed
            if (SoundOn4) {
                sound.play();
            }
            StartMenu.close();
            Levels();
            if(checkBackButton)
                LoadGame(music, sound);


        }
        if (Mousex > 840.f && Mousey > 550.f && Mousex < 840.f + 200.f && Mousey < 550.f + 60.f) {
                //if higscore was pressed
            if (SoundOn4)
                sound.play();
            StartMenu.close();
            DisplayHighs();

        }
        if (Mousex > 930.f && Mousey > 650.f && Mousex < 930.f + 100.f && Mousey < 650.f + 60.f) {
                //if exit was pressed
            if (SoundOn4)
                sound.play();

            StartMenu.close();
        }
        Mousex = 0;
        Mousey = 0;

        StartMenu.clear(sf::Color(34, 34, 34));
        StartMenu.draw(title);
        StartMenu.draw(NG);
        StartMenu.draw(CG);
        StartMenu.draw(HS);
        StartMenu.draw(blocks1);
        StartMenu.draw(blocks2);
        StartMenu.draw(blocks3);
        StartMenu.draw(blocks4);
        StartMenu.draw(blocks5);
        StartMenu.draw(blocks6);
        StartMenu.draw(blocks7);
        StartMenu.draw(blocks8);
        StartMenu.draw(tip);
        StartMenu.draw(exitbutton);

        StartMenu.display();

    }

    return 0;
}
