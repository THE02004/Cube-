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
} Player;

Player InitPlayer(Vector2 position, Vector2 size);
void DrawPlayer(Player player);
bool CheckPlayerGroundCollision(Player player, Rectangle groundRects[], int numGroundRects, Rectangle platformRect);
void map_unload();
void map_load();
void map_draw();

#define PLAYER_SIZE 50
#define PLAYER_SPEED 5.0f

#define GRAVITY         0.5f
#define JUMP_FORCE      15.0f
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
#endif