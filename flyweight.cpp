#define HEIGHT 25
#define WIDTH 25
#include <iostream>
#include <ctime>
#include <cstdlib>

enum Texture : unsigned char {
    GRASS, HILL, RIVER,
    COUNT //little hack
};

class Terrain{
    bool _isWater;    
    Texture _texture;
    int _moveCost;
    public:
    Terrain(bool isWater, int moveCost, Texture txt):
        _isWater(isWater), _moveCost(moveCost), _texture(txt) {}
    bool isWater() const { return _isWater; }
    int moveCost() const { return _moveCost; }
    const Texture& getTexture() const { return _texture; } 
};

class World{
    Terrain _grass; //this has a size of 8
    Terrain _hill;
    Terrain _river;
    Terrain* _map[HEIGHT][HEIGHT]; //this has a size of 4 * H * W
    void generate();
    public:
    World();
    const Terrain& getTile(unsigned, unsigned) const;
};

World::World():
    _grass(false, 3, GRASS), _hill(false, 2, HILL), _river(true, 1, RIVER)
{
    generate(); 
}

void World::generate() {
    srand(time(nullptr));
    for(unsigned i=0; i<HEIGHT; ++i){
        for(unsigned j=0; j<WIDTH; ++j){
            switch (rand()%COUNT){
                case 0:
                    _map[i][j] = &_grass;
                break;
                case 1:                
                    _map[i][j] = &_hill;
                break;
                case 2:
                    _map[i][j] = &_river;
                break;
            }
        }
    }
}

const Terrain& World::getTile(unsigned i, unsigned j) const
{
    return *(_map[i][j]);
}

int main(){
    World w;

    for(unsigned i =0; i<HEIGHT; ++i){
        for(unsigned j=0; j<WIDTH; ++j){
            std::cout<<w.getTile(i,j).getTexture()<<" ";
        }
        std::cout<<'\n';
    }

    return 0;
}