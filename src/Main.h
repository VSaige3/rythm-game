// Main.h

#ifndef NoteManager_h
#include "NoteManager.h"
#define NoteManager_h
#endif

#ifndef ImageDrawer_h
#define ImageDrawer_h
#include "ImageDrawer.h"
#endif

#include <time.h>
#include <stdio.h>
#include <string.h>

#define CONFIG_PATH "../config/"
#define PREFERENCES_FILE_NAME "preferences.json"
#define RESOURCES_PATH "../resources/"
#define DATA_PATH "../data/"

#define TIMER_OFF 0
#define TIMER_ON 1
#define TIMER_HALF_SPEED 2
#define TIMER_RESET_FRAMES 2

/**
 * Contains the main file with the mechanics and stuff
 * 
 * handles drawing, loading, setting up menus, etc.
 * 
 * mechanics and stuff
 * 
 */

struct {
    int window_width, window_height;
} initial_settings;

int main(int argc, char **argv);

void timer(int i);

void display();

void load();
void unload();
void load_settings();

void reshape(int w, int h);

void mouse_drag(int x, int y);
void keyboard(unsigned char key, int x, int y);
void special_keyboard(int key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void special_keyboard_up(int key, int x, int y);
void mouse_move(int x, int y);
void mouse_click(int button, int state, int x, int y);
void setupKeyboard();