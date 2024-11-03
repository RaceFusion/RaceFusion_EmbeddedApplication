#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include "SensorVelocidad.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "SensorCombustible.h"

// Configuración de la pantalla LCD 20x4 en la dirección I2C 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Credenciales de la red Wi-Fi
const char* ssid = "Wokwi-GUEST";  
const char* password = "";          

// Dirección del servidor Flask (cambia la IP y el puerto según corresponda)
const char* serverUrl = "https://edge-r47g.onrender.com/datos";

// ID único del dispositivo IoT
const char* deviceId = "DispositivoIoT_001";

void setup() {
  Serial.begin(115200);
  
  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a Wi-Fi...");
  }
  Serial.println("Conectado a Wi-Fi");

  // Inicialización de los sensores
  inicializarSensorVelocidad();
  inicializarSensorTemperatura();
  inicializarSensorPresion();
  inicializarSensorCombustible();

  // Inicialización de la pantalla LCD
  lcd.init();
  lcd.backlight(); // Activa la retroiluminación
}

void loop() {
  // Lee los valores de los sensores como enteros
  int velocidad = static_cast<int>(leerSensorVelocidad());
  int temperatura = static_cast<int>(leerSensorTemperatura());
  int presion = static_cast<int>(leerSensorPresion());
  int combustible = static_cast<int>(leerSensorCombustible());

  // Mostrar en la pantalla LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Velocidad:");
  lcd.print(velocidad);
  lcd.print(" km/h");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperatura);
  lcd.print(" C");

  lcd.setCursor(0, 2);
  lcd.print("Presion:");
  lcd.print(presion);
  lcd.print(" PSI");

  lcd.setCursor(0, 3);
  lcd.print("Combustible:");
  lcd.print(combustible);
  lcd.print(" %");

  if (WiFi.status() == WL_CONNECTED) {
    sendSensorData(velocidad, temperatura, presion, combustible);
  } else {
    Serial.println("WiFi desconectado");
  }

  delay(5000); // Espera 5 segundos antes de la siguiente actualización
}

void sendSensorData(int velocidad, int temperatura, int presion, int combustible) {
  HTTPClient http;
  Serial.print("Conectando a la URL: ");
  Serial.println(serverUrl);
  
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["device_id"] = deviceId;
  jsonDoc["velocidad"] = velocidad;
  jsonDoc["temperatura"] = temperatura;
  jsonDoc["presion"] = presion;
  jsonDoc["combustible"] = combustible;

  String requestBody;
  serializeJson(jsonDoc, requestBody);
  
  Serial.print("Datos enviados: ");
  Serial.println(requestBody);

  int httpResponseCode = http.POST(requestBody);

  // Verificar el código de respuesta
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
    Serial.println("Respuesta del servidor: ");
    Serial.println(response);
  } else {
    Serial.print("Error en la solicitud: ");
    Serial.println(httpResponseCode);
    Serial.println("Asegúrate de que el servidor esté activo y la URL sea correcta.");
  }

  http.end(); // Finalizar la conexión HTTP
}
