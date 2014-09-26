#include "SDIChecker.h"
#include "math.h"

void initialize_sdi_checker() {
  reset_sdi();
  prev_sdiX = 0;
  prev_sdiY = 0;
}

void update_sdi_checker() {
  if (sdi_started) {
    ++sdi_timer;
  }

  scan_sdi();

  if ((prev_sdiX * sdiX < 0 || (prev_sdiX == 0 && sdiX != 0)) ||
    (prev_sdiY * sdiY < 0 || (prev_sdiY == 0 && sdiY != 0))) {
    printf("  SDI\n");

    start_sdi();
    prev_sdi_time = sdi_timer;

    ++sdi_counter;
    sum_sdiX += sdiX;
    sum_sdiY += sdiY;

  }

  if (sdi_timer - prev_sdi_time > 60) {
    display_result();
    reset_sdi();
  }

  prev_sdiX = sdiX;
  prev_sdiY = sdiY;
}

void start_sdi() {
  if (!sdi_started) {
    sdi_started = true;
  }
}

void reset_sdi() {
  sdi_counter = 0;
  sdi_timer = 0;
  prev_sdi_time = 0;
  sdi_started = false;
}

void scan_sdi() {
  stickX = PAD_StickX(0);
  stickY = PAD_StickY(0);

  sdiX = stickX * 0.075f;
  sdiY = stickY * 0.075f;
  float dist = sqrt(sdiX * sdiX + sdiY * sdiY);

  float coefficient = 1;
  if (dist < 4.2) coefficient = 0;
  if (dist > 6) coefficient = 6 / dist;

  sdiX *= coefficient;
  sdiY *= coefficient;

  if (-1.65<= sdiX && sdiX <= 1.65) sdiX = 0;
  if (-1.65<= sdiY && sdiY <= 1.65) sdiY = 0;
}

void display_result() {
  if (prev_sdi_time == 0) return;

  float count_average = (sdi_counter - 1.0f) / prev_sdi_time;
  float distX_average = count_average * sum_sdiX / sdi_counter;
  float distY_average = count_average * sum_sdiY / sdi_counter;

  printf("  ---\n");
  printf("  Measure Time: %d\n", prev_sdi_time);
  printf("  Count: %d\n", sdi_counter);
  printf("  Distance: (%f, %f)\n", sum_sdiX, sum_sdiY);
  printf("  Count Average (count / frame): %f\n", count_average);
  printf("  Distance Average (distance / frame): (%f, %f)\n", distX_average, distY_average);
  printf("  Span Average (frame / count): %f\n", 1 / count_average);
  printf("  ---\n\n");
}
