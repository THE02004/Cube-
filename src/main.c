#include "raylib.h"
#include <stdio.h>
#include "Game.h"

const int screenWidth = 800;
const int screenHeight = 450;

extern Enemy enemy;

bool gameLoaded = false;
bool gameOver = false;
bool gameRunning = true; 

bool CheckCollisionRectangles(Rectangle rect1, Rectangle rect2) {
    return (rect1.x < rect2.x + rect2.width &&
            rect1.x + rect1.width > rect2.x &&
            rect1.y < rect2.y + rect2.height &&
            rect1.y + rect1.height > rect2.y);
}

Rectangle GetPlayerBounds(Player player) {
    return (Rectangle){ player.position.x, player.position.y, player.size.x, player.size.y };
}

int xSkyOffset = 0;
int elapsedTime = 0;

Vector2 test = {0,300};
Rectangle phitbox = {298,295, 195, 18};

Rectangle GetPhitbox() {
    return phitbox;
}

bool IsMouseInsideButton(Rectangle buttonBounds) {
    Vector2 mousePos = GetMousePosition();
    return (mousePos.x >= buttonBounds.x && mousePos.x <= buttonBounds.x + buttonBounds.width &&
            mousePos.y >= buttonBounds.y && mousePos.y <= buttonBounds.y + buttonBounds.height);
}

void DrawButton(Rectangle bounds, const char *text, Color textColor, Color buttonColor) {
    DrawRectangleRec(bounds, buttonColor);
    DrawText(text, bounds.x + bounds.width / 2 - MeasureText(text, 20) / 2, bounds.y + bounds.height / 2 - 10, 20, textColor);
}

int main(void) 
{
    InitWindow(screenWidth, screenHeight, "Cube");
    SetTargetFPS(60);

    GameButton startButton = { (Rectangle){ screenWidth / 2 - 100, screenHeight / 2 - 25, 200, 50 }, "Start" };
    Rectangle startButtonBounds = startButton.bounds;

    Player player = InitPlayer(test, (Vector2){ PLAYER_SIZE, PLAYER_SIZE });
    Enemy enemy = { 
    (Rectangle){ screenWidth - PLAYER_SIZE, screenHeight - PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE }, // Position en bas à droite
    { 0, 100 } 
    };

    Texture2D sky = LoadTexture("sky.png");
    Rectangle Rect3 = { 0, 131, sky.width, sky.height };

    while (!WindowShouldClose() && gameRunning) 
    {
        if ((IsMouseInsideButton(startButtonBounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyDown(KEY_ENTER)) 
        {
            printf("Start button clicked!\n");
            map_load();
            gameLoaded = true;
            gameOver = false;
        }

        if (gameLoaded && !gameOver) 
        {
            UpdatePlayer(&player, screenWidth, screenHeight);
            UpdateEnemy(&enemy, player, screenWidth, screenHeight);
            if (player.health <= 0) 
            {
                gameOver = true;
            }

            Rectangle playerBounds = GetPlayerBounds(player);

            if (CheckCollisionRectangles(playerBounds, phitbox))
            {
                player.position.y = phitbox.y - player.size.y;
            }

            elapsedTime++;
            xSkyOffset = (xSkyOffset + 1) % (int)Rect3.width;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameLoaded && !gameOver) 
        {
            HandleCombat(&player, &enemy);

            DrawTextureRec(sky, Rect3, (Vector2){ -xSkyOffset, 0 }, WHITE);
            DrawTextureRec(sky, Rect3, (Vector2){ Rect3.width - xSkyOffset, 0 }, WHITE);
            map_draw();
            DrawEnemy(enemy);
            DrawPlayer(player);
            DrawText(TextFormat("Time: %02ds", elapsedTime), screenWidth - 150, 20, 20, BLACK);
        } 
        else if (gameOver) 
        {
            DrawText("Game Over!", screenWidth / 2 - MeasureText("Game Over!", 40) / 2, screenHeight / 2 - 40, 40, RED);
            DrawText("Press ENTER to restart or ESC to quit", screenWidth / 2 - MeasureText("Press ENTER to restart or ESC to quit", 20) / 2, screenHeight / 2, 20, BLACK);

            if (IsKeyDown(KEY_ENTER)) 
            {
                gameLoaded = false;
                gameOver = false;
                elapsedTime = 0;
                player.health = 100;
                enemy.health = 100;
                player.position = (Vector2){ PLAYER_SIZE, PLAYER_SIZE }; // Réinitialisation de la position du joueur
                enemy.bounds = (Rectangle){ screenWidth - PLAYER_SIZE, screenHeight - PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE }; // Réinitialisation de la position de l'ennemi

            }

            if (IsKeyDown(KEY_ESCAPE)) 
            {
                gameRunning = false;
            }
        } 
        else 
            DrawButton(startButton.bounds, startButton.text, BLACK, GRAY);

        EndDrawing();
    }

    UnloadTexture(sky);
    map_unload();
    CloseWindow();

    return 0;
}
