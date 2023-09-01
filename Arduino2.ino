

#define temperature A5
#define ldr A4
#define ldrled 6
#define button 7

String send="\0";
char dataR='0';
char num[3];
int S[5]; //3slot ,temp,buttonR
int buttonR;
int brightnessR,brightness;
float tempR;
int temp;
const int led[]={13,12,11};




void setup() {
Serial.begin(9600);   
  
   for(int i=0;i<3;i++){pinMode(led[i],OUTPUT);}
  pinMode(ldrled,OUTPUT);
  pinMode(button,INPUT);
             }


void loop() {
  
  
  for(int i=0;i<length;i++)    {
   if(open==2 || carnum==6)break; 
  input();
  send();  
      
   
  analogWrite(ldrled,brightness);
    /*for(int i=0;i<6;i++){Serial.println(S[i]);}
    Serial.println(carnum);
     Serial.println(temp);*/
 
    
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
      //inputs
      S[3]=analogRead(A0);
      S[4]=analogRead(A1);
      S[5]=analogRead(A2);
      buttonR=digitalRead(button);
      brightnessR=analogRead(ldr);
      brightness=(brightnessR*255)/1020;
      tempR=analogRead(temperature);
      temp= (tempR*500)/1023; 
      //receiving
      while(1){
      if(Serial.available()) {
      for(int i=0;i<5;i++)
      {
      if(i<3){S[i]=Serial.parseInt();
              if(S[i]!=0) receive=1;
              else {receive=0;while(!S[i])
                   S[i]=Serial.parseInt();} 
             }
      if(i==3)carnum=Serial.parseInt();
      if(i==4)open=Serial.parseInt();
      
      }
  
                           }
       if(receive)break;
            }
    Serial.flush();
    //c = continue ,f =fire
    if(temp<90 || buttonR){Serial.write("c"); delay(50);}
    else{Serial.write("f"); delay(50); fire();
             //Write again  
               lcd.clear();
               lcd.setCursor(0,0);
               lcd.print("It is full :(");
               lcd.setCursor(0,1);
               lcd.print("Soryy my man");
        }
        //leds &&slots
        analogWrite(ldrled,brightness);
        for(int i=0;i<6;i++) {    
        if (S[i]<=80){
        slot[i]=1;if(i>=3)digitalWrite(led[i],LOW);
                     }
        else{slot[i]=0;if(i>=3)digitalWrite(led[i],HIGH);}
                             }
                       } 
               }
  //carnum is not 6
  else{
    //inputs
      S[3]=analogRead(A0);
      S[4]=analogRead(A1);
      S[5]=analogRead(A2);
      brightnessR=analogRead(ldr);
      buttonR=digitalRead(button);
      brightness=(brightnessR*255)/1020;
      tempR=analogRead(temperature);
      temp= (tempR*500)/1023; 
    //receiving
    while(1){
    if(Serial.available()) {
    for(int i=0;i<5;i++)
    {
    if(i<3){S[i]=Serial.parseInt();
            if(S[i]!=0) receive=1;
            else {receive=0;while(!S[i])
                  S[i]=Serial.parseInt();} 
           }
      if(i==3)carnum=Serial.parseInt();
      if(i==4)open=Serial.parseInt();
  
    }
                         }
       if(receive)break;
         }
    Serial.flush();
    //c = continue ,f =fire
    if(temp<90 || buttonR){Serial.write("c"); delay(50);}
    else{Serial.write("f"); delay(50); fire();}
    
    //leds &&slots
    analogWrite(ldrled,brightness);
    for(int i=0;i<6;i++) {    
    if (S[i]<=80){
    slot[i]=1;if(i>=3)digitalWrite(led[i],LOW);
                 }
    else{slot[i]=0;if(i>=3)digitalWrite(led[i],HIGH);}
                        }
    
    //welcome
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome!");
  for(int i=0;i<2;i++){
  lcd.print("S");
  lcd.print(i+1); 
  lcd.print(":"); 
  lcd.print(slot[i]);
                      }
  lcd.setCursor(0,1);
   for(int i=2;i<6;i++){
  lcd.print("S");
  lcd.print(i+1); 
  lcd.print(":"); 
  lcd.print(slot[i]);
                      }
    delay(1000);
      }
  
  
}

void input(void){
      S[0]=analogRead(A0);
      S[1]=analogRead(A1);
      S[2]=analogRead(A2);
      buttonR=digitalRead(button);
      tempR=analogRead(temperature);
      brightnessR=analogRead(ldr);
      brightness=(brightnessR*255)/1020;
      temp=(tempR*500.0)/1023.0; 
     S[3]=temp;
     S[4]=buttonR;
}

void send (void)
{
    for(int i=0;i<5;i++){
      if(S[i]<10)send.concat("0");
      if(S[i]<100)send.concat("0");
      
      //leds
      if(i<3){
      if(S[i]<=80)digitalWrite(led[i],LOW);
        else digitalWrite(led[i],HIGH);
             }
      
      send.concat(S[i]);
      for(int i=0;i<3;i++){num[i]=send.charAt(i);}
      Serial.write(num,3);
      Serial.write('\n');
      send="\0";
                        }
  
  
  
  //message is seen
  while(1){dataR=Serial.read();
           if(dataR=='c')break;
           if(dataR=='f'){closegate=0;fire();break;}
          }
}


void clearRow(int row){
 lcd.setCursor(0,row);
 lcd.print("                   ");
 lcd.setCursor(0,row); 
}

void fire (void)
{lcd.clear();
 lcd.setCursor(0,1);
 lcd.print("Ruuuuuuun!");
 while(1){
    lcd.setCursor(0,0);
    lcd.print("FIIIREEE!");
    delay(500);
   clearRow(0);
    tempR=analogRead(temperature);
    buttonR=digitalRead(button);
    temp= (tempR*500)/1023; 
   if(temp<90 || buttonR){Serial.write("c"); delay(50);break;}
         }
}


