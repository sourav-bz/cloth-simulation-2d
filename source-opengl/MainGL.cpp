#include <iostream>
#include <cmath>
#include "ApplicationGL.h"

int main(int argc, char* args[])
{
    ApplicationGL app;

    app.Setup(1200, 320, 10);

    while(app.IsRunning()) 
    {
        app.Input();
        app.Update();
        app.Render();
    }

    app.Destroy();

    return 0;
}
