#include <iostream>
using namespace std;
#include "iGraphics.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

int x = 0, y = 0, r = 20;

int turn = 1;
int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;
int b5 = 0;
int b6 = 0;
int b7 = 0;
int b8 = 0;
int b9 = 0;
int win = 0;
int res = 0;
int IndexNumber = 0;
int page;
int m;
int winner;
int qn;
int qidx;
int ans;
int score = 0;
int fscore = 0;
int bgin = 0;
int newg = 0;
int mode = 0;
int len;
int rps = 0;
int rpswin;
int gamestate = -2;
int ttt = 0;

bool musicOn = true;
bool hover = true;
bool homepage = true;
bool rstate = true;

int cntc = 0;
int cntg = 0;
int roundCount = 0;
int TotalRound3 = 3;
int TotalRound5 = 5;
int TotalRound9 = 9;
int input;

char question[20][20] = {"image\\q1.bmp", "image\\q2.bmp", "image\\q3.bmp", "image\\q4.bmp", "image\\q5.bmp",
                         "image\\q6.bmp", "image\\q7.bmp", "image\\q8.bmp", "image\\q9.bmp", "image\\q10.bmp",
                         "image\\q11.bmp", "image\\q12.bmp", "image\\q13.bmp", "image\\q14.bmp", "image\\q15.bmp",
                         "image\\q16.bmp", "image\\q17.bmp", "image\\q18.bmp", "image\\q19.bmp", "image\\q20.bmp"};

char bg[4][20] = {"image\\start.bmp", "image\\bg2.bmp"};
char tutorial[] = {"image\\tutorial.bmp"};
char about[] = {"image\\about.bmp"};
char triviat[] = {"image\\triviat.bmp"};
char triviabg[] = {"image\\triviabg.bmp"};
char button[4][20] = {"image\\button4.bmp", "image\\button3.bmp", "image\\trivia.bmp", "image\\ttt.bmp"};
char harryright[5][20] = {"image\\front.bmp", "image\\r1.bmp", "image\\r2.bmp", "image\\r3.bmp", "image\\r4.bmp"};
char harryleft[5][20] = {"image\\front.bmp", "image\\l1.bmp", "image\\l2.bmp", "image\\l3.bmp", "image\\l4.bmp"};
char str[1000] = "Score: ";
char SCORES[100][100];
char playername[50];
char cpyplayername[50];
char numbers[10];
char computerChoice;
char playerChoice;
char gamer;

// char music[1][20]={"music\\Lumos.wav"};
/*
    function iDraw() is called again and again by the system.

    */
struct buttonCoordinate
{
    int x;
    int y;
} bCoordinate[4];

void drawXO();
void result();
void refresh();
void scoreboardsave(char cpy[50], char number[10]);
void variableref();
void displayScores();
void startNewRound();
void drawRPS(char gamer, char comp);
void resetRPS();

char RPScomputer();

int RPSres(char gamer, char comp);

void scoreboardsave(char cpy[50], char number[10])
{
    FILE *fptr;
    fptr = fopen("scoreboard/scores.txt", "a");
    strcat(cpy, " : ");
    strcat(cpy, number);
    fprintf(fptr, "%s,", cpy);
    fclose(fptr);
}

void variableref()
{
    playername[0] = 0;
    cpyplayername[0] = 0;
    numbers[0] = 0;
    IndexNumber = 0;
    score = 0;
}

void displayScores()
{
    FILE *fptr;
    char line[1024];
    int yPosition = 400;

    // Open the file for reading
    fptr = fopen("scoreboard/scores.txt", "r");
    if (!fptr)
    {
        printf("Failed to open the file.\n");
        return;
    }

    if (fgets(line, sizeof(line), fptr) != NULL)
    {
        fclose(fptr);

        char *token = strtok(line, ",");
        while (token != NULL)
        {
            iSetColor(0, 0, 0);
            iText(240, yPosition, token, GLUT_BITMAP_HELVETICA_18);
            token = strtok(NULL, ",");
            yPosition -= 30;
            if (yPosition < 80)
                break; // Avoid writing beyond the screen
        }
    }
    else
    {
        fclose(fptr);
    }
}

