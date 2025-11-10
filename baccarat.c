#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void) 
{
    InitWindow(800, 600, "Testing Testing");
    SetTargetFPS(60);
    
    // variables
    int playerCard = 0;
    int dealerCard = 0;
    int gameState = 0;
    bool showDealerCard = false;
    int playerTextX = 200;
    int dealerTextX = 600;
    int cardY = 250;
    int textY = 150;
    int money = 1000;
    int bet = 100;
    
    Rectangle higherButton = { 250, 500, 100, 50 };
    Rectangle lowerButton = { 450, 500, 100, 50 };
    Rectangle playAgainButton = { 350, 500, 100, 50 };
    
    // Make random cards
    srand(time(NULL));
    playerCard = (rand() % 13) + 1;
    dealerCard = (rand() % 13) + 1;
    
    while (dealerCard == playerCard) {
        dealerCard = (rand() % 13) + 1;
    }
    
    while (!WindowShouldClose()) 
    {
        Vector2 mouse = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Higher or Lower Button
        {
            if (gameState == 0) 
            {
                if (CheckCollisionPointRec(mouse, higherButton)) 
                {
                    showDealerCard = true;
                    if (dealerCard > playerCard) 
                    {
                        gameState = 1; // win
                    } 
                    else 
                    {
                        gameState = 2; // lose
                    }
                }
                if (CheckCollisionPointRec(mouse, lowerButton)) 
                {
                    showDealerCard = true;
                    if (dealerCard < playerCard) 
                    {
                        gameState = 1; // win
                    } 
                    else 
                    {
                        gameState = 2; // lose
                    }
                }
            } 
            // Play Again Button 
            else 
            {
                if (CheckCollisionPointRec(mouse, playAgainButton)) 
                {
                    playerCard = (rand() % 13) + 1;
                    dealerCard = (rand() % 13) + 1;
                    
                    while (dealerCard == playerCard) 
                    {
                        dealerCard = (rand() % 13) + 1;
                    }
                    
                    showDealerCard = false;
                    gameState = 0;
                }
            }
        }
        
        BeginDrawing();
        ClearBackground(DARKGREEN);

        // title
        int titleWidth = MeasureText("BACCARAT", 40);
        DrawText("BACCARAT", (800 - titleWidth) / 2, 50, 40, GOLD);
        
        // Player Card
        int playerTextWidth = MeasureText("Your Card:", 30);
        DrawText("Your Card:", playerTextX - playerTextWidth / 2, textY, 30, WHITE);
        DrawRectangle(playerTextX - 50, cardY, 100, 150, WHITE);
        DrawRectangleLines(playerTextX - 50, cardY, 100, 150, BLACK);

        // Player Card Value
        if (playerCard == 1) 
        {
            DrawText("A", playerTextX - 10, cardY + 60, 40, RED);
        } 
        else if (playerCard == 11) 
        {
            DrawText("J", playerTextX - 10, cardY + 60, 40, RED);
        } 
        else if (playerCard == 12) 
        {
            DrawText("Q", playerTextX - 10, cardY + 60, 40, RED);
        } 
        else if (playerCard == 13) 
        {
            DrawText("K", playerTextX - 10, cardY + 60, 40, RED);
        } 
        else if (playerCard == 10) 
        {
            DrawText("10", playerTextX - 20, cardY + 60, 40, RED);
        } 
        else 
        {
            if (playerCard == 2) DrawText("2", playerTextX - 10, cardY + 60, 40, RED);
            if (playerCard == 3) DrawText("3", playerTextX - 10, cardY + 60, 40, RED);
            if (playerCard == 4) DrawText("4", playerTextX - 10, cardY + 60, 40, RED);
            if (playerCard == 5) DrawText("5", playerTextX - 10, cardY + 60, 40, RED);
            if (playerCard == 6) DrawText("6", playerTextX - 10, cardY + 60, 40, RED);
            if (playerCard == 7) DrawText("7", playerTextX - 10, cardY + 60, 40, RED);
            if (playerCard == 8) DrawText("8", playerTextX - 10, cardY + 60, 40, RED);
            if (playerCard == 9) DrawText("9", playerTextX - 10, cardY + 60, 40, RED);
        }
        
        // Dealer Card 
        int dealerTextWidth = MeasureText("Dealer Card:", 30);
        DrawText("Dealer Card:", dealerTextX - dealerTextWidth / 2, textY, 30, WHITE);
        DrawRectangle(dealerTextX - 50, cardY, 100, 150, WHITE);
        DrawRectangleLines(dealerTextX - 50, cardY, 100, 150, BLACK);
        
        // Dealer Card Value
        if (showDealerCard) 
        {
            if (dealerCard == 1) 
            {
                DrawText("A", dealerTextX - 10, cardY + 60, 40, RED);
            } 
            else if (dealerCard == 11) 
            {
                DrawText("J", dealerTextX - 10, cardY + 60, 40, RED);
            } 
            else if (dealerCard == 12) 
            {
                DrawText("Q", dealerTextX - 10, cardY + 60, 40, RED);
            } 
            else if (dealerCard == 13) 
            {
                DrawText("K", dealerTextX - 10, cardY + 60, 40, RED);
            } 
            else if (dealerCard == 10) 
            {
                DrawText("10", dealerTextX - 20, cardY + 60, 40, RED);
            } 
            else 
            {
                if (dealerCard == 2) DrawText("2", dealerTextX - 10, cardY + 60, 40, RED);
                if (dealerCard == 3) DrawText("3", dealerTextX - 10, cardY + 60, 40, RED);
                if (dealerCard == 4) DrawText("4", dealerTextX - 10, cardY + 60, 40, RED);
                if (dealerCard == 5) DrawText("5", dealerTextX - 10, cardY + 60, 40, RED);
                if (dealerCard == 6) DrawText("6", dealerTextX - 10, cardY + 60, 40, RED);
                if (dealerCard == 7) DrawText("7", dealerTextX - 10, cardY + 60, 40, RED);
                if (dealerCard == 8) DrawText("8", dealerTextX - 10, cardY + 60, 40, RED);
                if (dealerCard == 9) DrawText("9", dealerTextX - 10, cardY + 60, 40, RED);
            }
        } 
        else 
        {
            // Dealer Card Down
            DrawRectangle(dealerTextX - 40, cardY + 10, 80, 130, DARKBLUE);
            DrawRectangleLines(dealerTextX - 40, cardY + 10, 80, 130, BLACK);
        }
        
        // Button During Game Loop
        if (gameState == 0) 
        {
            // Higher Button
            DrawRectangleRec(higherButton, GREEN);
            DrawRectangleLinesEx(higherButton, 2, BLACK);
            int higherTextWidth = MeasureText("HIGHER", 20);
            DrawText("HIGHER", higherButton.x + (higherButton.width - higherTextWidth) / 2, higherButton.y + 15, 20, BLACK);
            
            // Lower Button
            DrawRectangleRec(lowerButton, RED);
            DrawRectangleLinesEx(lowerButton, 2, BLACK);
            int lowerTextWidth = MeasureText("LOWER", 20);
            DrawText("LOWER", lowerButton.x + (lowerButton.width - lowerTextWidth) / 2, lowerButton.y + 15, 20, BLACK);
        } 
        else 
        {
            // Win and Lose
            if (gameState == 1) 
            {
                DrawText("YOU WIN!", 290, 300, 50, YELLOW);
            } 
            else
            {
                DrawText("YOU LOSE!", 270, 300, 50, RED);
            }
            
            // Play Again button
            DrawRectangleRec(playAgainButton, YELLOW);
            DrawRectangleLinesEx(playAgainButton, 2, BLACK);
            int playAgainWidth = MeasureText("PLAY AGAIN", 15);
            DrawText("PLAY AGAIN", playAgainButton.x + (playAgainButton.width - playAgainWidth) / 2, playAgainButton.y + 15, 15, BLACK);
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
