#include "SensorVelocidad.h"
#include <Arduino.h>

void inicializarSensorVelocidad() {
  pinMode(32, INPUT); // Configura GPIO32 (A0) como entrada para el sensor de velocidad
}

float leerSensorVelocidad() {
  
  int valor = analogRead(32); // Lee el valor del potenciómetro desde SIG
  return map(valor, 0, 4095, 0, 200); // Mapea el valor a un rango de 0-200 km/h
}
