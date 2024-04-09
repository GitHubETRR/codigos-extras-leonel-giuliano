#define I_PIN0 1        /* Entrada de la señal */
#define O_PIN0 2        /* Salida */

#define READ_I_PIN0  digitalRead(I_PIN0) /* Valor digital de la entrada */

#define LED_PRESS 3     /* Led que indica si se presiona el botón */
#define LED_RELEASE 4   /* Led que indica si se soltó el botón */

#define DELAY 40        /* Retardo para considerar la señal */

long time;              /* Tiempo desde que se prendió el Arduino */

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING,
}debounceState_t;

debounceState_t buttonState;

void debounceFSM_init();	// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
					        // transición de estados y actualizar las salidas
void buttonPressed();		// debe invertir el estado del LED1
void buttonReleased();		// debe invertir el estado del LED2



void setup() {
    debounceFSM_init();
}

void loop() {

}



void debounceFSM_init() {	// debe cargar el estado inicial
    buttonState = BUTTON_UP;

    pinMode(I_PIN0, INPUT);

    pinMode(O_PIN0, OUTPUT);
    pinMode(LED_PRESS, OUTPUT);
    pinMode(LED_RELEASE, OUTPUT);
}

/* 
    Debe leer las entradas, resolver la lógica de
    transición de estados y actualizar las salidas
*/
void debounceFSM_update() {
    switch (buttonState) {
        
    case BUTTON_UP:
        if(!READ_I_PIN0) break;

        buttonState = BUTTON_FALLING;
        time = millis();    /* Inicia un tiempo para comparar según el DELAY */

        break;

    case BUTTON_FALLING:
        if(millis() - time <= DELAY) break; /* No hace nada si es menor al DELAY */

        buttonState = (READ_I_PIN0) ? BUTTON_DOWN : BUTTON_UP;
        /* En caso de que siga apretado, avanza. Sino, retrocede */

        break;

    case BUTTON_DOWN:
        if(READ_I_PIN0) break;

        buttonState = BUTTON_RAISING;
        time = millis();    /* Inicia un tiempo para comparar según el DELAY */

        break;

    case BUTTON_RAISING:
        if(millis() - time <= DELAY) break; /* No hace nada si es menor al DELAY */

        buttonState = (READ_I_PIN0) ? BUTTON_DOWN : BUTTON_UP;
        /* En caso de que no se aprete, vuelve al estado inicial. Sino, retrocede */
    
    default:
        break;
    }
}

void buttonPressed() {		// debe invertir el estado del LED1
    digitalWrite(LED_PRESS, !digitalRead(LED_PRESS));
}

void buttonReleased() {		// debe invertir el estado del LED2
    digitalWrite(LED_RELEASE, !digitalRead(LED_RELEASE));
}