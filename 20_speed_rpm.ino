/*
 * Speed and RPM functions
 * 
 */
 
void update_speed() {
  //update total, trip, speed
  uint32_t distance;
  uint16_t currentSpeed;
  static byte noUpdateCount;

  if (speedCount == 0 and (millis() - speedEvent) > ZEROTIME) { //no pulses for ZEROTIME ms?
    speed = 0;
  } else if ( speedCount > 15 ) { //sample enough events to increase precision
    //speed
    currentSpeed = ((speedCount * 3600000) / SPEED_IMP_PER_REV) / IMP_PER_KM / (speedEvent - speedLastEvent); //speed in kph

    //calm speed reading
    if ((abs(currentSpeed - speed) > 2) or (noUpdateCount > 10) ) {
      speed = currentSpeed;
      noUpdateCount = 0;
    } else {
      noUpdateCount++;
    }

    //distance
    distance = ((speedCount * 10000) / SPEED_IMP_PER_REV) / IMP_PER_KM; // distance travelled in decimeters
    total = total + distance;
    trip = trip + distance;

    //roll over
    if (total > ROLLOVER) {
      total = total - ROLLOVER;
    }
    if (trip > ROLLOVER) {
      trip = trip - ROLLOVER;
    }

    //prepare for next events
    speedLastEvent = speedEvent;
    speedCount = 0;
  }
}

void update_rpm() {
  //update rpm
  if ((millis() - rpmEvent) > ZEROTIME) { //no pulses for ZEROTIME ms?
    rpm = 0;
  } else if ( rpmCount > 0 ) {
    //60000ms in a minute, divided by milliseconds per revolution
    rpm = (uint16_t)((60000 * rpmCount) / ((rpmEvent - rpmLastEvent) * RPM_IMP_PER_REV ));

    //prepare for next events
    rpmLastEvent = rpmEvent;
    rpmCount = 0;
  }
}
