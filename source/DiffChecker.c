#include "DiffChecker.h"

void initialize_diff_checker() {
  reset_counter();

  printf("  InputDiff -- Program to count how many frames you input between keys.\n");
  printf("  usage: START to reset\n");
}

void start_counter() {
  if (!started) {
    started = true;
    printf("  Button pressed. Start counter.\n");
  }
}

void reset_counter() {
  counter = 0;
  started = false;
  printf("  START pressed. Reset counter.\n");
}

void check_button(const int button_id, const char* button_name) {
  if (buttonsDown & button_id) {
    printf("  %s: %d\n", button_name, counter);
  }
}

void update_diff_checker() {

  if (started) {
    ++counter;
  }

  buttonsDown = PAD_ButtonsDown(0);
  stickX = PAD_StickX(0);
  stickY = PAD_StickY(0);
  analogR = PAD_TriggerR(0);
  analogL = PAD_TriggerL(0);

  if (buttonsDown != 0 && buttonsDown != PAD_BUTTON_START) {
    start_counter();
  }

  // buttons
  check_button(PAD_BUTTON_A, "A");
  check_button(PAD_BUTTON_B, "B");
  check_button(PAD_BUTTON_X, "X");
  check_button(PAD_BUTTON_Y, "Y");
  check_button(PAD_TRIGGER_Z, "Z");
  check_button(PAD_TRIGGER_R, "R");
  check_button(PAD_TRIGGER_L, "L");
  check_button(PAD_BUTTON_LEFT, "LEFT");
  check_button(PAD_BUTTON_RIGHT, "RIGHT");
  check_button(PAD_BUTTON_DOWN, "DOWN");
  check_button(PAD_BUTTON_UP, "UP");

  // LR : < 74
  if (analogR >= 74) {
    printf("  R (analog %d): %d\n", analogR, counter);
  }
  if (analogL >= 74) {
    printf("  L (analog %d): %d\n", analogL, counter);
  }

  if (buttonsDown & PAD_BUTTON_START) {
    reset_counter();
  }
}
