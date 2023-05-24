#ifndef GAME4_H_INCLUDED
#define GAME4_H_INCLUDED
#include <string>

#include <iostream>

using namespace std;
int main();
int colorCode4clone[4][4] = {
    0
};
bool truthTable4[4][4] = {
    false
};
int xam, yam;
bool usedUndo, NEWGAME = true;
extern bool SoundOn4 = true;
extern bool MusicOn = true;

void CreateGame(sf::Music & music, sf::Sound & sound);
sf::RectangleShape spawnblocks(int colorCode, float x, float y);





int check_Percentage4(int colorCode[4][4], bool truthTable[4][4]) {
    //checks at what percentage of completion the player is at
    float counter = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (colorCode[i][j] != 0 && truthTable[i][j] == false) {
                counter += 9.09091;
            }
        }
    }
    return counter;

}

void Gameover4(int colorCode[4][4], bool truthTable[4][4], sf::RenderWindow & window, string timer, int sec) {
    //checks if the game has been won and prints the end game screen
    int perRow[4] = {
        0
    };
    if (check_Percentage4(colorCode, truthTable) == 100) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (colorCode[i][j] == 1) {
                    perRow[i]++;
                }
            }
        }
        bool checker = true;
        for (int i = 0; i < 4; i++) {
            if (perRow[i] != 2) {
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
            inf.open("High4.txt");

            bool congra = false;
            if (inf) {
                inf >> num;
                if (sec < num) {

                    ofstream onf;
                    onf.open("High4.txt");

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
            high.setPosition(700.f, 880.f);

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

void newGameGenerator4(int colorCode[4][4], bool truthTable[4][4]) {
    //generated a new game board that is completly random every single time
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            colorCode[i][j] = 0;
            colorCode4clone[i][j] = 0;
            truthTable[i][j] = false;
        }
    }
    int Column, Row;
    int columnmax[4] = {
        0
    }, rowmax[4] = {
        0
    };
    int colorrand = 0;

    for (int i = 0; i < 5; i++) {
        do {
            srand(time(0) + i);
            Row = (rand() % 4);
            Column = (rand() % 4);
        } while (truthTable[Row][Column] == true || rowmax[Row] == 2 || columnmax[Column] == 2);
        truthTable[Row][Column] = true;

        columnmax[Column]++;
        rowmax[Row]++;

        if (colorrand != (4 / 2)) {
            colorCode[Row][Column] = 1;
            colorCode4clone[Row][Column] = 1;
            colorrand++;
        } else {
            colorCode[Row][Column] = 2;
            colorCode4clone[Row][Column] = 2;
        }
    }

}

void undo4(int colorCode[4][4]) {
    //reverses the last move that was mad on the board
    if (colorCode[xam][yam] == 0) {
        colorCode[xam][yam] = 2;
    } else
        colorCode[xam][yam]--;

    usedUndo = true;

}

string hint4(int colorCode[4][4]) {
    //gives hits based on the current board setting
    string hinter;
    int perRow[4] = {
        0
    }, totalRow[4] = {
        0
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (colorCode[i][j] == 1) {
                perRow[i]++;
            }
            if (colorCode[i][j] != 0)
                totalRow[i]++;
        }
        if (totalRow[i] == 4)
            continue;
        if (perRow[i] > 2) {
            hinter = "you cant have more than 2 yellow blocks in one row";
            break;
        }
        if (perRow[i] < 2) {
            hinter = "there is more space open for an extra yellow in the row ";
            hinter = hinter.append(to_string(i + 1));
            break;
        }
        if (perRow[i] == 2) {
            hinter = to_string(i + 1);
            hinter = hinter.append("  row already has 2 yellow blocks");
            break;
        }

    }
    return hinter;
}
void thegame4(sf::RenderWindow & window, int & Mousex, int & Mousey, int colorCode[4][4], bool truthTable[4][4], sf::Sound & sound, sf::Music & music, int time) {
    //checks for where the user clicked and changes its color accordingly and also forbids them from clicking on the default blocks , as well as listens to the input for any of the buttons in the game menu
    float x = 0, y = 0, defaultx = 0;

    x = 800.f;
    y = 400.f;
    defaultx = x;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
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

        if (usedUndo == false && check_Percentage4(colorCode, truthTable) != 0)
            undo4(colorCode);
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
        hinter = hint4(colorCode);

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

        ofstream saver("Game4SaveTable.txt");

        if (saver) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    saver << colorCode[i][j];
                    saver << " ";
                }
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
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

#endif // GAME4_H_INCLUDED
