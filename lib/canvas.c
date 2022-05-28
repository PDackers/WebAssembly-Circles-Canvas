#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Number of circles to create.
#define NUM_CIRCLES 120

// Circle Struct.
struct Circle {
    int x;  // X coordinate.
    int y;  // Y coordinate.
    int r;  // Circle radius.
    int cr; // Color red.
    int cg; // Color green.
    int cb; // Color blue.
};

// Circle Anitmation Data Struct.
struct CircleAnimationData {
    int x;  // X coordinate.
    int y;  // Y coordinate.
    int r;  // Circle radius.
    int xv; // X axis velocity.
    int yv; // Y axis velocity.
    int xd; // X axis direction. (1 = forward, 0 = backwards).
    int xy; // Y axis direction. (1 = forward, 0 = backwards).
};

// Circles variable.
struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

// Random number generator.
int getRand(int max) {
    return (rand() % max);
}

// Init circle data and start render - JS.
int main() {
    // Seed random number generator.
    srand(time(NULL));

    // Create circles.
    for (int i = 0; i < NUM_CIRCLES; i++) {

        // Radius.
        int radius = getRand(50);

        // Coordinates.
        int x = getRand(1000) + radius;
        int y = getRand(1000) + radius;

        // Fill animation data struct - [i].
        animationData[i].x = x;
        animationData[i].y = y;
        animationData[i].r = radius;
        animationData[i].xv = getRand(10);
        animationData[i].yv = getRand(10);
        animationData[i].xd = 1;
        animationData[i].xy = 1;

        // Fill circle struct - [i].
        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radius;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
    }

    // Start JS rendering.
    EM_ASM({ render($0, $1); }, NUM_CIRCLES * 6, 6); // 6 being the length of the Circle struct.
}

// Return animated circles to JS.
struct Circle * getCircles(int canvasWidth, int canvasHeight) {
    // Update circle data.
    for (int i = 0; i < NUM_CIRCLES; i++) {

        // Collission right-side. Set X axis direction backwards.
        if ((animationData[i].x + animationData[i].r) >= canvasWidth) {
            animationData[i].xd = 0;
        }

        // Collission left-side. Set X axis direction backwards.
        if ((animationData[i].x - animationData[i].r) <= 0) {
            animationData[i].xd = 1;
        }

        // Collission top-side. Set y axis direction forwards.
        if ((animationData[i].y - animationData[i].r) <= 0) {
            animationData[i].xy = 1;
        }

        // Collission bottom-side. Set y axis direction backwards.
        if ((animationData[i].y + animationData[i].r) >= canvasHeight) {
            animationData[i].xy = 0;
        }

        // Move circle in specified direction.
        if (animationData[i].xd == 1) {
            animationData[i].x += animationData[i].xv;
        } else {
            animationData[i].x -= animationData[i].xv;
        }
        if (animationData[i].xy == 1) {
            animationData[i].y += animationData[i].yv;
        } else {
            animationData[i].y -= animationData[i].yv;
        }

        // Update matching circle.
        circles[i].x = animationData[i].x;
        circles[i].y = animationData[i].y;
    }

    // Return updated circles.
    return circles;
}