char RPScomputer()
{
    char choices[3] = {'r', 'p', 's'};
    int n = rand() % 3;
    return choices[n]; // Return computer's choice
}

void startNewRound()
{
    if (rps == 2)
    {
        if (roundCount < TotalRound3)
        {
            computerChoice = RPScomputer(); // Get computer's choice
            roundCount++;
        }
        else
        {
            rps = 5; // Game over, proceed to display the winner
        }
    }
    else if (rps == 3)
    {
        if (roundCount < TotalRound5)
        {
            computerChoice = RPScomputer(); // Get computer's choice
            roundCount++;
        }
        else
        {
            rps = 5; // Game over, proceed to display the winner
        }
    }
    if (rps == 4)
    {
        if (roundCount < TotalRound9)
        {
            computerChoice = RPScomputer(); // Get computer's choice
            roundCount++;
        }
        else
        {
            rps = 5; // Game over, proceed to display the winner
        }
    }
}

int RPSres(char gamer, char comp)
{
    if ((gamer == 'r' && comp == 's') || (gamer == 's' && comp == 'p') || (gamer == 'p' && comp == 'r'))
    {
        return 2; // Gamer wins
    }
    else if (gamer == comp)
    {
        return 0; // Tie
    }
    else
    {
        return 1; // Computer wins
    }
}

void drawRPS(char gamer, char comp)
{
    switch (gamer)
    {
    case 'r':
        iShowBMP2(40, 100, "image\\rock.bmp", 0);
        break;
    case 'p':
        iShowBMP2(40, 100, "image\\paper.bmp", 0);
        break;
    case 's':
        iShowBMP2(40, 100, "image\\scissor.bmp", 0);
        break;
    }

    switch (comp)
    {
    case 'r':
        iShowBMP2(420, 100, "image\\rock.bmp", 0);
        break;
    case 'p':
        iShowBMP2(420, 100, "image\\paper.bmp", 0);
        break;
    case 's':
        iShowBMP2(420, 100, "image\\scissor.bmp", 0);
        break;
    }
}

// Function to reset the game to initial state
void resetRPS()
{
    playerChoice = 0;
    computerChoice = 0;
    cntc = 0;
    cntg = 0;
    roundCount = 0;
}

