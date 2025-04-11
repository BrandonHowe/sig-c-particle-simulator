#include "raylib.h"
#include <stdlib.h>  // for rand()

#define MAX_PARTICLES 1000000

typedef struct Particle {
    Vector2 position;
    Vector2 velocity;
    float lifetime;
    Color color;
    bool active;
} Particle;

Particle particles[MAX_PARTICLES];

// Initialize a particle at a given position
void spawn_particle(Vector2 pos)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particles[i].active)
        {
            particles[i].position = pos;
            // x velocity is any value with 1 decimal place between -5 and 5 (e.g. -3.8)
            // y velocity is any value with 1 decimal place between -5 and 0 (e.g. -2.0)
            particles[i].velocity = (Vector2){ (float)(rand() % 100 - 50) / 10.0f, (float)(-rand() % 50) / 10.0f };
            particles[i].lifetime = 1.0f + (rand() % 100) / 100.0f;
            particles[i].color = RAYWHITE;
            particles[i].active = true;
            break;
        }
    }
}

void update_particles(float dt)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].active)
        {
            particles[i].position.x += particles[i].velocity.x;
            particles[i].position.y += particles[i].velocity.y;
            particles[i].velocity.y += 0.05;
            particles[i].lifetime -= dt;

            if (particles[i].lifetime <= 0)
            {
                particles[i].active = false;
            }
        }
    }
}

void draw_particles() {
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].active)
        {
            DrawCircleV(particles[i].position, 3.0f, particles[i].color);
        }
    }
}

int main() {
    InitWindow(800, 600, "Particle System Starter");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 5; i++) {
                spawn_particle(GetMousePosition());
            }
        }

        update_particles(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        draw_particles();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
