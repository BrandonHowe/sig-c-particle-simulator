#include "raylib.h"
#include <stdlib.h>

typedef struct Particle
{
    Vector2 pos;
    Vector2 vel;
    Color color;
    float lifetime;
    bool alive;
} Particle;

#define MAX_PARTICLES 10000

Particle particles[MAX_PARTICLES];

#define TARGET_FPS 120.0f

void create_new_particle(Vector2 pos)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particles[i].alive)
        {
            particles[i].pos = pos;
            float x_vel = (float)GetRandomValue(-50, 50) * 10.0f / TARGET_FPS;
            float y_vel = (float)GetRandomValue(-50, 0) * 10.0f / TARGET_FPS;
            particles[i].vel = (Vector2){ .x = x_vel, .y = y_vel };
            particles[i].color = RAYWHITE;
            particles[i].lifetime = GetRandomValue(3, 15) / 10.0f;
            particles[i].alive = true;
            break;
        }
    }
}

void move_all_particles(float dt)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].alive)
        {
            particles[i].pos.x += particles[i].vel.x;
            particles[i].pos.y += particles[i].vel.y;
            particles[i].vel.y += 10.0f / TARGET_FPS;

            particles[i].lifetime -= dt;
            if (particles[i].lifetime <= 0)
            {
                particles[i].alive = false;
            }
        }
    }
}

int main()
{
    InitWindow(800, 600, "My Particle System");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            create_new_particle(GetMousePosition());
        }

        move_all_particles(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (particles[i].alive)
            {
                DrawCircleV(particles[i].pos, 3, particles[i].color);
            }
        }
        EndDrawing();
    }

    return 0;
}