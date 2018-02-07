#define mid  580                  //found by physically setting the steering at mid
#define left_comp 695               //found by physically setting the steering at left max
#define right_comp 463                //found by physically setting the steering at right max
#define left 680
#define right 480
const int Enable = 2;               //for the servo to start working
const int InA = 7;                  //inhibit input has to be disabled for the motor to spin
const int InB = 9;                 // the PWM input. 1 for direction 1 254 for direction 2
const int fdbk = A0;                //output of the encoder goes here
double currentpos = 0;                //variable for current position
int desired = mid ;               //setting the desired position as mid
double pos_er = 0;                  //position error
double Outputval;

unsigned long lastTime= 0;
double errSUM, LastERR;
double sampletime = 0.1;
double Kp = 1, Ki = 0, Kd = 2.6;
double kp, ki, kd,a,b;

byte incdata;
long  incoming[2];
int angle = 0;
void setup() {
   Serial.begin(9600);               //start serial comms
  pinMode(Enable, OUTPUT);            //setting enable, InA, InB in output mode
  pinMode(InA, OUTPUT);
  pinMode(InB, OUTPUT);
  kp = Kp;
  ki = Ki * sampletime;
  kd = Kd / sampletime;
  a = kp * 1;
  b = kp * 100;

}

void loop() {
  currentpos = analogRead(fdbk);          //current postion will be the direct input of the analog pin
  pos_er = desired - currentpos;          //self explanatory

  if(Serial.available()>=2){
  for (int i = 0; i<2 ; i++){
    incoming[i] = Serial.read();
    }`
    angle = (256*incoming[0])+incoming[1];
  Serial.println(angle);
  desired = (angle * 0.277) + 580;
  Serial.println(desired);


   while (pos_er != 0)
  {
    unsigned long now = millis();
    double timechange = (double)(now - lastTime);


    currentpos = analogRead(fdbk);
    pos_er = desired - currentpos;          //self explanatory
    errSUM += (pos_er * timechange);
    double dErr = (pos_er - LastERR) / timechange;

//    Serial.print(pos_er);
//  Serial.print("\t");
//  Serial.println("127");

    Outputval = kp * pos_er + ki*errSUM + kd*dErr;

    
    LastERR = pos_er;
    lastTime = now - sampletime;

    //delay(500);


    if (currentpos < right_comp | currentpos <right)
    {
      digitalWrite(InA, LOW);
      analogWrite(InB, 254);
    }
    else if (currentpos > left_comp | currentpos >left)
    {
      digitalWrite(InA, LOW);
      analogWrite(InB, 1);
    }


    if ((currentpos >= right_comp) && (currentpos <= left_comp))
    {
      if ((desired >= right_comp) && (desired <= left_comp))
      {
        if (Outputval > 1)
        {
          digitalWrite(Enable, HIGH);
          digitalWrite(InA, LOW);
          int val_pve = map(Outputval, a, b, 128, 254);
          if (val_pve > 254)
          {
          analogWrite(InB, 254);
//        
//            Serial.print(pos_er);
//            Serial.print("\t");
// 
//            Serial.println("254");
          }
          else
          {
            analogWrite(InB, val_pve);
//        
//            Serial.print(pos_er);
//            Serial.print("\t");
//            
//            Serial.println(val_pve);
          
            
            }
        }

        if (Outputval < -1)
        {
          digitalWrite(Enable, HIGH);

          digitalWrite(InA, LOW);

          int val_nve = map(Outputval, -a, -b, 126, 1);
          if (val_nve < 1)
          {
          analogWrite(InB, 1);
//          
//            Serial.print(pos_er);
//            Serial.print("\t");
//  
//            Serial.println("1");
          }
          else
          {
            analogWrite(InB, val_nve);
//         
//          Serial.print(pos_er);
//          Serial.print("\t");
//          Serial.println(val_nve);
          

            
            }
            
            }

      }
    }
  }
  if (pos_er == 0)
  {
    digitalWrite(Enable, HIGH);

    digitalWrite(InA, HIGH);
    analogWrite(InB, 127);
//Serial.print("0");
//Serial.print("\t");
//Serial.println("127");
//    
    
  }
  

    
  }


}
