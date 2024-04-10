#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
    Rectangle bounds;
    const char *text;
} GameButton;

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Rectangle rect;
    int jumpCount;
    float lastJumpTime;
    int health;
} Player;

Player InitPlayer(Vector2 position, Vector2 size);
void DrawPlayer(Player player);
bool CheckPlayerGroundCollision(Player player, Rectangle groundRects[], int numGroundRects, Rectangle platformRect);
void map_unload();
void map_load();
void map_draw();

#define PLAYER_SIZE 50
#define PLAYER_SPEED 5.0f
#define ENEMY_SPEED 3.0f

#define GRAVITY         0.5f
#define JUMP_FORCE      13.0f
#define MAX_FALL_SPEED  10.0f
#define GROUND_Y        GetScreenHeight() - 32
#define MAX_JUMP_COUNT  2
#define COOLDOWN_TIME   3000

#define MAX_GROUND_RECTS 10

bool IsMouseInsideButton(Rectangle buttonBounds);

extern Rectangle groundRects[MAX_GROUND_RECTS];
extern int numGroundRects;
Rectangle GetPlatformRect();
extern Rectangle Rplat;
void UpdatePlayer(Player *player, int screenWidth, int screenHeight);
bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);
Rectangle GetPhitbox();
Rectangle GetPlayerBounds(Player player);

extern const int screenWidth;
extern const int screenHeight;

typedef struct {
    Rectangle bounds;
    Vector2 speed; // Ajout du membre speed
    int health;
} Enemy;

// Fonction pour dessiner l'ennemi
void DrawEnemy(Enemy enemy);

// Fonction pour détecter les collisions entre le joueur et l'ennemi
bool CheckPlayerEnemyCollision(Player player, Enemy enemy);

// Fonction pour gérer la logique de combat
void HandleCombat(Player *player, Enemy *enemy);

// Fonction pour mettre à jour l'ennemi en se dirigeant vers le joueur
void UpdateEnemy(Enemy *enemy, Player player, int screenWidth, int screenHeight);


bool CheckCollisionRectangles(Rectangle rect1, Rectangle rect2);

#endif