#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight) {
    tileCount = (tileSet.GetWidth() / tileWidth) * (tileSet.GetHeight() / tileHeight);
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index >= (unsigned)tileCount) {
        return;
    }

    int tilesPerRow = tileSet.GetWidth() / tileWidth;
    int row = index / tilesPerRow;
    int col = index % tilesPerRow;

    int clipX = col * tileWidth;
    int clipY = row * tileHeight;

    tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
    tileSet.Render(x, y, tileWidth, tileHeight);
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}
