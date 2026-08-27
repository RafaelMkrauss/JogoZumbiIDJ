#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"

#include <vector>
#include <memory>
#include <string>

class TileMap : public Component {
public:
    TileMap(GameObject& associated, std::string file, TileSet* tileSet);

    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    void SetParallax(int layer, float factor);

    int& At(int x, int y, int z = 0);

    void Update(float dt) override;
    void Render() override;
    void RenderLayer(int layer);

    int GetWidth();
    int GetHeight();
    int GetDepth();

private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;
    std::vector<float> parallax;

    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif
