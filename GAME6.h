#ifndef GAME6_H_INCLUDED
#define GAME6_H_INCLUDED
#include<iostream>

#include "GAME4.h"

using namespace std;
int colorCode6clone[6][6] = {
    0
};
extern bool truthTable6[6][6] = {
    false
};

sf::RectangleShape spawnblocks(int colorCode, float x, float y);

int check_Percentage6(int colorCode[6][6], bool truthTable[6][6]) {
    //checks at what percentage of completion the player is at
    float counter = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (colorCode[i][j] != 0 && truthTable[i][j] == false) {
                counter += 3.57143;
            }
        }
    }
    return counter;

}

void Gameover6(int colorCode[6][6], bool truthTable[6][6], sf::RenderWindow & window, string timer, int sec) {
    //checks if the game has been won and prints the end game screen
    int perRow[6] = {
        0
    };
    if (check_Percentage6(colorCode, truthTable) == 100) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (colorCode[i][j] == 1) {
                    perRow[i]++;
                }
            }
        }
        bool checker = true;
        for (int i = 0; i < 6; i++) {
            if (perRow[i] != 3) {
                checker = false;
            }
        }
        if (checker) {
            window.close();
            sf::RenderWindow win(sf::VideoMode(1920, 1080), "DONE !!!", sf::Style::Titlebar | sf::Style::Close);

            //open font file
            sf::Font font;
            if (!font.loadFromFile("BERNHC.TTF")) {
                cout << "error";
            }
            sf::Text text;
            text.setFont(font);
            text.setString("YOU WIN !!!");
            text.setCharacterSize(90);
            text.setFillColor(sf::Color::White);
            text.setLetterSpacing(5.f);
            text.setPosition(650.f, 460.f);
            text.setOutlineColor(sf::Color::Red);
            text.setOutlineThickness(-3.f);

            timer = "Time : " + timer;

            sf::Text time;
            time.setFont(font);
            time.setString(timer);
            time.setCharacterSize(60);
            time.setFillColor(sf::Color::White);
            time.setPosition(810.f, 580.f);

            //congra text
            sf::Text cong;
            cong.setFont(font);
            cong.setString("You broke the highscore");
            cong.setCharacterSize(40);
            cong.setFillColor(sf::Color::White);
            cong.setPosition(780.f, 800.f);

            ifstream inf;
            int num;
            inf.open("High6.txt");

            bool congra = false;
            if (inf) {
                inf >> num;
                if (sec < num) {

                    ofstream onf;
                    onf.open("High6.txt");

                    if (onf) {
                        onf << sec;
                        onf.close();
                    }
                    congra = true;

                } else {
                    sec = num;

                }
            }

            int min = 0;
            while (sec >= 60) {
                min++;
                sec -= 60;
            }

            string highs;
            if (sec < 10)
                highs = " Highscore : " + to_string(min) + ": 0" + to_string(sec);
            else
                highs = " Highscore : " + to_string(min) + " : " + to_string(sec);

            sf::Text high;
            high.setFont(font);
            high.setString(highs);
            high.setCharacterSize(60);
            high.setFillColor(sf::Color::White);
            high.setPosition(780.f, 880.f);


             sf::Text info;
            info.setFont(font);
            info.setString("press back button to go back to main menu");
            info.setCharacterSize(40);
            info.setFillColor(sf::Color::White);
            info.setPosition(650.f, 50.f);

            while (win.isOpen()) {

                sf::Event event;
                while (win.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        win.close();
                    else if (event.type == sf::Keyboard::Escape)
                        win.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                    win.close();
                    main();
                 }

                win.clear(sf::Color(34, 34, 34));

                win.draw(text);
                win.draw(time);
                win.draw(high);
                win.draw(info);
                if (congra)
                    win.draw(cong);

                win.display();
            }

        }
    }
}

void newGameGenerator6(int colorCode[6][6], bool truthTable[6][6]) {
    //generated a new game board that is completly random every single time
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            colorCode[i][j] = 0;
            colorCode6clone[i][j] = 0;
            truthTable[i][j] = false;
        }
    }
    int Column, Row;
    int columnmax[6] = {
        0
    }, rowmax[6] = {
        0
    };
    int colorrand = 0;

    for (int i = 0; i < 8; i++) {
        do {
            srand(time(0) + i);
            Row = (rand() % 6);
            Column = (rand() % 6);
        } while (truthTable[Row][Column] == true || rowmax[Row] == 3 || columnmax[Column] == 3);
        truthTable[Row][Column] = true;

        columnmax[Column]++;
        rowmax[Row]++;

        if (colorrand != (6 / 2)) {
            colorCode[Row][Column] = 1;
            colorCode6clone[Row][Column] = 1;
            colorrand++;
        } else {
            colorCode[Row][Column] = 2;
            colorCode6clone[Row][Column] = 2;
        }
    }

}

void undo6(int colorCode[6][6]) {
    //reverses the last move that was mad on the board
    if (colorCode[xam][yam] == 0) {
        colorCode[xam][yam] = 2;
    } else
        colorCode[xam][yam]--;

    usedUndo = true;

}

