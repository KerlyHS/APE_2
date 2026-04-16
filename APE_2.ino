// Definir pines
const int LED_PINS[] = {2, 3, 4, 5, 6, 7};  // Pines de los LEDs
const int BOTON_PIN = 8;  // Pin del botón
int patronActual = 0;  // Patrón actual

void setup() {
  // Configurar los pines de los LEDs como salida
  for (int i = 0; i < 6; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  // Configurar el pin del botón como entrada
  pinMode(BOTON_PIN, INPUT);
}

void loop() {
  leerBoton();  // Llamar a la función para leer el botón

  switch (patronActual) {  // Según el patrón actual, ejecutar una función
    case 0:
      patronSecuencia();
      break;
    case 1:
      patronPersecucion();
      break;
    case 2:
      patronParpadeo();
      break;
    case 3:
      patronAleatorio();
      break;
    case 4:
      patronOnda();
      break;
    default:
      break;
  }
}

// Función para leer el botón y cambiar el patrón aleatorio
void leerBoton() {
  if (digitalRead(BOTON_PIN) == HIGH) {  // Si el botón está presionado
    patronActual = random(0, 5);  // Generar un número aleatorio entre 0 y 4
  }
}

// Función del patrón de secuencia (luces consecutivas de izquierda a derecha)
void patronSecuencia() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], HIGH);  // Enciende el LED en el pin actual
    delay(200);  // Esperar 200 ms entre luces
    digitalWrite(LED_PINS[i], LOW);   // Apagar el LED
  }
}

// Función de persecución (luces en persecución de derecha a izquierda)
void patronPersecucion() {
  for (int i = 5; i >= 0; i--) {
    digitalWrite(LED_PINS[i], HIGH);  // Enciende el LED en el pin actual
    digitalWrite(LED_PINS[i], LOW);   // Apagar el LED
  }
}

// Función de parpadeo (todos los LEDs se encienden y apagan juntos)
void patronParpadeo() {
  static unsigned long tiempoUltimoCambio = 0;
  const long intervaloCambio = 500;  // Intervalo de parpadeo de todos los LEDs

  // Solo cambia el estado si ha pasado el intervalo
  if (millis() - tiempoUltimoCambio >= intervaloCambio) {
    // Encender todos los LEDs
    for (int i = 0; i < 6; i++) {
      digitalWrite(LED_PINS[i], HIGH);  // Enciende todos los LEDs
    }

    // Esperar el intervalo para apagarlos
    for (int i = 0; i < 6; i++) {
      digitalWrite(LED_PINS[i], LOW);  // Apaga todos los LEDs
    }

    tiempoUltimoCambio = millis();  // Actualiza el último tiempo de cambio
  }
}

// Función aleatoria (luces que encienden y apagan rápidamente de forma aleatoria)
void patronAleatorio() {
  static unsigned long tiempoUltimoCambio = 0;
  const long intervaloCambio = 100;  // Tiempo entre cada cambio

  // Solo cambia el estado si ha pasado el intervalo
  if (millis() - tiempoUltimoCambio >= intervaloCambio) {
    for (int i = 0; i < 6; i++) {
      int estado = random(0, 2);  // Genera un valor aleatorio 0 o 1
      digitalWrite(LED_PINS[i], estado);  // Enciende o apaga el LED
    }
    tiempoUltimoCambio = millis();  // Actualiza el tiempo del último cambio
  } 
}


// Función de onda (luces que se encienden y apagan de forma onda)
void patronOnda() {
  // De izquierda a derecha
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], HIGH);  // Enciende el LED
    digitalWrite(LED_PINS[i], LOW);   // Apaga el LED
  }
  // De derecha a izquierda
  for (int i = 5; i >= 0; i--) {
    digitalWrite(LED_PINS[i], HIGH);  // Enciende el LED
    digitalWrite(LED_PINS[i], LOW);   // Apaga el LED
  }
}