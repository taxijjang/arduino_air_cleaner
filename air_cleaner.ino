#define fadePin 9

int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
float ugm3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(fadePin, OUTPUT);
  starttime = millis();
}

void loop() {
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;
  if ((millis() - starttime) > sampletime_ms)
  {
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0);
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
    ugm3 = concentration * 100 / 13000;
    Serial.print("lowpuleoccupancy=");
    Serial.println(lowpulseoccupancy);
    Serial.print("ratio = ");
    Serial.print(ratio);
    Serial.print("concentration = ");
    Serial.print(concentration);
    Serial.println(" pcs/0.01cf");
    Serial.print(ugm3);
    Serial.println(" u/m3 PM1.0");
    Serial.println(" ================== ");
    lowpulseoccupancy = 0;
    starttime = millis();

    if (int(ugm3) > 25){
      Serial.print("pan on");
      analogWrite(fadePin, 255);
    }
    else{
      Serial.print("pan off");
      analogWrite(fadePin, 0);
    }
  }
}
