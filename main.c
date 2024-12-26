#include "window.h"

Window window;
Player player = {70, -110, 20, 0, 0};

int main(void)
{    
    windowInit(&window);
    while (window.isRunning) {
       renderShow(&window, &player);
       windowEvents(&window, &player); 
    }
    windowDestroy(&window);
    return 0;
}
