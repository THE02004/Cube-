/*  ________  __                                   ______             __            __                                  __       
   |        \|  \                                 /      \           |  \          |  \                                |  \      
    \$$$$$$$$| $$____    ______    ______        |  $$$$$$\ __    __  \$$  _______ | $$____    ______    ______    ____| $$      
      | $$   | $$    \  /      \  /      \       | $$ __\$$|  \  |  \|  \ /       \| $$    \  |      \  /      \  /      $$      
      | $$   | $$$$$$$\|  $$$$$$\|  $$$$$$\      | $$|    \| $$  | $$| $$|  $$$$$$$| $$$$$$$\  \$$$$$$\|  $$$$$$\|  $$$$$$$      
      | $$   | $$  | $$| $$    $$| $$  | $$      | $$ \$$$$| $$  | $$| $$| $$      | $$  | $$ /      $$| $$   \$$| $$  | $$      
      | $$   | $$  | $$| $$$$$$$$| $$__/ $$      | $$__| $$| $$__/ $$| $$| $$_____ | $$  | $$|  $$$$$$$| $$      | $$__| $$      
      | $$   | $$  | $$ \$$     \ \$$    $$       \$$    $$ \$$    $$| $$ \$$     \| $$  | $$ \$$    $$| $$       \$$    $$      
       \$$    \$$   \$$  \$$$$$$$  \$$$$$$         \$$$$$$   \$$$$$$  \$$  \$$$$$$$ \$$   \$$  \$$$$$$$ \$$        \$$$$$$$      
*/
#include "raylib.h"
#include "Game.h"

extern Rectangle groundRects[MAX_GROUND_RECTS];
extern int numGroundRects;

Rectangle Rect = {0, 90, 150, 200}; // Rectangle de base pour les textures
Rectangle Rplat = {280,240, 250, 30};
Rectangle Rect2 = {-80, -350, 980, 950};

// Positions initiales des textures
Vector2 initialPositions[] = {
    {152, -415},    // Première texture
    {52, -415},     // Deuxième texture
    {-204, -415},   // Troisième texture
    {-402, -415},   // Quatrième texture
    {-542, -415}    // Cinquième texture
};

// Positions ajustées des textures
Vector2 positions[5];
Vector2 platforme1 = {0, -50}; 

// Taille initiale des textures
Vector2 size = {290, 200};

// Taille ajustée des textures
Vector2 sizes[5];

Texture2D plat; // Première texture
Texture2D plat1; // Deuxième texture
Texture2D plat2; // Troisième texture
Texture2D plat3; // Quatrième texture
Texture2D plat6; // Cinquième texture
Texture2D platf1; 

void map_load(void)
{
    // Charger les textures du sol
    plat = LoadTexture("ground.png"); // Charger la première texture
    plat1 = LoadTexture("ground.png"); // Charger la deuxième texture
    plat2 = LoadTexture("ground.png"); // Charger la troisième texture
    plat3 = LoadTexture("ground.png"); // Charger la quatrième texture
    plat6 = LoadTexture("ground.png"); // Charger la cinquième texture
    platf1 = LoadTexture("platform2.png");

    // Ajuster les positions et les tailles en fonction de la taille de l'écran
    for (int i = 0; i < 5; i++)
    {
        positions[i].x = initialPositions[i].x * (float)GetScreenWidth() / 800.0f;
        positions[i].y = initialPositions[i].y * (float)GetScreenHeight() / 450.0f;

        sizes[i].x = size.x * (float)GetScreenWidth() / 800.0f;
        sizes[i].y = size.y * (float)GetScreenHeight() / 450.0f;
    }
}

void map_draw(void)
{

    // Dessiner les textures du sol
    for (int i = 0; i < 5; i++)
    {
        DrawTexturePro(plat, Rect, (Rectangle){0, 0, size.x, size.y}, (Vector2){positions[i].x, positions[i].y}, 0, WHITE);
    }

    DrawTexturePro(platf1, Rplat, Rplat, platforme1, 0, WHITE);

}

void map_unload(void)
{
    UnloadTexture(plat);
    UnloadTexture(plat1);
    UnloadTexture(plat2);
    UnloadTexture(plat3);
    UnloadTexture(plat6);
}
