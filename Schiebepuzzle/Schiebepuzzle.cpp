#include <iostream>
#include <ctime>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

int nScreenWidth = 80;
int nScreenHeight = 30;

int main()
{
    void PrintBoard(char[4][4]);
    void InitializeBoard(char[4][4]);
    void LocateSpace(int&, int&, char[4][4]);
    int KeyCounter = 0;
    int nRekord = 0;
    int nRekordOld = 0;
    int nScoreOld = 0;

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    std::string line;
    std::ifstream myfile("Schiebepuzzle.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::stringstream geek(line);
            int line = 0;
            geek >> line;

            nRekordOld = line;
        }
        myfile.close();
    }

    do {

        wsprintf(&screen[ 7 * nScreenWidth + 20], L"PPPPPPPP   UU        UU   ZZZZZZZZZZZ   ZZZZZZZZZZZ   LL            EEEEEEEEEEE");
        wsprintf(&screen[ 8 * nScreenWidth + 20], L"PPPPPPPP   UU        UU   ZZZZZZZZZZZ   ZZZZZZZZZZZ   LL            EEEEEEEEEEE");
        wsprintf(&screen[ 9 * nScreenWidth + 20], L"PP    PP   UU        UU           ZZZ           ZZZ   LL            EE         ");
        wsprintf(&screen[10 * nScreenWidth + 20], L"PP    PP   UU        UU          ZZZ           ZZZ    LL            EE         ");
        wsprintf(&screen[11 * nScreenWidth + 20], L"PP    PP   UU        UU         ZZZ           ZZZ     LL            EE         ");
        wsprintf(&screen[12 * nScreenWidth + 20], L"PPPPPPPP   UU        UU        ZZZ           ZZZ      LL            EEEEEEEEEEE");
        wsprintf(&screen[13 * nScreenWidth + 20], L"PPPPPPPP   UU        UU       ZZZ           ZZZ       LL            EEEEEEEEEEE");
        wsprintf(&screen[14 * nScreenWidth + 20], L"PP         UU        UU      ZZZ           ZZZ        LL            EE         ");
        wsprintf(&screen[15 * nScreenWidth + 20], L"PP         UU        UU     ZZZ           ZZZ         LL            EE         ");
        wsprintf(&screen[16 * nScreenWidth + 20], L"PP         UU        UU    ZZZ           ZZZ          LL            EE         ");
        wsprintf(&screen[17 * nScreenWidth + 20], L"PP         UU       UUU   ZZZ           ZZZ           LL            EE         ");
        wsprintf(&screen[18 * nScreenWidth + 20], L"PP          UUUUUUUU UU   ZZZZZZZZZZZ   ZZZZZZZZZZZ   LLLLLLLLLLL   EEEEEEEEEEE");
        wsprintf(&screen[19 * nScreenWidth + 20], L"PP           UUUUUU  UU   ZZZZZZZZZZZ   ZZZZZZZZZZZ   LLLLLLLLLLL   EEEEEEEEEEE");

        wsprintf(&screen[21 * nScreenWidth + 55], L"by Alex");

        wsprintf(&screen[23 * nScreenWidth + 48], L"PRESS   'SPACE' TO PLAY");

        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

    } while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);

    while (1)
    {       
        char caaBoard[4][4];
        InitializeBoard(caaBoard);

        bool bKeyExit = false;
        bool GameOver = false;

        bool bKeyUp = false, bKeyDown = false, bKeyRight = false, bKeyLeft = false;
        
        int nScore = 0;

        while (!GameOver)
        {
            nScoreOld = nScore;
            if (nScore < nRekordOld)
            {
                nRekordOld = nScore;
                nRekord = nScore;
                if (line < std::to_string(nRekord))
                {
                    std::ofstream myfile("Schiebepuzzle.txt");
                    if (myfile.is_open())
                    {
                        myfile << nRekord;
                        myfile.close();
                    }
                }
            }
            else
            {
                nRekord = nRekordOld;
            }
            
            do {

                system("CLS");
                PrintBoard(caaBoard);

                int iRowSpace;
                int iColSpace;
                LocateSpace(iRowSpace, iColSpace, caaBoard);
                int iRowMove(iRowSpace);
                int iColMove(iColSpace);

                std::cout << std::endl;
                std::cout << "Use Arrow-Keys to move" << std::endl;
                std::cout << " " << std::endl;
                std::cout << "Zuege: ";
                std::cout << ("%d", KeyCounter) << std::endl;

                bKeyExit = (0x8000 & GetAsyncKeyState((unsigned char)('\x4C'))) != 0;
                bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('\x26'))) != 0;
                bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('\x28'))) != 0;
                bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
                bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;

                if (bKeyUp)
                {
                    iRowMove = iRowSpace + 1;
                    KeyCounter++;
                }

                if (bKeyDown)
                {
                    iRowMove = iRowSpace - 1;
                    KeyCounter++;
                }

                if (bKeyLeft)
                {
                    iColMove = iColSpace + 1;
                    KeyCounter++;
                }

                if (bKeyRight)
                {
                    iColMove = iColSpace - 1;
                    KeyCounter++;
                }

                if (bKeyExit)
                {
                    return EXIT_SUCCESS;
                }

                if (iRowMove >= 0 && iRowMove < 4 && iColMove >= 0 && iColMove < 4) {
                    caaBoard[iRowSpace][iColSpace] = caaBoard[iRowMove][iColMove];
                    caaBoard[iRowMove][iColMove] = ' ';
                }

            } while (bKeyUp || bKeyDown || bKeyRight || bKeyLeft);
            
            

            if (GameOver)
            {
                std::cout << "GAME OVER" << std::endl;
                wsprintf(&screen[12 * nScreenWidth + 40], L"     Score:%d", nScore);
                wsprintf(&screen[13 * nScreenWidth + 40], L"     Rekord:%d", nRekord);
                wsprintf(&screen[15 * nScreenWidth + 35], L"PRESS    'SPACE' TO PLAY AGAIN");
                wsprintf(&screen[17 * nScreenWidth + 35], L"PRESS    'X' TO EXIT");                           
            }
        }
    }
    return EXIT_SUCCESS;
}

void InitializeBoard(char caaBoard[4][4])
{
    const char kcaaInitial[4][4] = {
                 {'2', '3', '5', ' '},
                 {'9', '6', 'F', '8'},
                 {'A', 'C', '1', '4'},
                 {'D', '7', 'E', 'B'}
    };
    for (int iRow = 0; iRow < 4; ++iRow) {
        for (int iCol = 0; iCol < 4; ++iCol) {
            caaBoard[iRow][iCol] = kcaaInitial[iRow][iCol];
        }
    }
}

void LocateSpace(int& irRow, int& irCol, char caaBoard[4][4]) {
    for (int iRow = 0; iRow < 4; ++iRow) {
        for (int iCol = 0; iCol < 4; ++iCol) {
            if (caaBoard[iRow][iCol] == ' ') {
                irRow = iRow;
                irCol = iCol;
            }
        }
    }
}

void PrintBoard(char caaBoard[4][4]) {
    for (int iRow = 0; iRow < 4; ++iRow) {
        for (int iCol = 0; iCol < 4; ++iCol) {
            std::cout << caaBoard[iRow][iCol];
        }
        std::cout << std::endl;
    }
}