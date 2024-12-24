#include "window.h"

Window window;

int main(void)
{    
    windowInit(&window);
    while (window.isRunning) {
        windowEvents(&window);
    }
    windowDestroy(&window);
    return 0;
}
