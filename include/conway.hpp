
#include <stdlib.h>
#include <Arduino.h>
#define WIDTH 20
#define HEIGHT 20

int resize(int x, int max_value){
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
    bool updating=false;
    // #  or 0
    Conway(char *initialMap)
    {
        this->map = new bool[WIDTH * HEIGHT];
        // so aqui tenemos esta parte donde copia una base :D
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            this->map[i] = initialMap[i] == '#';
        }
    }
    //** esto va a ser usado desde el servidor :D */
    void update_slice(int x, int y, bool is_alive)
    {
        int nx = resize(x, WIDTH);
        int ny = resize(y, HEIGHT);
        map[ny * WIDTH + nx] = is_alive;
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
        bool *new_map=new bool[WIDTH*HEIGHT];
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
        this->map=new_map;
    }
};

char *returnMapChar()
{
    String initialMap = 
                  "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "0000000#000000000000";
    initialMap += "00000000#00000000000";
    initialMap += "000000###00000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";
    initialMap += "00000000000000000000";

    char *initialMapChar = new char[WIDTH * HEIGHT];
    memcpy(initialMapChar, initialMap.c_str(), WIDTH * HEIGHT);
    return initialMapChar;
}