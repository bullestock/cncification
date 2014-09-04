// Stepper controller for router


// Pin definitions
int N_ENABLE = 9;
int STEP1 = 8;
int DIR1 = 7;
int STEP3 = 6;
int DIR3 = 5;
int N_RESET = 4;
int STEP2 = 3;
int DIR2 = 2;
int INTERNAL_LED = 13;
int ROTARY_SWITCH = A3;
int X_SWITCH = A2;
int Y_SWITCH = A1;
int ROTARY_SWITCH_STEP = 1023/11;

// When toggle switch value is below this, we assume it is in the 'down' position
int ANALOG_LOW = 400;
// When toggle switch value is above this, we assume it is in the 'up' position
int ANALOG_HIGH = 600;

// After this number of ms where no switch is active, disable the stepper drivers
int MAX_IDLE_TIME = 5000;

void setup()
{                
    pinMode(INTERNAL_LED, OUTPUT); 
    pinMode(N_ENABLE, OUTPUT);
    pinMode(N_RESET, OUTPUT);
    pinMode(STEP1, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(STEP2, OUTPUT);
    pinMode(DIR2, OUTPUT);
    pinMode(STEP3, OUTPUT);
    pinMode(DIR3, OUTPUT);
    pinMode(ROTARY_SWITCH, INPUT);  
    pinMode(X_SWITCH, INPUT);  
    pinMode(Y_SWITCH, INPUT);  

    digitalWrite(N_ENABLE, HIGH);
    digitalWrite(N_RESET, LOW);
    delay(10);
    digitalWrite(N_RESET, HIGH);
    digitalWrite(N_ENABLE, LOW);

    Serial.begin(9600);
    Serial.println("Router driver ready");
}

void doDelay(double us)
{
    while (us > 10000)
    {
        delay(10);
        us -= 10000;
    }
    delayMicroseconds(us);
}

int n = 0;
int ledState = LOW;
int idleTime = 0;
unsigned long lastActiveTick = 0;

void loop()
{
    // Rotary switch: 0, 93, 186, ..., 1023
    // Max rate: 100 steps/second -> total delay = 10 ms
    // Max value of del = 5000
    // Min rate: 1 step/second -> total delay = 1000 ms
    // Min value of del = 500000

    // switchPosition will be 0-11
    int switchPosition = (analogRead(ROTARY_SWITCH) + ROTARY_SWITCH_STEP/2)/ROTARY_SWITCH_STEP;
    double del = 600 + pow(2.5, switchPosition);
    int x = analogRead(X_SWITCH);
    int y = analogRead(Y_SWITCH);
    if (n == 0)
    {
        digitalWrite(INTERNAL_LED, ledState);
        ledState = !ledState;
#if 0
        Serial.print("R ");
        Serial.print(switchPosition);
        Serial.print(" del ");
        Serial.print(del);
        Serial.print(" X ");
        Serial.print(x);
        Serial.print(" Y ");
        Serial.println(y);
        delay(50);
#endif
    }
    ++n;
    if (n > 500)
        n = 0;
    if ((x < ANALOG_LOW) || (x > ANALOG_HIGH))
    {
        digitalWrite(N_RESET, HIGH);
        digitalWrite(N_ENABLE, LOW);
        digitalWrite(DIR1, x < ANALOG_LOW);
        digitalWrite(STEP1, HIGH);
        lastActiveTick = millis();
    }
    if ((y < ANALOG_LOW) || (y > ANALOG_HIGH))
    {
        digitalWrite(N_RESET, HIGH);
        digitalWrite(N_ENABLE, LOW);
        digitalWrite(DIR2, y < ANALOG_LOW);
        digitalWrite(STEP2, HIGH);
        lastActiveTick = millis();
    }
    unsigned long idleTime = millis() - lastActiveTick;
    if (++idleTime > MAX_IDLE_TIME)
    {
        digitalWrite(N_ENABLE, HIGH);
        digitalWrite(N_RESET, LOW);
    }
    
    doDelay(del);

    if ((x < ANALOG_LOW) || (x > ANALOG_HIGH))
        digitalWrite(STEP1, LOW); 

    if ((y < ANALOG_LOW) || (y > ANALOG_HIGH))
        digitalWrite(STEP2, LOW); 

    doDelay(del);
}
