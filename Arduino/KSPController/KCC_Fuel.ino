//KCC_Fuel _FUEL;

void KCC_Fuel::update(Telemetry* telemetry) {

  if (solid != telemetry->fuel_solid) {
    solid = telemetry->fuel_solid;
    int val = map(telemetry->fuel_solid, 0, 10, 10, 255);
    analogWrite(PIN_FUEL_SOLID, val);
  }

}