void iDraw()
{
    // place your drawing codes here
    iClear();

    if (gamestate == -2)
    {
        iShowBMP(0, 0, bg[0]);
        iSetColor(245, 245, 245);
        iText(400, 20, "Press c to continue...", GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == -1 && homepage == true)
    {
        iShowBMP(0, 0, bg[1]);
        // for (int i = 0; i < 4; i++)
        // {
        //     iShowBMP2(bCoordinate[i].x, bCoordinate[i].y, button[i], 0);
        // }
    }

    else if (gamestate == 0)
    {
        iShowBMP(0, 0, about);
        iSetColor(173, 93, 23);
        iText(400, 20, "Press c to go back to Main Menu", GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 1)
    {
        iShowBMP(0, 0, "image\\rps1.bmp");
    }

    else if (gamestate == 2)
    {
        iShowBMP(0, 0, triviat);
        iSetColor(173, 93, 23);
        iText(400, 20, "Press c to go back to Main Menu", GLUT_BITMAP_HELVETICA_12);
        iText(20, 20, "Press Insert to start the game", GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == -3)
    {
        iShowBMP(0, 0, "image\\tutorial.bmp");
    }

    else if (gamestate == 3)
    {
        win = 0;
        iShowBMP(0, 0, triviabg);

        iSetColor(255, 255, 255);
        iLine(250, 150, 250, 450);
        iLine(250 + 1, 150, 250 + 1, 450);
        iLine(250 - 1, 150, 250 - 1, 450);

        iLine(150, 250, 450, 250);
        iLine(150, 250 + 1, 450, 250 + 1);
        iLine(150, 250 - 1, 450, 250 - 1);

        iLine(150, 350, 450, 350);
        iLine(150, 350 + 1, 450, 350 + 1);
        iLine(150, 350 - 1, 450, 350 - 1);

        iLine(350, 150, 350, 450);
        iLine(350 + 1, 150, 350 + 1, 450);
        iLine(350 - 1, 150, 350 - 1, 450);

        drawXO();
    }

    if (gamestate == 4)
    {
        result();
        // iSetColor(255, 255, 255);
        // iText(400, 20, "Press c to go back to Main Menu", GLUT_BITMAP_HELVETICA_12);
        // refresh();
    }

    if (newg == 1)
    {
        // printf("works");
        iShowBMP(0, 0, "image\\input.bmp");
        iSetColor(0, 0, 0);
        iText(150, 270, playername, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    if (gamestate == 5)
    {
        iShowBMP(0, 0, question[0]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    if (gamestate == 6)
    {
        iShowBMP(0, 0, question[1]);
        iSetColor(60, 60, 60);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iSetColor(0, 0, 0);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 7)
    {
        iShowBMP(0, 0, question[2]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 8)
    {
        iShowBMP(0, 0, question[3]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 9)
    {
        iShowBMP(0, 0, question[4]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 10)
    {
        iShowBMP(0, 0, question[5]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 11)
    {
        iShowBMP(0, 0, question[6]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 12)
    {
        iShowBMP(0, 0, question[7]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 13)
    {
        iShowBMP(0, 0, question[8]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 14)
    {
        iShowBMP(0, 0, question[9]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 15)
    {
        iShowBMP(0, 0, question[10]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 16)
    {
        iShowBMP(0, 0, question[11]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 17)
    {
        iShowBMP(0, 0, question[12]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 18)
    {
        iShowBMP(0, 0, question[13]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 19)
    {
        iShowBMP(0, 0, question[14]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 20)
    {
        iShowBMP(0, 0, question[15]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 21)
    {
        iShowBMP(0, 0, question[16]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 22)
    {
        iShowBMP(0, 0, question[17]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 23)
    {
        iShowBMP(0, 0, question[18]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 24)
    {
        iShowBMP(0, 0, question[19]);
        iText(10, 50, "Press A or B for the correct answer", GLUT_BITMAP_TIMES_ROMAN_24);
        char str[1000] = "Score: ";
        sprintf(str, "%s%d", str, score);
        iText(500, 550, str, GLUT_BITMAP_HELVETICA_12);
    }

    else if (gamestate == 25)
    {
        iShowBMP(0, 0, "image\\result.bmp");
        char str1[1000] = "Score: ";
        sprintf(str1, "%s%d", str1, fscore);
        iText(250, 350, str1, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    else if (gamestate == 26)
    {
        iShowBMP(0, 0, "image\\highscore.bmp");
        displayScores();
        variableref();
        iText(300, 75, "Press c to go back to main menu");
    }

    else if (rps == 1)
    {
        iShowBMP(0, 0, "image\\round.bmp");
    }

    else if (rps == 2)
    {
        // resetRPS();
        iShowBMP(0, 0, "image\\rpsgame.bmp");
        if (playerChoice != 0)
        {
            drawRPS(playerChoice, computerChoice);
        }
    }

    else if (rps == 3)
    {
        iShowBMP(0, 0, "image\\rpsgame.bmp");
        if (playerChoice != 0)
        {
            drawRPS(playerChoice, computerChoice);
        }
    }

    else if (rps == 4)
    {
        iShowBMP(0, 0, "image\\rpsgame.bmp");
        if (playerChoice != 0)
        {
            drawRPS(playerChoice, computerChoice);
        }
    }

    else if (rps == 5)
    {
        // printf("%d %d", cntg, cntc);
        //  if (cntg > cntc)
        //  {
        //      iShowBMP(0, 0, "image\\prps.bmp");
        //  }
        //  else if (cntg < cntc)
        //  {
        //      iShowBMP(0, 0, "image\\airps.bmp");
        //  }
        //  else if(cnt==cntc)
        //  {
        //      iShowBMP(0, 0, "image\\drps.bmp");
        //  }
        iSetColor(0, 0, 0);
        if (rpswin == 2)
        {
            iShowBMP(0, 0, "image\\prps.bmp");
        }

        else if (rpswin == 1)
        {
            iShowBMP(0, 0, "image\\airps.bmp");
        }

        else if (rpswin == 3)
        {
            iShowBMP(0, 0, "image\\drps.bmp");
        }

        resetRPS();
    }
}

void drawXO()
{
    if (win == 0)
    {
        if (b1 == 1)
        {
            iShowBMP2(150, 350, "image\\cross.bmp", 0);
        }
        if (b1 == 2)
        {
            iShowBMP2(150, 350, "image\\circle.bmp", 0);
        }
        if (b2 == 1)
        {
            iShowBMP2(250, 350, "image\\cross.bmp", 0);
        }
        if (b2 == 2)
        {
            iShowBMP2(250, 350, "image\\circle.bmp", 0);
        }
        if (b3 == 1)
        {
            iShowBMP2(350, 350, "image\\cross.bmp", 0);
        }
        if (b3 == 2)
        {
            iShowBMP2(350, 350, "image\\circle.bmp", 0);
        }
        if (b4 == 1)
        {
            iShowBMP2(150, 250, "image\\cross.bmp", 0);
        }
        if (b4 == 2)
        {
            iShowBMP2(150, 250, "image\\circle.bmp", 0);
        }
        if (b5 == 1)
        {
            iShowBMP2(250, 250, "image\\cross.bmp", 0);
        }
        if (b5 == 2)
        {
            iShowBMP2(250, 250, "image\\circle.bmp", 0);
        }
        if (b6 == 1)
        {
            iShowBMP2(350, 250, "image\\cross.bmp", 0);
        }
        if (b6 == 2)
        {
            iShowBMP2(350, 250, "image\\circle.bmp", 0);
        }
        if (b7 == 1)
        {
            iShowBMP2(150, 150, "image\\cross.bmp", 0);
        }
        if (b7 == 2)
        {
            iShowBMP2(150, 150, "image\\circle.bmp", 0);
        }
        if (b8 == 1)
        {
            iShowBMP2(250, 150, "image\\cross.bmp", 0);
        }
        if (b8 == 2)
        {
            iShowBMP2(250, 150, "image\\circle.bmp", 0);
        }
        if (b9 == 1)
        {
            iShowBMP2(350, 150, "image\\cross.bmp", 0);
        }
        if (b9 == 2)
        {
            iShowBMP2(350, 150, "image\\circle.bmp", 0);
        }
    }
}

void result()
{
    if (win == 1)
    {
        iShowBMP(0, 0, "image\\harrywin.bmp");
    }

    else if (win == 2)
    {
        iShowBMP(0, 0, "image\\ronwin.bmp");
    }

    else if (win == 3)
    {
        iShowBMP(0, 0, "image\\draw.bmp");
    }
}

void refresh()
{
    turn = 1;
    b1 = 0;
    b2 = 0;
    b3 = 0;
    b4 = 0;
    b5 = 0;
    b6 = 0;
    b7 = 0;
    b8 = 0;
    b9 = 0;
}
/*
    function iMouseMove() is called when the user presses and drags the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
    // place your codes here
}

/*
    function iMouse() is called when the user presses/releases the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if ((mx >= 145 && mx <= 450 && my >= 470 && my <= 535) && gamestate == -1)
        {
            gamestate = -3;
        }
        if ((mx >= 145 && mx <= 450 && my >= 370 && my <= 435) && gamestate == -1)
        {
            gamestate = 2;
        }
        if ((mx >= 145 && mx <= 450 && my >= 270 && my <= 335) && gamestate == -1)
        {
            gamestate = 1;
        }
        if ((mx >= 145 && mx <= 450 && my >= 170 && my <= 235) && gamestate == -1)
        {
            gamestate = 0;
        }
        if ((mx >= 530 && mx <= 580 && my >= 25 && my <= 70) && gamestate == 1)
        {
            // printf("hoise");
            rps = 1;
            rstate = true;
            // printf("%d", rps);
        }
        if ((mx >= 30 && mx <= 190 && my >= 190 && my <= 340) && rps == 1 && rstate == true)
        {
            rstate = false;
            rps = 2;
            // printf("%d", rps);
        }
        if ((mx >= 215 && mx <= 370 && my >= 190 && my <= 340) && rps == 1 && rstate == true)
        {
            rstate = false;
            rps = 3;
        }
        if ((mx >= 415 && mx <= 590 && my >= 190 && my <= 340) && rps == 1 && rstate == true)
        {
            rstate = false;
            rps = 4;
        }

        // if((mx >= 525 && mx <= 580 && my >= 65 && my <= 115) && rps==5)
        // {
        //     homepage=true;
        //     gamestate=-1;
        // }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && gamestate == 4)
    {
        gamestate = -1;
        homepage = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && (mx >= 535 && mx <= 580 && my >= 25 && my <= 75) && gamestate == -3)
    {
        // printf("%d %d", gamestate, ttt);
        gamestate = 3;
        // printf("\n%d %d", gamestate, ttt);
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && win == 0)
    {
        // place your codes here

        if (mx >= 150 && mx <= 250 && my >= 350 && my <= 450) // b1
        {
            if (b1 == 0 && turn == 1)
            {
                turn = 2;
                b1 = 1;
                if ((b1 == 1 && b4 == 1 && b7 == 1) || (b1 == 1 && b5 == 1 && b9 == 1) || (b1 == 1 && b2 == 1 && b3 == 1))
                {
                    win = 1;
                }
            }
            else if (b1 == 0 && turn == 2)
            {
                turn = 1;
                b1 = 2;
                if ((b1 == 2 && b4 == 2 && b7 == 2) || (b1 == 2 && b5 == 2 && b9 == 2) || (b1 == 2 && b2 == 2 && b3 == 2))
                {
                    win = 2;
                }
            }
            else
                win = 3;
        }

        if (mx >= 250 && mx <= 350 && my >= 350 && my <= 450) // b2
        {
            if (b2 == 0 && turn == 1)
            {
                turn = 2;
                b2 = 1;
                if ((b2 == 1 && b1 == 1 && b3 == 1) || (b2 == 1 && b5 == 1 && b8 == 1))
                {
                    win = 1;
                }
            }
            else if (b2 == 0 && turn == 2)
            {
                turn = 1;
                b2 = 2;
                if ((b2 == 2 && b1 == 2 && b3 == 2) || (b2 == 2 && b5 == 2 && b8 == 2))
                {
                    win = 2;
                }
            }
            else
                win = 3;
        }

        if (mx >= 350 && mx <= 450 && my >= 350 && my <= 450) // b3
        {
            if (b3 == 0 && turn == 1)
            {
                turn = 2;
                b3 = 1;
                if ((b3 == 1 && b6 == 1 && b9 == 1) || (b3 == 1 && b5 == 1 && b7 == 1) || (b1 == 1 && b2 == 1 && b3 == 1))
                {
                    win = 1;
                }
            }
            else if (b3 == 0 && turn == 2)
            {
                turn = 1;
                b3 = 2;
                if ((b3 == 2 && b6 == 2 && b9 == 2) || (b3 == 2 && b5 == 2 && b7 == 2) || (b1 == 2 && b2 == 2 && b3 == 2))
                {
                    win = 2;
                }
            }
            else
                win = 3;
        }

        if (mx >= 150 && mx <= 250 && my >= 250 && my <= 350) // b4
        {
            if (b4 == 0 && turn == 1)
            {
                turn = 2;
                b4 = 1;
                if ((b1 == 1 && b4 == 1 && b7 == 1) || (b4 == 1 && b5 == 1 && b6 == 1))
                {
                    win = 1;
                }
            }
            else if (b4 == 0 && turn == 2)
            {
                turn = 1;
                b4 = 2;
                if ((b1 == 2 && b4 == 2 && b7 == 2) || (b4 == 2 && b5 == 2 && b6 == 2))
                {
                    win = 2;
                }
            }
            else
                win = 3;
        }

        if (mx >= 250 && mx <= 350 && my >= 250 && my <= 350) // b5
        {
            if (b5 == 0 && turn == 1)
            {
                turn = 2;
                b5 = 1;
                if ((b2 == 1 && b5 == 1 && b8 == 1) || (b1 == 1 && b5 == 1 && b9 == 1) || (b3 == 1 && b5 == 1 && b7 == 1) || (b4 == 1 && b5 == 1 && b6 == 1))
                {
                    win = 1;
                }
            }
            else if (b5 == 0 && turn == 2)
            {
                turn = 1;
                b5 = 2;
                if ((b2 == 2 && b5 == 2 && b8 == 2) || (b1 == 2 && b5 == 2 && b9 == 2) || (b3 == 2 && b5 == 2 && b7 == 2) || (b4 == 2 && b5 == 2 && b6 == 2))
                {
                    win = 2;
                }
            }
            else
                win = 3;
        }

        if (mx >= 350 && mx <= 450 && my >= 250 && my <= 350) // b6
        {
            if (b6 == 0 && turn == 1)
            {
                turn = 2;
                b6 = 1;
                if ((b3 == 1 && b6 == 1 && b9 == 1) || (b4 == 1 && b5 == 1 && b6 == 1))
                {
                    win = 1;
                }
            }
            else if (b6 == 0 && turn == 2)
            {
                turn = 1;
                b6 = 2;
                if ((b3 == 2 && b6 == 2 && b9 == 2) || (b4 == 2 && b5 == 2 && b6 == 2))
                {
                    win = 2;
                }
            }
            else
                win = 3;
        }

        if (mx >= 150 && mx <= 250 && my >= 150 && my <= 250) // b7
        {
            if (b7 == 0 && turn == 1)
            {
                turn = 2;
                b7 = 1;
                if ((b1 == 1 && b4 == 1 && b7 == 1) || (b3 == 1 && b5 == 1 && b7 == 1) || (b7 == 1 && b8 == 1 && b9 == 1))
                {
                    win = 1;
                }
            }
            else if (b7 == 0 && turn == 2)
            {
                turn = 1;
                b7 = 2;
                if ((b1 == 2 && b4 == 2 && b7 == 2) || (b3 == 2 && b5 == 2 && b7 == 2) || (b7 == 2 && b8 == 2 && b9 == 2))
                {
                    win = 2;
                }
            }
            else
                win = 3;
        }

        if (mx >= 250 && mx <= 350 && my >= 150 && my <= 250) // b8
        {
            if (b8 == 0 && turn == 1)
            {
                turn = 2;
                b8 = 1;
                if ((b7 == 1 && b8 == 1 && b9 == 1) || (b2 == 1 && b5 == 1 && b8 == 1))
                {
                    win = 1;
                }
            }
            else if (b8 == 0 && turn == 2)
            {
                turn = 1;
                b8 = 2;
                if ((b7 == 2 && b8 == 2 && b9 == 2) || (b2 == 2 && b5 == 2 && b8 == 2))
                {
                    win = 2;
                }
            }
        }

        if (mx >= 350 && mx <= 450 && my >= 150 && my <= 250) // b9
        {
            if (b9 == 0 && turn == 1)
            {
                turn = 2;
                b9 = 1;
                if ((b1 == 1 && b5 == 1 && b9 == 1) || (b7 == 1 && b8 == 1 && b9 == 1) || (b3 == 1 && b6 == 1 && b9 == 1))
                {
                    win = 1;
                }
            }
            else if (b9 == 0 && turn == 2)
            {
                turn = 1;
                b9 = 2;
                if ((b1 == 2 && b5 == 2 && b9 == 2) || (b7 == 2 && b8 == 2 && b9 == 2) || (b3 == 2 && b6 == 2 && b9 == 2))
                {
                    win = 2;
                }
            }
        }

        if (b1 != 0 && b2 != 0 && b3 != 0 && b4 != 0 && b5 != 0 && b6 != 0 && b7 != 0 && b8 != 0 && b9 != 0 && win == 0)
            win = 3;

        if (win == 1 || win == 2 || win == 3)
        {
            gamestate = 4;
            refresh();
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if ((mx >= bCoordinate[i].x && mx <= bCoordinate[i].x + 150 && my >= bCoordinate[i].y && my <= bCoordinate[i].y + 100) && homepage == true)
        {
            homepage = false;
            gamestate = i;
            // if(hover||musicOn)
            // PlaySound("music\\bhovering.wav", NULL, SND_ASYNC);
        }
    }

    // if ((mx >= 525 && mx <= 580 && my >= 60 && my <= 120) && rps == 5 && homepage==false)
    // {
    //     printf("\n%d %d\n", rps, gamestate);
    //     homepage=true;
    //     gamestate=-1;
    //     printf("\n%d %d\n", rps, gamestate);
    // }

    if ((mx >= 523 && mx <= 553 && my >= 77 && my <= 115) && newg == 1)
    {
        strcpy(cpyplayername, playername);
        gamestate = 5;
        newg = 0;
    }

    if ((mx >= 70 && mx <= 545 && my >= 130 && my <= 235) && gamestate == 25)
    {
        gamestate = 26;
    }
}

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
    */

void iKeyboard(unsigned char key)
{
    // printf("Before condition: rps = %d, gamestate = %d\n", rps, gamestate);
    if ((key == 'c' || key == 'C') && (rps == 5 || gamestate == 2 || gamestate == 4 || gamestate == 26 || gamestate == 0 || gamestate == -2 || gamestate == 1 || gamestate == 3 || gamestate == 25))
    {
        // printf("Inside condition\n");
        if (rps == 5)
        {
            rps = 0;
        }
        gamestate = -1;
        homepage = true;
    }
    // printf("After condition: rps = %d, gamestate = %d\n", rps, gamestate);

    if (newg == 1)
    {
        if (key != '\b')
        {
            playername[IndexNumber] = key;
            IndexNumber++;
            playername[IndexNumber] = '\0';
        }
        else
        {
            if (IndexNumber <= 0)
                IndexNumber = 0;
            else
                IndexNumber--;
            playername[IndexNumber] = '\0';
        }
    }
    // if (key == '1' && newg == 1)
    // {
    //     strcpy(cpyplayername, playername);
    //     gamestate = 5;
    //     newg = 0;
    // }
    if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 5)
    {
        score = 0;
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate = 6;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 6)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 7)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 8)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 9)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 10)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 11)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 12)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 13)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 14)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 15)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 16)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 17)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 18)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 19)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 20)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 21)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 22)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 23)
    {
        if (key == 'a' || key == 'A')
            score -= 10;
        else if (key == 'b' || key == 'B')
            score += 10;

        // printf("%d %d\n",score,fscore);
        // fscore=score;
        gamestate++;
    }

    else if ((key == 'A' || key == 'B' || key == 'a' || key == 'b') && gamestate == 24)
    {
        if (key == 'a' || key == 'A')
            score += 10;
        else if (key == 'b' || key == 'B')
            score -= 10;

        // fscore = score;
        //  printf("%d %d",score,fscore);
        gamestate++;
    }

    // fscore = score;
    int i = 0;
    if (gamestate == 25)
    {
        fscore = score;
        // printf("%d %d\n", score, fscore);
        sprintf(numbers, "%d", score);
        if (i == 0)
        {
            scoreboardsave(cpyplayername, numbers);
            i = 1;
        }
    }

    if (rps == 2 || rps == 3 || rps == 4)
    {
        if (key == 's' || key == 'p' || key == 'r')
        {
            playerChoice = key; // Set player choice based on key press
            startNewRound();
            // Determine the result of the round
            int result = RPSres(playerChoice, computerChoice);
            if (result == 2)
            {
                cntg++; // Increment player score
            }
            else if (result == 1)
            {
                cntc++; // Increment computer score
            }
        }
        else if (key == 'q')
        {               // Press 'q' to quit or reset the game
            resetRPS(); // Reset game state
        }
        if (cntc > cntg)
            rpswin = 1;
        else if (cntc == cntg)
            rpswin = 3;
        else
            rpswin = 2;
    }

    // place your codes for other keys here
}

/*
    function iSpecialKeyboard() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
    */
void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_F10)
    {
        if (musicOn)
        {
            musicOn = false;
            PlaySound(0, 0, 0);
        }
        else
        {
            musicOn = true;
            PlaySound("music\\Lumos.wav", NULL, SND_LOOP | SND_ASYNC);
        }
    }

    if (key == GLUT_KEY_INSERT)
    {
        newg = 1;
    }

    // place your codes for other keys here
}

int main()
{
    // place your own initialization codes here.
    srand((unsigned int)time(NULL));
    if (musicOn)
    {
        PlaySound("music\\Lumos.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    int sum = 150;
    // for (int i = 0; i < 4; i++)
    // {
    //     bCoordinate[i].x = 60;
    //     bCoordinate[i].y = sum;
    //     sum += 110;
    // }

    iInitialize(600, 600, "MINI-HOGWARTS");
    return 0;
}