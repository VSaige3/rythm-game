#ifndef Main_h
#include "Main.h"
#define Main_h
#endif

#define get_millis() time(NULL) * 1000;

// -- VARS --
float mouse_x, mouse_y;
bool mouse_dragged;
float mouse_drag_origin_x, mouse_drag_origin_y;

float window_width, window_height;

int frame;
int i=0;
bool on = false;
int fps = 60;
float float_fps = 0.0f;
long long real_fps = 0L;
long long avg_fps = 0L;
long long c_millis = 0L, p_millis = 0L;

struct cached_img test_img;



// (p(n-1)+a)/n = (pn-p+a)/n = p-(p+a)/n
// will fill in later
// handles all gameplay calculations
void timer(int value) {
    i++;
    p_millis = c_millis;
    c_millis = get_millis();
    real_fps = 1000L / (c_millis-p_millis);
    avg_fps = ((avg_fps*(i-1)+real_fps)/i);
    if (value == TIMER_ON) {
        if (!on) {
            frame = 0; 
            i = 0;
            on = true;
        }
        frame += 1;
    } else if (value == TIMER_RESET_FRAMES){
        frame = 0; 
        i = 0;
    } else if (value == TIMER_OFF) {
        on = false;
    }

    glutPostRedisplay();
    float_fps = (int)round(1000/60);
    glutTimerFunc(float_fps, timer, (int)TIMER_ON); // 60 FPS
}

float max = 500.0f;
float imgscale = 4.0f;
char str[40];
// draws all elements in the drawableBuffer
void display() {
    // will change this when the drawing buffer is implemented    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    sprintf(str, "%d", real_fps);
    output(-1.0f, 0.9f, 1.0f, 1.0f, 0.0f, GLUT_BITMAP_9_BY_15, str);
    sprintf(str, "%d", avg_fps);
    output(-1.0f, 0.8f, 1.0f, 1.0f, 0.0f, GLUT_BITMAP_9_BY_15, str);
    
    // center_cached_img(test_img, mouse_x, mouse_y, imgscale, imgscale, window_height, window_width);

    glFlush();  // Render now
}

void reshape(int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0,0,width,height);
}

void load() {}
void unload() {}
void load_settings() {
    initial_settings.window_height = 100;
    initial_settings.window_width = 100;
}

int main(int argc, char **argv) {

    // load stuff
    load_settings();

    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("Puzzle Game"); // Create a window with the given title
    glutInitWindowSize(initial_settings.window_width, initial_settings.window_height);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    // glutTimerFunc((int)round(1000/60), timer, (int)TIMER_ON); // 60 FPS
    glutCloseFunc(unload);
    glutReshapeFunc(reshape);

    
    c_millis = get_millis();

    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}