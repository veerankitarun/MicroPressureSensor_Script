#include<Wire.h>
#include <SparkFun_MicroPressure.h>

SparkFun_MicroPressure mpr;

const float OFFSET_PSI = 13.74; // Offset value to calibrate 13.74

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if(!mpr.begin()) {
    Serial.println("Cannot connect to MicroPressure sensor.");
    while(1);
  }
}

void loop() {
  float pressure_psi = mpr.readPressure(PSI); // Reading in PSI

  float adjusted_pressure_psi = pressure_psi - OFFSET_PSI; // Apply the offset

  // Convert adjusted PSI to mbar
  float pressure_mbar = adjusted_pressure_psi * 68.9476;

  // Check for applied pressure and display in mbar
  if (pressure_psi > OFFSET_PSI) {
    Serial.print("Pressure (mbar): ");
    Serial.println(pressure_mbar, 2); // Display to 2 decimal places
  } else {
    Serial.println("No pressure applied");
  }

  delay(500);
}
