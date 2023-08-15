#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#include <cstdio>
#define __STRICT_ANSI__
#else
#include <cstdio>
#endif

#include <SDL_render.h>
#include "SDL.h"
#include "physics.h"
#include <iostream>
#include "sdl2.h"
#include <glad/glad.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <stdlib.h>
#include <share.h>

struct Point2D {
    int32_t x;
    int32_t y;
    bool operator==(const Point2D &other) const {
        return (x == other.x && y == other.y);
    }
};

struct Line2D {
    Point2D a;
    Point2D b;

    bool operator==(const Line2D &other) const {
        return (a == other.a && b == other.b);
    }
};

int main (int argc, char *argv[]) {
    using std::cerr;
    using std::endl;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    auto sys = sdl2::make_sdlsystem(SDL_INIT_VIDEO);
    if(!sys) {
        cerr << "Error creating SDL2 system: " << SDL_GetError() << endl;
        return 1;
    }
    auto win = sdl2::make_window("Hello World!", 500, 500, 640, 480, SDL_WINDOW_OPENGL);
    if(!win) {
        cerr << "Error creating window: " << SDL_GetError() << endl;
        return 1;
    }
    SDL_GL_CreateContext(win.get());
    if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cerr << "Error loading OpenGL " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Log("Vendor: %s \n", glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s \n", glGetString(GL_RENDERER));
    SDL_Log("Version: %s \n", glGetString(GL_VERSION));

    /* Set the background black */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* Depth buffer setup */
    glClearDepth(1.0f);

    /* Enables Depth Testing */
    glEnable(GL_DEPTH_TEST);

    /* The Type Of Depth Test To Do */
    glDepthFunc(GL_LEQUAL);
    /* Set the background black */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    /* Clear The Screen And The Depth Buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);

    glBegin(GL_TRIANGLES);          /* Drawing Using Triangles */
    glVertex3f(0.0f, 1.0f, 0.0f);   /* Top */
    glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
    glVertex3f(1.0f, -1.0f, 0.0f);  /* Bottom Right */
    glEnd();                        /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glTranslatef(3.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);              /* Draw A Quad */
    glVertex3f(-1.0f, 1.0f, 0.0f);  /* Top Left */
    glVertex3f(1.0f, 1.0f, 0.0f);   /* Top Right */
    glVertex3f(1.0f, -1.0f, 0.0f);  /* Bottom Right */
    glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
    glEnd();                        /* Done Drawing The Quad */

    SDL_RenderPresent(displayRenderer);
    return 0;
}