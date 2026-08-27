#include "TileMap.h"
#include "GameObject.h"
#include "Camera.h"

#include <fstream>
#include <sstream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet)
    : Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream mapFile(file);

    std::stringstream buffer;
    buffer << mapFile.rdbuf();
    std::string content = buffer.str();

    for (char& c : content) {
        if (c == ',') {
            c = ' ';
        }
    }

    std::stringstream ss(content);
    ss >> mapWidth >> mapHeight >> mapDepth;

    tileMatrix.resize(mapWidth * mapHeight * mapDepth);
    for (int i = 0; i < (int)tileMatrix.size(); i++) {
        ss >> tileMatrix[i];
    }

    parallax.assign(mapDepth, 1.0f);
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

void TileMap::SetParallax(int layer, float factor) {
    parallax[layer] = factor;
}

int& TileMap::At(int x, int y, int z) {
    int index = z * (mapWidth * mapHeight) + y * mapWidth + x;
    return tileMatrix[index];
}

void TileMap::Update(float dt) {
    (void)dt;
}

void TileMap::RenderLayer(int layer) {
    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();
    float factor = parallax[layer];

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int tileIndex = At(x, y, layer);
            if (tileIndex < 0) {
                continue;
            }

            float worldX = associated.box.x + x * tileWidth;
            float worldY = associated.box.y + y * tileHeight;

            float renderX = worldX + Camera::pos.x * (1.0f - factor);
            float renderY = worldY + Camera::pos.y * (1.0f - factor);

            tileSet->RenderTile((unsigned)tileIndex, renderX, renderY);
        }
    }
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDepth; layer++) {
        RenderLayer(layer);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}
