#include <math.h>
#include <stdio.h>
#include "Game.h"

const int Width = 800;
const int Height = 450;

Enemy enemy = { (Rectangle){ Width / 2 - PLAYER_SIZE / 2, 50, PLAYER_SIZE, PLAYER_SIZE }, {100} };

// Fonction pour dessiner l'ennemi
void DrawEnemy(Enemy enemy) {
    DrawRectangleRec(enemy.bounds, ORANGE);
}

// Fonction pour détecter les collisions entre le joueur et l'ennemi
bool CheckPlayerEnemyCollision(Player player, Enemy enemy) {
    Rectangle playerBounds = GetPlayerBounds(player);
    return CheckCollisionRecs(playerBounds, enemy.bounds);
}
// Fonction pour gérer la logique de combat
void HandleCombat(Player *player, Enemy *enemy) {
    if (CheckPlayerEnemyCollision(*player, *enemy)) {
        // Réduire la vie du joueur si collision détectée
        player->health -= 10;
    }
}

void UpdateEnemy(Enemy *enemy, Player player, int screenWidth, int screenHeight) {
    // Calculer la distance horizontale et verticale entre l'ennemi et le joueur
    float distanceX = player.position.x - enemy->bounds.x;
    float distanceY = player.position.y - enemy->bounds.y;

    // Vérifier si le joueur peut sauter
    Rectangle phitbox = GetPhitbox();

    // Calculer la longueur du vecteur direction
    float distanceLength = sqrtf(distanceX * distanceX + distanceY * distanceY);

    // Vérifier si la distance est nulle pour éviter la division par zéro
    if (distanceLength != 0) {
        // Normaliser les distances horizontale et verticale
        float directionX = distanceX / distanceLength;
        float directionY = distanceY / distanceLength;

        // Appliquer la vitesse à l'ennemi dans la direction du joueur
        enemy->bounds.x += directionX * ENEMY_SPEED;
        enemy->bounds.y += directionY * ENEMY_SPEED;

        // Ajouter une vitesse verticale à l'ennemi (simulation de gravité)
        enemy->speed.y += GRAVITY;
        // Mettre à jour la position verticale de l'ennemi en fonction de sa vitesse
        enemy->bounds.y += enemy->speed.y;
    }

    // Vérifier si l'ennemi peut sauter
    if (enemy->bounds.y >= GROUND_Y - enemy->bounds.height) {
        // Si l'ennemi est au sol, il peut sauter
        enemy->speed.y = -JUMP_FORCE; // Appliquer une force vers le haut
    }

    // Vérifier si l'ennemi est en collision avec la phitbox
    if (CheckCollisionRectangles(enemy->bounds, phitbox)) {
        // Si collision avec la phitbox, réinitialiser la position de l'ennemi
        enemy->bounds.y = phitbox.y - enemy->bounds.height;
        enemy->speed.y = 0; // Arrêter le mouvement vertical de l'ennemi
    }

    // Restreindre la position de l'ennemi en fonction de l'écran
    if (enemy->bounds.x < 0) {
        enemy->bounds.x = 0;
    } else if (enemy->bounds.x + enemy->bounds.width > screenWidth) {
        enemy->bounds.x = screenWidth - enemy->bounds.width;
    }

    if (enemy->bounds.y < 0) {
        enemy->bounds.y = 0;
    } else if (enemy->bounds.y + enemy->bounds.height > screenHeight) {
        enemy->bounds.y = screenHeight - enemy->bounds.height;
    }

    // Vérifier les collisions avec le sol
    if (enemy->bounds.y >= GROUND_Y - enemy->bounds.height) {
        enemy->bounds.y = GROUND_Y - enemy->bounds.height;
    }
}