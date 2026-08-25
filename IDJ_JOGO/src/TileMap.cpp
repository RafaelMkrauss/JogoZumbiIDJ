#include "TileMap.h"
#include "GameObject.h"

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
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
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

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int tileIndex = At(x, y, layer);
            if (tileIndex < 0) {
                continue;
            }

            float posX = associated.box.x + x * tileWidth;
            float posY = associated.box.y + y * tileHeight;

            tileSet->RenderTile((unsigned)tileIndex, posX, posY);
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
