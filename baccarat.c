#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

int gamestate = 0;
int money = 1000;
int bet = 100;
int endingType = 0;
float fade = 0;
int fadeDirection = 1;
bool borrowedMoney = false;
int playerCard = 0;
int dealerCard = 0;
int gameOver = 0;
int showDealer = 0;

void ResetGame();
void MainMenu();
void BorrowPopup();
void gameloop();
void EndingScreen();

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Baccarat Game");
    SetTargetFPS(60);
    
    srand(time(NULL));
    ResetGame();
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        // MAIN MENU
        if (gamestate == 0)
        {
            ClearBackground(DARKGREEN);
    
             // Title
            DrawText("Gambling Simulator", SCREEN_WIDTH/2 - MeasureText("Gambling Simulator", 60)/2, 200, 60, GOLD);
    
            // Start Button
            Rectangle startButton = { SCREEN_WIDTH/2 - 100, 400, 200, 80 };
            DrawRectangleRec(startButton, GREEN);
            DrawText("START", startButton.x + 50, startButton.y + 25, 30, BLACK);
    
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, startButton))
                {
                    ResetGame();
                    gamestate = 1;
                }
            }
        }

        else if (gamestate == 1) gameloop();
        else if (gamestate == 2) BorrowPopup();
        else if (gamestate == 3) EndingScreen();
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

// resets the game when finished
void ResetGame()
{
    playerCard = (rand() % 13) + 1;
    dealerCard = (rand() % 13) + 1;
    while (dealerCard == playerCard)
    {
        dealerCard = (rand() % 13) + 1;
    }
    gameOver = 0;
    showDealer = 0;
    bet = 100;
    borrowedMoney = false;
}

//===================== POPUP ==========================
void BorrowPopup()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.8f));
    Rectangle popup = { SCREEN_WIDTH/2 - 350, SCREEN_HEIGHT/2 - 150, 700, 300 };
    DrawRectangleRec(popup, DARKGRAY);
    DrawRectangleLinesEx(popup, 3, WHITE);
    
    DrawText("You have insufficient money for the bet.", SCREEN_WIDTH/2 - MeasureText("You have insufficient money for the bet.", 28)/2, SCREEN_HEIGHT/2 - 80, 28, WHITE);
    DrawText("Do you want to borrow money? :)", SCREEN_WIDTH/2 - MeasureText("Do you want to borrow money? :)", 28)/2, SCREEN_HEIGHT/2 - 40, 28, WHITE);
    
    Rectangle yesButton = { SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 + 50, 120, 50 };
    Rectangle noButton = { SCREEN_WIDTH/2 + 30, SCREEN_HEIGHT/2 + 50, 120, 50 };
    
    DrawRectangleRec(yesButton, GREEN);
    DrawRectangleRec(noButton, RED);
    
    DrawText("YES", yesButton.x + 35, yesButton.y + 12, 25, BLACK);
    DrawText("NO", noButton.x + 40, noButton.y + 12, 25, BLACK);
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        if (CheckCollisionPointRec(mouse, yesButton))
        {
            borrowedMoney = true;
            gamestate = 1;
        }
        else if (CheckCollisionPointRec(mouse, noButton))
        {
            gamestate = 1;
        }
    }
}

