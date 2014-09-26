#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>

int sdi_counter;
int sdi_timer;
int prev_sdi_time;
bool sdi_started;
signed char stickX;
signed char stickY;
float sdiX;
float sdiY;
float prev_sdiX;
float prev_sdiY;
float sum_sdiX;
float sum_sdiY;

void initialize_sdi_checker();
void update_sdi_checker();
void start_sdi();
void reset_sdi();
void scan_sdi();
void display_result();
