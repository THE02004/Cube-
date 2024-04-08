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
#include "Game.h"

Player InitPlayer(Vector2 position, Vector2 size) {
    Player player;
    player.position = position;
    player.rect = (Rectangle){ player.position.x, player.position.y, size.x, size.y };
    player.speed = (Vector2){ 0, 0 };
    player.size = size;
    player.jumpCount = 0;
    player.lastJumpTime = 0;
    return player;
}

void UpdatePlayer(Player *player, int screenWidth, int screenHeight) {
    // Gérer les entrées de clavier pour le déplacement horizontal du joueur
    if (IsKeyDown(KEY_LEFT)) {
        player->speed.x = -PLAYER_SPEED; // Déplacer vers la gauche
    } else if (IsKeyDown(KEY_RIGHT)) {
        player->speed.x = PLAYER_SPEED; // Déplacer vers la droite
    } else {
        player->speed.x = 0; // Arrêter le mouvement horizontal si aucune touche n'est enfoncée
    }

    // Vérifier si le joueur peut sauter (au sol ou sur la plateforme)
    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && (player->position.y >= GROUND_Y - player->size.y || CheckCollisionRecs(GetPlayerBounds(*player), GetPhitbox()))) {
        player->speed.y = -JUMP_FORCE; // Appliquer la force de saut
        player->jumpCount = 1; // Réinitialiser le compteur de saut
    }

    // Appliquer la gravité
    player->speed.y += GRAVITY;

    // Mettre à jour la position du joueur en fonction de sa vitesse
    player->position.x += player->speed.x;
    player->position.y += player->speed.y;

    // Restreindre la position du joueur en fonction de l'écran
    if (player->position.x < 0) {
        player->position.x = 0;
    } else if (player->position.x + player->size.x > screenWidth) {
        player->position.x = screenWidth - player->size.x;
    }

    if (player->position.y < 0) {
        player->position.y = 0;
    } else if (player->position.y + player->size.y > screenHeight) {
        player->position.y = screenHeight - player->size.y;
    }

    // Vérifier les collisions avec le sol
    if (player->position.y >= GROUND_Y - player->size.y) {
        player->position.y = GROUND_Y - player->size.y;
        player->speed.y = 0;
        player->jumpCount = 0; // Réinitialiser le compteur de saut lorsque le joueur touche le sol
    }

    // Vérifier la collision avec la plateforme
    if (CheckCollisionRecs(GetPlayerBounds(*player), GetPhitbox())) {
        // Si le joueur est en collision avec la plateforme, réinitialiser le saut
        player->jumpCount = 0;
    }
}

void DrawPlayer(Player player) {
    DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, RED);
}