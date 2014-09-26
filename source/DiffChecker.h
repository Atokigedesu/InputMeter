#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>

int counter;
bool started;
int buttonsDown;
signed char stickX;
signed char stickY;
unsigned char analogR;
unsigned char analogL;

void initialize_diff_checker();
void start_counter();
void reset_counter();
void update_counter();
void check_button(const int, const char*);
void update_diff_checker();
