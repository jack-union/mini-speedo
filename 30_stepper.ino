/*
 * Stepper motor functions
 * 
 */
 
void reset_stepper() {
  stepper.zero(); //Initialize stepper at 0 location
  if (SWEEP_AT_START) {
    stepper.setPosition(STEPS - 1);
    stepper.updateBlocking();
    delay (500);
    stepper.setPosition(0);
    stepper.updateBlocking();
  }
}

void do_stepper() {
  uint16_t pos;

  pos = (uint32_t)speed * STEPS / SPEEDO_RANGE;
  if (pos >= STEPS) {
    stepper.setPosition(STEPS - 1);
  } else {
    stepper.setPosition(pos);
  }
}
