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
#include <stdio.h>
#include "Game.h"

bool collision = false;
bool gameLoaded = false;
// Vérifie s'il y a collision entre deux rectangles
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

Vector2 test = {0,0};
Rectangle phitbox = {298,295, 195, 18};
Rectangle GetPhitbox() {
    return phitbox;
}

bool IsMouseInsideButton(Rectangle buttonBounds) {
    Vector2 mousePos = GetMousePosition();
    return (mousePos.x >= buttonBounds.x && mousePos.x <= buttonBounds.x + buttonBounds.width &&
            mousePos.y >= buttonBounds.y && mousePos.y <= buttonBounds.y + buttonBounds.height);
}

// Dessine un bouton rectangulaire avec du texte à l'intérieur
void DrawButton(Rectangle bounds, const char *text, Color textColor, Color buttonColor) {
    // Dessine le rectangle du bouton
    DrawRectangleRec(bounds, buttonColor);
    
    // Dessine le texte centré dans le rectangle
    DrawText(text, bounds.x + bounds.width / 2 - MeasureText(text, 20) / 2, bounds.y + bounds.height / 2 - 10, 20, textColor);
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Cube");
    SetTargetFPS(60);

    // Création d'un bouton
    GameButton startButton = { (Rectangle){ screenWidth / 2 - 100, screenHeight / 2 - 25, 200, 50 }, "Start" };
    Rectangle startButtonBounds = startButton.bounds;

    // Initialisation du joueur
    Player player = InitPlayer((Vector2){ screenWidth / 2 - PLAYER_SIZE / 2, screenHeight / 2 - PLAYER_SIZE / 2 }, (Vector2){ PLAYER_SIZE, PLAYER_SIZE });

    Texture2D sky = LoadTexture("sky.png"); // charge le ciel
    Rectangle Rect3 = { 0, 131, sky.width, sky.height };

while (!WindowShouldClose()) {
    if ((IsMouseInsideButton(startButtonBounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyDown(KEY_ENTER)) {
        printf("Start button clicked!\n");
        map_load();
        gameLoaded = true;
    }

    if (gameLoaded) {
        // Mettre à jour le joueur en fonction des entrées utilisateur et des collisions avec la plateforme
        UpdatePlayer(&player, screenWidth, screenHeight);
    
    Rectangle playerBounds = GetPlayerBounds(player);

    if (CheckCollisionRecs(playerBounds, phitbox)){
            // Si une collision est détectée, ajuster la position du joueur pour le maintenir sur la plateforme
            player.position.y = phitbox.y - player.size.y;
        }

        // Déplacer le fond de manière cyclique
        xSkyOffset = (xSkyOffset + 1) % (int)Rect3.width;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (gameLoaded) {
        // Dessiner le ciel en arrière-plan
        DrawTextureRec(sky, Rect3, (Vector2){ -xSkyOffset, 0 }, WHITE);
        DrawTextureRec(sky, Rect3, (Vector2){ Rect3.width - xSkyOffset, 0 }, WHITE);
        map_draw();
        DrawPlayer(player); // Appel de la fonction DrawPlayer
    } else {
        // Si le jeu n'est pas chargé, afficher le bouton de démarrage
        DrawButton(startButton.bounds, startButton.text, BLACK, GRAY);
    }

    EndDrawing();
}

    UnloadTexture(sky);
    map_unload();
    CloseWindow();

    return 0;
}
