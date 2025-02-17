#include <stdlib.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#define WIDTH 20
#define HEIGHT 20

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
    bool map[WIDTH * HEIGHT];
    bool update = false;
    // #  or 0
    Conway(char *initialMap)
    {
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            this->map[i] = initialMap[i] == '#';
        }
    }

    void update_cell(int x, bool is_alive)
    {
        if (update)
            return;
        int nx = resize(x, WIDTH * HEIGHT);
        this->map[nx] = is_alive;
    }

    String map_to_string()
    {
        String result;
        result.reserve(WIDTH * HEIGHT);  // Reservar espacio para evitar realocaciones
        
        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            result += this->map[i] ? '#' : '-';
        }
        
        return result;
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
    void update_map(AsyncWebSocket& ws)
    {
        static bool new_map[WIDTH * HEIGHT];
        this->update = true;
        
        if (ws.count() > 0)
        {
            ws.textAll("ut");
        }

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int neighbours = this->check_neightbours(x, y);
                bool is_alive = this->map[y * WIDTH + x];
                new_map[y * WIDTH + x] = (is_alive && neighbours == 2) || neighbours == 3;
            }
        }
        
        memcpy(this->map, new_map, WIDTH * HEIGHT * sizeof(bool));
        this->update = false;
        
        if (ws.count() > 0)
        {
            ws.textAll("uf");
        }
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