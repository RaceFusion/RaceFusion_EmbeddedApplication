#include "SensorPresion.h"
#include <Arduino.h>

void inicializarSensorPresion() {
  pinMode(34, INPUT); // Configura GPIO34 como entrada para el sensor de presión de llantas
}

float leerSensorPresion() {
  int valor = analogRead(34); // Lee el valor del potenciómetro conectado a GPIO34
  return map(valor, 0, 4095, 0, 50); // Mapea el valor a un rango de 0-50 PSI
}
