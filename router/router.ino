// Stepper controller for router

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

int ANALOG_LOW = 400;
int ANALOG_HIGH = 600;

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

void loop()
{
    // Rotary switch: 0, 93, 186, ..., 1023
    // Max rate: 100 steps/second -> total delay = 10 ms
    // Max value of del = 5000
    // Min rate: 1 step/second -> total delay = 1000 ms
    // Min value of del = 500000

    // switchPosition will be 0-11
    int switchPosition = (analogRead(ROTARY_SWITCH) + ROTARY_SWITCH_STEP/2)/ROTARY_SWITCH_STEP;
    double del = 5000 + pow(3.2938, switchPosition);
    int x = analogRead(X_SWITCH);
    if (n == 0)
    {
        Serial.print("R ");
        Serial.print(switchPosition);
        Serial.print(" del ");
        Serial.print(del);
        Serial.print(" X ");
        Serial.println(x);
    }
    ++n;
    if (n > 1000)
        n = 0;
    if ((x < ANALOG_LOW) || (x > ANALOG_HIGH))
    {
        digitalWrite(DIR1, x < ANALOG_LOW);
        digitalWrite(STEP1, HIGH);
    }
    int y = analogRead(Y_SWITCH);
    if ((y < ANALOG_LOW) || (y > ANALOG_HIGH))
    {
        digitalWrite(DIR2, y < ANALOG_LOW);
        digitalWrite(STEP2, HIGH);
    }

    if ((x < ANALOG_LOW) || (x > ANALOG_HIGH) ||
        (y < ANALOG_LOW) || (y > ANALOG_HIGH))
        digitalWrite(INTERNAL_LED, HIGH);
    
    doDelay(del);

    if ((x < ANALOG_LOW) || (x > ANALOG_HIGH))
        digitalWrite(STEP1, LOW); 

    if ((y < ANALOG_LOW) || (y > ANALOG_HIGH))
        digitalWrite(STEP2, LOW); 

    if ((x < ANALOG_LOW) || (x > ANALOG_HIGH) ||
        (y < ANALOG_LOW) || (y > ANALOG_HIGH))
        digitalWrite(INTERNAL_LED, LOW);

    doDelay(del);
}