string hint6(int colorCode[6][6]) {
    //gives hits based on the current board setting
    string hinter;
    int perRow[6] = {
        0
    }, totalRow[6] = {
        0
    };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (colorCode[i][j] == 1) {
                perRow[i]++;
            }
            if (colorCode[i][j] != 0)
                totalRow[i]++;
        }
        if (totalRow[i] == 6)
            continue;
        if (perRow[i] > 3) {
            hinter = "you cant have more than 3 yellow blocks in one row";
            cout << hinter << endl;
            break;
        }
        if (perRow[i] < 3) {
            hinter = "there is more space open for an extra yellow in the row ";
            hinter = hinter.append(to_string(i + 1));
            cout << hinter << endl;
            break;
        }
        if (perRow[i] == 3) {
            hinter = to_string(i + 1);
            hinter = hinter.append("  row already has 3 yellow blocks");
            cout << hinter << endl;
            break;
        }

    }
    return hinter;
}
void thegame6(sf::RenderWindow & window, int & Mousex, int & Mousey, int colorCode[6][6], bool truthTable[6][6], sf::Sound & sound, sf::Music & music, int time) {
    //checks for where the user clicked and changes its color accordingly and also forbids them from clicking on the default blocks , as well as listens to the input for any of the buttons in the game menu
    float x = 0, y = 0, defaultx = 0;

    x = 715.f;
    y = 315.f;
    defaultx = x;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (Mousex > x && Mousey > y && Mousex < x + 85.f && Mousey < y + 85.f && truthTable[i][j] == false) {
                if (SoundOn4)
                    sound.play();

                xam = i;
                yam = j;
                usedUndo = false;
                if (colorCode[i][j] == 2)
                    colorCode[i][j] = 0;
                else
                    colorCode[i][j]++;

            }
            window.draw(spawnblocks(colorCode[i][j], x, y));
            x += 85.f;
        }
        x = defaultx;
        y += 85.f;
    }
    sf::Font font;
    if (!font.loadFromFile("BERNHC.TTF")) {
        cout << "error";
    }
    sf::Text Undowarn;
    Undowarn.setFont(font);
    Undowarn.setString("X");
    Undowarn.setCharacterSize(150);
    Undowarn.setFillColor(sf::Color::Red);
    Undowarn.setPosition(610.f, 850.f);

    if (Mousex > 600.f && Mousey > 900.f && Mousex < 600.f + 120.f && Mousey < 900.f + 60.f) {
        //when undo button is clicked
        if (SoundOn4)
            sound.play();

        if (usedUndo == false && check_Percentage6(colorCode, truthTable) != 0)
            undo6(colorCode);
        else {

            window.draw(Undowarn);

        }
    }
    if (Mousex > 1400.f && Mousey > 50.f && Mousex < 1400.f + 200.f && Mousey < 50.f + 60.f) {
        //when the new game button is pressed
        if (SoundOn4)
            sound.play();

        MusicOn = true;
        NEWGAME = true;
        window.close();
        CreateGame(music, sound);
    }
    if (Mousex > 1220.f && Mousey > 900.f && Mousex < 1220.f + 120.f && Mousey < 900.f + 60.f) {
        //when the reset button is pressed
        if (SoundOn4)
            sound.play();

        NEWGAME = false;
        window.close();
        CreateGame(music, sound);

    }
    if (Mousex > 900.f && Mousey > 900.f && Mousex < 900.f + 120.f && Mousey < 900.f + 60.f) {
        //if hint button is pressed
        if (SoundOn4)
            sound.play();

        string hinter;
        hinter = hint6(colorCode);

        sf::Font font;
        if (!font.loadFromFile("BERNHC.TTF")) {
            cout << "error";
        }

        sf::Text hintgive;
        hintgive.setFont(font);
        hintgive.setString(hinter);
        hintgive.setCharacterSize(20);
        hintgive.setFillColor(sf::Color::White);
        hintgive.setPosition(690.f, 130.f);

        clock_t start;
        start = clock();
        int seconds;
        window.draw(hintgive);
        seconds = (clock() - start) / (int) CLOCKS_PER_SEC;
        window.draw(hintgive);
        while (seconds < 2) {
            window.draw(hintgive);
            window.draw(hintgive);
            seconds = (clock() - start) / (int) CLOCKS_PER_SEC;
            window.draw(hintgive);
        }

    }
    if (Mousex > 1700.f && Mousey > 50.f && Mousex < 17000.f + 220.f && Mousey < 50.f + 60.f) {
        //when save button is pressed

        if (SoundOn4)
            sound.play();

        ofstream saver("Game6SaveTable.txt");

        if (saver) {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    saver << colorCode[i][j];
                    saver << " ";
                }
            }
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    saver << truthTable[i][j];
                    saver << " ";
                }
            }
            saver << time;
        }
        window.close();

    }

    Mousex = 0;
    Mousey = 0;

}

#endif // GAME6_H_INCLUDED
