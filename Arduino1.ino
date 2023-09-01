#include<Servo.h>
#include <LiquidCrystal.h>
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String Rteam =String("R Team Smart Garage");
int  length=Rteam.length();//19


#define entrance A4
#define exit A3
#define motor 3
#define temperature A5

Servo motorg;

int S[6];//6sllot
int gate[2];
int closegate,open;
int carnum,temp,buttonR;
int slot[6];
bool receive=0;


int closegate,open=1,carnum;

const int led[]={13,12,11};


void setup() {
  lcd.begin(16, 2);
Serial.begin(9600);
  for(int i=0;i<3;i++){pinMode(led[i],OUTPUT);}
 
    pinMode(motor,OUTPUT);
  motorg.attach(motor);
  for(int i=0;i<=90;i++){motorg.write(i); delay(30);} 
}



void loop() 
{
   for(int i=0;i<length;i++)    {
     input();
     receive();
     leds_slots();
   if(gate[0]<=80 && gate[1]>80 &&carnum<6)break;
   if(gate[0]<=80 && gate[1]>80)break; 
   if(carnum==6)break; 
    //moving message
     lcd.setCursor(0, 1);
     lcd.print("Parking is free!"); 
     lcd.setCursor(0,0);
     clearRow(0);
     lcd.print(Rteam.substring(i,i+15));
     delay(300);
     if(i==length-1)i=-1;
                                }
  
    //close full slots
  if(carnum==6){lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("It is full :(");
               lcd.setCursor(0,1);
               lcd.print("Soryy my man");
      //waiting for exit
      while(carnum==6){
      input();
      receiving();
               //Write again  
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("It is full :(");
               lcd.setCursor(0,1);
               lcd.print("Soryy my man");
                       }
        leds_slots();
                 } 
               
  
  
  
  
  //welcome open
   open=1;
  if(gate[0]<=80 && gate[1]>80 &&carnum<6){closegate=0;
   
    while(1){gate[0]=analogRead(entrance);
             input();
             receive();
             leds_slots();
    //check the case
    if(gate[0]>80){int timebegin=millis(),timeend;
                 while(1){timeend=millis();
                          gate[1]=analogRead(exit);
                          if(gate[1]<=80){carnum++;closegate=1;break;}
                          if((timeend-timebegin)>=2000){closegate=1;break;} 
                           }
                }
             if(closegate)break;
            }
          for(int i=0;i<=90;i++){motorg.write(i); delay(30);}       
          //restart
          gate[0]=153;
          gate[1]=153; 
          delay(1000);
                       }
  
  
  //exit open
  if(gate[1]<=80 && gate[0]>80){closegate=0;          
     for(int i=90;i>=0;i--){motorg.write(i); delay(30);}
     while(1){gate[1]=analogRead(exit);
              input();
              receive();
              leds_slots();
                
    //check the case
    if(S[6]>80) {int timebegin=millis(),timeend;
                 while(1){timeend=millis();
                         S[5]=analogRead(entrance);
                         if(S[5]<=80){carnum--;closegate=1;break;}
                         if((timeend-timebegin)>=2000){closegate=1;break;} 
                          }
                 }
              if(closegate)break;
             }
           for(int i=0;i<=90;i++){motorg.write(i); delay(30);}  
           //restart
          gate[0]=153;
          gate[1]=153;
          delay(1000);
                        }
 
}


void input (void){
   S[0]=analogRead(A0);
   S[1]=analogRead(A1);
   S[2]=analogRead(A2);
   gate[0]=analogRead(entrance);
   gate[1]=analogRead(exit);
  delay(200);
}

void receive (void){
  while(1){
  if(Serial.available()) {
    for(int i=0;i<5;i++)
    {
      if(i<3){S[i]=Serial.parseInt();
              if(S[i]!=0) receive=1;
              else {receive=0;while(!S[i])
                   S[i]=Serial.parseInt();} 
             }
      if(i==3)temp=Serial.parseInt();
      if(i==4)buttonR=Serial.parseInt();
      
    }
  
                         }
       if(receive)break;
         }
    Serial.flush();
    //c = continue ,f =fire
    if(temp<90 || buttonR){Serial.write("c"); delay(50);}
    else{Serial.write("f"); delay(50); fire();}
}

void leds_slots(void)
{
  for(int i=0;i<6;i++) {    
     if (S[i]<=80){
       slot[i]=1;if(i<3)digitalWrite(led[i],LOW);
                  }
  else{slot[i]=0;if(i<3)digitalWrite(led[i],HIGH);}
                        }
}
  
void fire(void) 
{//close
if(closegate)for(int i=0;i<=90;i++){motorg.write(i); delay(30);}
  
  //buzzser
  while(1){
    digitalWrite(buzzer,HIGH);
    delay(30);
    digitalWrite(buzzer,LOW);
    delay(30);
    dataR=Serial.read();
    if(dataR=='c'){if(closegate){closegate=0;
                                for(int i=90;i>=0;i--)
                                motorg.write(i); delay(30);
                                }
                   break;
                  }
         }
   
}