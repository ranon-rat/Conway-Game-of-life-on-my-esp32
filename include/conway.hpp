
#include <stdlib.h>
#include <Arduino.h>
#define WIDTH 20
#define HEIGHT 20
#define MAX_UPDATES 50

struct Update
{
    int x, y;
    bool is_alive;
};

int resize(int x, int max_value)
{
    if (x < 0)
    {
        return max_value - (abs(x) % max_value);
    }
    if (x >= max_value)
    {
        return x % max_value;
    }
    return x;
}
class Conway
{
public:
    bool *map;
    Update update_queue[MAX_UPDATES];
    int update_count = 0;
    // #  or 0
    Conway(char *initialMap)
    {
        this->map = new bool[WIDTH * HEIGHT];
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            this->map[i] = initialMap[i] == '#';
        }
    }
    /** this will be used for the server, i was thinking that i could just add this into a query
     * that i would execute when updating the map, so i can avoid any kind of problem in the future
     * with race conditioning
     */

    void update_slice(int x, int y, bool is_alive)
    {
        int nx = resize(x, WIDTH);
        int ny = resize(y, HEIGHT);
    
        if (this->update_count >= MAX_UPDATES)
        {
            return; // just in case we run out of space :D
        }
       
        this->update_queue[this->update_count] = {nx, ny, is_alive};
        this->update_count++;
    }
    void apply_updates()
    {
        for (int i = 0; i < this->update_count; i++)
        {
            Update update_obj = this->update_queue[i];
            int x = update_obj.x;
            int y = update_obj.y;
            this->map[y * WIDTH + x] = update_obj.is_alive;
        }
        update_count = 0;
    }
    char *map_to_char()
    {
        char *char_map = new char[WIDTH * HEIGHT];
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            char_map[i] = this->map[i] ? '#' : ' ';
        }
        return char_map;
    }
    int check_neightbours(int x, int y)
    {
        int nx = resize(x, WIDTH);
        int ny = resize(y, HEIGHT);
        int count = 0;
        for (int ly = -1; ly <= 1; ly++)
        {
            for (int lx = -1; lx <= 1; lx++)
            {
                if (lx == 0 && ly == 0)
                    continue;
                if (this->map[resize(ny + ly, HEIGHT) * WIDTH + resize(nx + lx, WIDTH)])
                    count++;
            }
        }
        return count;
    }
    void update_map()
    {
        this->apply_updates();
        bool *new_map = new bool[WIDTH * HEIGHT];
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {

                int neighbours = this->check_neightbours(x, y);
                if ((this->map[y * WIDTH + x] && (neighbours == 2)) || neighbours == 3)
                {
                    new_map[y * WIDTH + x] = true;
                    continue;
                }

                new_map[y * WIDTH + x] = false;
            }
        }
        this->map = new_map;
    }
};

char *returnMapChar()
{
    String initialMap = "";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "-------#------------";
    initialMap += "--------#-----------";
    initialMap += "------###-----------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";
    initialMap += "--------------------";

    char *initialMapChar = new char[WIDTH * HEIGHT];
    memcpy(initialMapChar, initialMap.c_str(), WIDTH * HEIGHT);
    return initialMapChar;
}