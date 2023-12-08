/*
   Tile Definitions
*/

#ifndef _TILES_H
#define _TILES_H


// TODO: optimize size?
enum tile_e 
{
   Tile1,
   Tile2,
   Tile3,
   Tile4,
   Tile5,
   Tile6,
   Tile7,
   Tile8,
   Tile9,
   TileCount,
};

struct tile_s
{
   const char id;
   const char ascii;
   const enum tile_e tile_idx;  // TODO: is this needed?
   const float adjacency[TileCount];
};

struct tile_s tile1 = 
{
   .id = '1',
   .ascii = '%',
   .tile_idx = Tile1,
   .adjacency = {0.f},
};

struct tile_s tile2 = 
{
   .id = '2',
   .ascii = '%',
   .tile_idx = Tile2,
   .adjacency = {0.f},
};

struct tile_s tile3 = 
{
   .id = '3',
   .ascii = '%',
   .tile_idx = Tile3,
   .adjacency = {0.f},
};

struct tile_s tile4 = 
{
   .id = '4',
   .ascii = '%',
   .tile_idx = Tile4,
   .adjacency = {0.f},
};

struct tile_s tile5 =
{
    .id = '6',
    .ascii = '%',
    .tile_idx = Tile5,
    .adjacency = {0.f},
};

struct tile_s tile6 =
{
    .id = '6',
    .ascii = '%',
    .tile_idx = Tile6,
    .adjacency = {0.f},
};

struct tile_s tile7 =
{
    .id = '6',
    .ascii = '%',
    .tile_idx = Tile7,
    .adjacency = {0.f},
};

struct tile_s tile8 =
{
    .id = '6',
    .ascii = '%',
    .tile_idx = Tile8,
    .adjacency = {0.f},
};

struct tile_s tile9 =
{
    .id = '6',
    .ascii = '%',
    .tile_idx = Tile9,
    .adjacency = {0.f},
};

// important to keep in the order you defined in the enum
struct tile_s* tiles[TileCount] =
{
   &tile1,
   &tile2,
   &tile3,
   &tile4,
   &tile5,
   &tile6,
   &tile7,
   &tile8,
   &tile9,   
};


#endif /* _TILES_H */
