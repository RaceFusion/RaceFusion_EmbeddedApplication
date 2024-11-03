#include "SensorCombustible.h"
#include <Arduino.h>

void inicializarSensorCombustible() {
  pinMode(33, INPUT); // Configura GPIO33 como entrada para el sensor de combustible  
}

float leerSensorCombustible() {
  int valor = analogRead(33); // Lee el valor del potenciómetro conectado a GPIO33
  return map(valor, 0, 4095, 0, 100); // Mapea el valor a un rango de 0-100% de combustible
}
