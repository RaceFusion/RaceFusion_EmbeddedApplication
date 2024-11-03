#include "SensorTemperatura.h"
#include <Arduino.h>

void inicializarSensorTemperatura() {
  pinMode(35, INPUT); // Configura GPIO35 como entrada para el sensor de temperatura
}

float leerSensorTemperatura() {
  
  int valor = analogRead(35); // Lee el valor del potenciómetro conectado a GPIO35
  return map(valor, 0, 4095, -40, 125); // Mapea el valor a un rango de -40 a 125°C (rango típico de temperatura)
}
