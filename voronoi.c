#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>

#include "tiles.h"

// #define GRID_HEIGHT 100
// #define GRID_WIDTH 500
// #define SEED_NUM 1000

int GRID_HEIGHT = 720; // this is default, for my personal laptop, 200 is max size for terminal
int GRID_WIDTH = 720;  // this is defaultm for my personal laptop, about 900 is max width for terminal
int SEED_NUM = 250;

//struct tile_s* gridMatrix[100][500];
struct tile_s ***gridMatrix;  // Pointer to a 2D array

typedef struct Seed
{
    unsigned int x;
    unsigned int y;
    char ascii;
    struct tile_s* tile;
} Seed;


void init_world()
{
    // Allocate memory for gridMatrix based on GRID_HEIGHT and GRID_WIDTH
    gridMatrix = (struct tile_s ***)malloc(GRID_HEIGHT * sizeof(struct tile_s **));
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        gridMatrix[i] = (struct tile_s **)malloc(GRID_WIDTH * sizeof(struct tile_s *));
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            gridMatrix[i][j] = &tile1;
        }
    }
}

void free_grid()
{
    // Free memory for gridMatrix
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        free(gridMatrix[i]);
    }
    free(gridMatrix);
}


#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[38;5;220m"
#define BLU "\e[38;5;21m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define BRN "\e[38;5;94m"
#define LBL "\e[38;5;33m"
#define PUR "\e[38;5;54m"
#define ORG "\e[38;5;166m"

void print_grid()
{
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if(gridMatrix[i][j] == NULL){
                continue;
            }
            char *color = "";
            switch (gridMatrix[i][j]->tile_idx)
            {
            case Tile1:
                color = PUR;
                break;
            case Tile2:
                color = YEL;
                break;
            case Tile3:
                color = BLU;
                break;
            case Tile4:
                color = GRN;
                break;
            case Tile5:
                color = RED;
                break;
            case Tile6:
                color = BRN;
                break;
            case Tile7:
                color = WHT;
                break;
            case Tile8:
                color = ORG;
                break;
            case Tile9:
                color = LBL;
                break;    
            default:
                // unreachable
                fprintf(stderr, "unhandled color case: ---> %c <---\n", gridMatrix[i][j]->id);
                break;
            }
            printf("%s%c", color, gridMatrix[i][j]->ascii);
        }
        putchar('\n');
    }
}

void gen_voronoi_seeds(Seed storedSeeds[SEED_NUM])
{
    for (int i = 0; i < SEED_NUM; i++)
    {
        storedSeeds[i].x = 1 + (rand() % (GRID_HEIGHT - 1));
        storedSeeds[i].y = 1 + (rand() % (GRID_WIDTH - 1));
        storedSeeds[i].ascii = tiles[i % TileCount]->ascii;
        storedSeeds[i].tile = tiles[i % TileCount];
    }
}

static inline double euclidean_distance(int x, int y, int x2, int y2)
{
    return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
}

static inline double manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void voronoi_generate(Seed storedSeeds[SEED_NUM], double (*distance_func)(int, int, int, int))
{
    for (int x = 0; x < GRID_HEIGHT; x++)
    {
        for (int y = 0; y < GRID_WIDTH; y++)
        {
            int closestSeed = 0;
            int closestDist = distance_func(x, y, storedSeeds[0].x, storedSeeds[0].y);
            for (int i = 1; i < SEED_NUM; i++)
            {
                int currDist = distance_func(x, y, storedSeeds[i].x, storedSeeds[i].y);
                if (currDist < closestDist)
                {
                    closestSeed = i;
                    closestDist = currDist;
                }
            }
            gridMatrix[x][y] = storedSeeds[closestSeed].tile;
        }
    }
}

void print_usage(char *program_name)
{
    printf("Usage: %s [OPTIONS]\n", program_name);
    printf("OPTIONS:\n");
    printf("  -h, --height <height>   Set grid height (default is 100)\n");
    printf("  -w, --width <width>     Set grid width  (default is 500)\n");
    printf("  -s, --seeds <seeds>     Set seed amount (default is 800)\n");
    printf("  -e, --euclidean        Use Euclidean distance for Voronoi\n");
    printf("  -m, --manhattan        Use Manhattan distance for Voronoi\n");
    printf("  -?, --help             Show usage information\n");
}


void write_ppm_image(const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        return;
    }

    fprintf(file, "P6\n");
    fprintf(file, "%d %d\n", GRID_WIDTH, GRID_HEIGHT);
    fprintf(file, "255\n");

    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            unsigned char r, g, b;
            switch (gridMatrix[i][j]->tile_idx)
            {
            case Tile1:
                r = 128;  // purple
                g = 0;
                b = 128;
                break;
            case Tile2:
                r = 255; // yellow
                g = 255;
                b = 0;
                break;
            case Tile3:
                r = 0;  // blue
                g = 0;
                b = 255;
                break;
            case Tile4: // green
                r = 0;
                g = 255;
                b = 0;
                break;
            case Tile5: // red
                r = 255;
                g = 0;
                b = 0;
                break;
            case Tile6: // brown
                r = 102;
                g = 52;
                b = 0;
                break;
            case Tile7: // orange
                r = 255;
                g = 128;
                b = 0;
                break;
            case Tile8: // light blue
                r = 51;
                g = 255;
                b = 255;
                break;
            case Tile9: // weird pink/purple
                r = 255;
                g = 51;
                b = 255;
                break;
            default:
                // white to default
                r = 255;
                g = 255;
                b = 255;
                break;
            }

            // Write RGB values to the file
            fputc(r, file);
            fputc(g, file);
            fputc(b, file);
        }
    }

    fclose(file);
}



int main(int argc, char *argv[])
{
    srand(time(NULL));
    Seed seeds[SEED_NUM];

    int opt;
    int use_euclidean = 1; // Default to Euclidean distance

    while ((opt = getopt(argc, argv, "h:w:s:em?")) != -1)
    {
        switch (opt)
        {
        case 'h':
            GRID_HEIGHT = atoi(optarg);
            break;
        case 'w':
            GRID_WIDTH = atoi(optarg);
            break;
        case 's':
            SEED_NUM = atoi(optarg);
            break;
        case 'e':
            use_euclidean = 1;
            break;
        case 'm':
            use_euclidean = 0;
            break;
        case '?':
            print_usage(argv[0]);
           // free_grid();
            return 0;
        }
    }

    gen_voronoi_seeds(seeds);
    init_world();

    if (use_euclidean)
    {
        voronoi_generate(seeds, euclidean_distance);
    }
    else
    {
        voronoi_generate(seeds, manhattan_distance);
    }
    write_ppm_image("voronoi_diagram.ppm");
    //print_grid();
    free_grid();

    return 0;
}