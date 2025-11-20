#include "sprite.h"
#include "mapa.h"

// Desenha um sprite centralizado no TILE e com escala ajustável
void DrawSpriteInTile(Texture2D tex, int tileX, int tileY, float scale) {
    // tamanho final do sprite
    float drawW = tex.width * scale;
    float drawH = tex.height * scale;

    // centralização dentro do tile
    float posX = tileX * TILE + (TILE - drawW) / 2.0f;
    float posY = tileY * TILE + (TILE - drawH) / 2.0f;

    DrawTextureEx(
        tex,
        (Vector2){ posX, posY },
        0.0f,
        scale,
        WHITE
    );
}
