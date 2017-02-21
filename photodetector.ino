const int SENSOR = A0;

int level = 0;
int average = 0;
int count = 0;
int total = 0;

void setup() {
  pinMode(SENSOR, INPUT);
 
  // set up serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ready to go...");
}

void loop() {
  level = analogRead(SENSOR);
  count++;
  total += level;
  average = total / count;
  Serial.print("Detected: ");
  Serial.println(average, DEC);
}
