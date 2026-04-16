// Definir pines
const int LED_PINS[] = {2, 3, 4, 5, 6, 7};  // Pines de los LEDs
const int BOTON_PIN = 8;  // Pin del botón
int patronActual = 0;  // Patrón actual

// Variables de tiempo
unsigned long tiempoAnterior = 0;  
const long intervaloSecuencia = 200;  // Intervalo de tiempo para la secuencia
const long intervaloBoton = 500;     // Intervalo de tiempo para evitar lecturas múltiples del botón

void setup() {
  // Configurar los pines de los LEDs como salida
  for (int i = 0; i < 6; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  // Configurar el pin del botón como entrada
  pinMode(BOTON_PIN, INPUT);
}

void loop() {
  leerBoton();  

  switch (patronActual) {  
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
  if (digitalRead(BOTON_PIN) == HIGH && (millis() - tiempoAnterior) > intervaloBoton) {  
    patronActual = random(0, 5);  // Generar un número aleatorio entre 0 y 4
    tiempoAnterior = millis();  // Actualizar el tiempo anterior
  }
}

// Función del patrón de secuencia (luces consecutivas de izquierda a derecha)
void patronSecuencia() {
  static unsigned long lastTime = 0;
  static int ledIndex = 0;

  if (millis() - lastTime >= intervaloSecuencia) {
    digitalWrite(LED_PINS[ledIndex], HIGH);  // Enciende el LED en el pin actual
    digitalWrite(LED_PINS[ledIndex], LOW);   // Apaga el LED
    ledIndex = (ledIndex + 1) % 6;  // Pasar al siguiente LED, ciclo de 0 a 5
    lastTime = millis();  // Actualizar el tiempo de la última acción
  }
}

// Función de persecución (luces en persecución de derecha a izquierda)
void patronPersecucion() {
  static unsigned long lastTime = 0;
  static int ledIndex = 5;

  if (millis() - lastTime >= intervaloSecuencia) {
    digitalWrite(LED_PINS[ledIndex], HIGH);  // Enciende el LED en el pin actual
    digitalWrite(LED_PINS[ledIndex], LOW);   // Apaga el LED
    ledIndex = (ledIndex - 1 + 6) % 6;  // Pasar al LED anterior, ciclo de 5 a 0
    lastTime = millis();  // Actualizar el tiempo de la última acción
  }
}

// Función de parpadeo (luces que parpadean al azar)
void patronParpadeo() {
  static unsigned long lastTime = 0;
  static int ledIndex = 0;

  if (millis() - lastTime >= intervaloSecuencia) {
    int estado = random(0, 2);  // Genera un valor aleatorio 0 o 1
    digitalWrite(LED_PINS[ledIndex], estado);  // Enciende o apaga el LED
    ledIndex = (ledIndex + 1) % 6;  // Pasar al siguiente LED
    lastTime = millis();  // Actualizar el tiempo de la última acción
  }
}

// Función aleatoria (luces que encienden de forma aleatoria)
void patronAleatorio() {
  static unsigned long lastTime = 0;
  static int ledIndex = 0;

  if (millis() - lastTime >= intervaloSecuencia) {
    int estado = random(0, 2);  // Genera un valor aleatorio 0 o 1
    digitalWrite(LED_PINS[ledIndex], estado);  // Enciende o apaga el LED
    ledIndex = (ledIndex + 1) % 6;  // Pasar al siguiente LED
    lastTime = millis();  // Actualizar el tiempo de la última acción
  }
}

// Función de onda (luces que se encienden y apagan de forma onda)
void patronOnda() {
  static unsigned long lastTime = 0;
  static int ledIndex = 0;
  static bool direccion = true; // Indica la dirección de la onda (true = izquierda a derecha, false = derecha a izquierda)

  if (millis() - lastTime >= intervaloSecuencia) {
    digitalWrite(LED_PINS[ledIndex], HIGH);  // Enciende el LED
    digitalWrite(LED_PINS[ledIndex], LOW);   // Apaga el LED

    if (direccion) {
      ledIndex++;
      if (ledIndex == 6) {
        direccion = false;
        ledIndex = 5;
      }
    } else {
      ledIndex--;
      if (ledIndex == -1) {
        direccion = true;
        ledIndex = 0;
      }
    }

    lastTime = millis();  // Actualizar el tiempo 
  }
}