//===================== main game loop ==========================
void gameloop()
{
    ClearBackground(DARKGREEN);
    
    // Check if money is -1000 for auto ending 6
    if (money <= -1000)
    {
        endingType = 6;
        gamestate = 3;
        fade = 0;
        fadeDirection = 1;
        money = 1000;
        return;
    }
    
    // Money and Bet
    char moneyText[50];
    sprintf(moneyText, "Money: $%d", money);
    DrawText(moneyText, SCREEN_WIDTH - 300, 20, 40, YELLOW);
    
    char betText[50];
    sprintf(betText, "Bet: $%d", bet);
    DrawText(betText, SCREEN_WIDTH - 300, 70, 40, YELLOW);
    
    // Bet Buttons
    Rectangle decreaseBet = { SCREEN_WIDTH - 300, 115, 50, 50 };
    Rectangle increaseBet = { SCREEN_WIDTH - 200, 115, 50, 50 };

    DrawRectangleRec(decreaseBet, RED);
    DrawText("-", decreaseBet.x + 15, decreaseBet.y + 7, 40, WHITE);

    DrawRectangleRec(increaseBet, GREEN);
    DrawText("+", increaseBet.x + 15, increaseBet.y + 7, 40, WHITE);
    
    // Title
    DrawText("CASINO", SCREEN_WIDTH/2 - MeasureText("CASINO", 40)/2, 50, 40, GOLD);
    
    // Player Card
    int playerCardX = 300;
    DrawText("Your Card:", playerCardX - MeasureText("Your Card:", 30)/2, 200, 30, WHITE);
    DrawRectangle(playerCardX - 50, 250, 100, 150, WHITE);
    
    if (playerCard == 1) DrawText("A", playerCardX - 10, 305, 40, RED);
    else if (playerCard == 11) DrawText("J", playerCardX - 10, 305, 40, RED);
    else if (playerCard == 12) DrawText("Q", playerCardX - 10, 305, 40, RED);
    else if (playerCard == 13) DrawText("K", playerCardX - 10, 305, 40, RED);
    else if (playerCard == 10) DrawText("10", playerCardX - 20, 305, 40, RED);
    else
    {
        char cardText[3];
        sprintf(cardText, "%d", playerCard);
        DrawText(cardText, playerCardX - 10, 305, 40, RED);
    }
    
    // Dealer Card
    int dealerCardX = 900;
    DrawText("Dealer Card:", dealerCardX - MeasureText("Dealer Card:", 30)/2, 200, 30, WHITE);
    DrawRectangle(dealerCardX - 50, 250, 100, 150, WHITE);
    
    if (showDealer)
    {
        if (dealerCard == 1) DrawText("A", dealerCardX - 10, 305, 40, RED);
        else if (dealerCard == 11) DrawText("J", dealerCardX - 10, 305, 40, RED);
        else if (dealerCard == 12) DrawText("Q", dealerCardX - 10, 305, 40, RED);
        else if (dealerCard == 13) DrawText("K", dealerCardX - 10, 305, 40, RED);
        else if (dealerCard == 10) DrawText("10", dealerCardX - 20, 305, 40, RED);
        else
        {
            char cardText[3];
            sprintf(cardText, "%d", dealerCard);
            DrawText(cardText, dealerCardX - 10, 305, 40, RED);
        }
    }
    else
    {
        DrawRectangle(dealerCardX - 40, 260, 80, 130, DARKBLUE);
    }
    
    // Game buttons
    if (gameOver == 0)
    {
        Rectangle higherButton = { 400, 550, 150, 60 };
        DrawRectangleRec(higherButton, GREEN);
        DrawText("HIGHER", higherButton.x + 28, higherButton.y + 17, 25, BLACK);
        
        Rectangle lowerButton = { 650, 550, 150, 60 };
        DrawRectangleRec(lowerButton, RED);
        DrawText("LOWER", lowerButton.x + 33, lowerButton.y + 17, 25, BLACK);
    }
    else if (gameOver != 0)
    {
        if (gameOver == 1) DrawText("YOU WIN!", SCREEN_WIDTH/2 - MeasureText("YOU WIN!", 50)/2, 400, 50, YELLOW);
        else DrawText("YOU LOSE!", SCREEN_WIDTH/2 - MeasureText("YOU LOSE!", 50)/2, 400, 50, RED);
        
        Rectangle playAgainButton = { SCREEN_WIDTH/2 - 100, 550, 200, 60 };
        DrawRectangleRec(playAgainButton, YELLOW);
        DrawText("PLAY AGAIN", playAgainButton.x + 20, playAgainButton.y + 17, 25, BLACK);
    }
    
    // End Game button
    Rectangle endButton = { 20, SCREEN_HEIGHT - 70, 150, 50 };
    DrawRectangleRec(endButton, RED);
    DrawText("END GAME", endButton.x + 10, endButton.y + 12, 25, BLACK);
    
    // Mouse clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        
        // Bet buttons
        if (CheckCollisionPointRec(mouse, increaseBet))
        {
            if (borrowedMoney) bet += 50;
            else if (bet + 50 <= money) bet += 50;
            else gamestate = 2;
        }
        if (CheckCollisionPointRec(mouse, decreaseBet))
        {
            if (bet - 50 >= 50) bet -= 50;
        }
        
        // Game buttons
        if (gameOver == 0)
        {
            Rectangle higherButton = { 400, 550, 150, 60 };
            if (CheckCollisionPointRec(mouse, higherButton))
            {
                if (money >= bet || borrowedMoney)
                {
                    showDealer = 1;
                    if (dealerCard > playerCard)
                    {
                        gameOver = 1;
                        money += bet;
                    }
                    else
                    {
                        gameOver = 2;
                        money -= bet;
                    }
                }
                else gamestate = 2;
            }
            
            Rectangle lowerButton = { 650, 550, 150, 60 };
            if (CheckCollisionPointRec(mouse, lowerButton))
            {
                if (money >= bet || borrowedMoney)
                {
                    showDealer = 1;
                    if (dealerCard < playerCard)
                    {
                        gameOver = 1;
                        money += bet;
                    }
                    else
                    {
                        gameOver = 2;
                        money -= bet;
                    }
                }
                else gamestate = 2;
            }
        }
        else if (gameOver != 0)
        {
            Rectangle playAgainButton = { SCREEN_WIDTH/2 - 100, 550, 200, 60 };
            if (CheckCollisionPointRec(mouse, playAgainButton))
            {
                ResetGame();
            }
        }
        
        // End Game button
        if (CheckCollisionPointRec(mouse, endButton))
        {
            if (money > 1000) endingType = 5;
            else if (money == 1000) endingType = 1;
            else if (money < 1000 && money > 0) endingType = 4;
            else if (money == 0) endingType = 2;
            else if (money < 0) endingType = 3;
            
            money = 1000;
            gamestate = 3;
            fade = 0;
            fadeDirection = 1;
        }
    }
}

void EndingScreen()
{
    if (fadeDirection == 1)
    {
        fade += 0.01f;
        if (fade >= 1.0f)
        {
            fade = 1.0f;
            fadeDirection = 0;
        }
    }
    else
    {
        fade -= 0.01f;
        if (fade <= 0.0f)
        {
            gamestate = 0;
            return;
        }
    }
    
    ClearBackground(BLACK);
    
    char endingText[100];
    if (endingType == 1) sprintf(endingText, "GREAT ENDING: You didn't gamble");
    else if (endingType == 2) sprintf(endingText, "BROKE ENDING: You're now broke");
    else if (endingType == 3) sprintf(endingText, "DEBT ENDING: You're now bankrupt");
    else if (endingType == 4) sprintf(endingText, "LOSING ENDING: You lost money");
    else if (endingType == 5) sprintf(endingText, "EARNING ENDING: You earned more money");
    else if (endingType == 6) sprintf(endingText, "DEAD ENDING: You died due to debts");
    
    DrawText(endingText, SCREEN_WIDTH/2 - MeasureText(endingText, 40)/2, SCREEN_HEIGHT/2 - 20, 40, Fade(WHITE, fade));
}
