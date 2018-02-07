long  incoming[2];
int a;
double desired;
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600); 
  //Serial.println("Ready");
}

void loop() {
  if(Serial.available()>=2) {
    for (int i = 0; i<2 ; i++) {
      incoming[i] = Serial.read();
    }
    a = (256*incoming[0])+incoming[1];
    Serial.println(a);
    desired = (a * 0.277) + 580;
    Serial.println(desired);
   // Serial.println(incoming[2]);
  }
  
}
