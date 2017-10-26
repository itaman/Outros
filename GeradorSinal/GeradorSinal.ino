//Copyright (c) 2013 Itaman Cavalcanti de Oliveira <itamanman@yahoo.com.br>

//Este programa é um software livre; você pode redistribui-lo e/ou 
//modifica-lo dentro dos termos da Licença Pública Geral Menor GNU como 
//publicada pela Fundação do Software Livre (FSF); na versão 3 da 
//Licença, ou (na sua opnião) qualquer versão.

//Este programa é distribuido na esperança que possa ser  util, 
//mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUAÇÂO
//a qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a Licença
//Pública Geral GNU para maiores detalhes em <www.gnu.org>.

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU Lesser General Public License
//as published by the Free Software Foundation; either version 3
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details at www.gnu.org

#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

RTC_DS1307 RTC;
LiquidCrystal lcd (8, 9, 10, 11, 12, 13);

int btt1=0;
int btt2=1;
int btt3=2;
int OldHour;
int OldMin;
int OldYear;
int OldMonth;
int OldDay;
int btt1state;
int btt2state;
int btt3state;
int hour_inicial, min_inicial,sec_inicial;
int min_dif , hour_dif;
int hour_teste, min_teste,sec_teste;
int day_teste, month_teste,year_teste, dow_teste;
int hour_teste1, min_teste1,sec_teste1;
int hour_15=0;
int hour_30=0;
int hour_45=0;
int hour_60=0;
int min_15=0;
int min_30=0;
int min_45=0;
int min_60=0;
int hour_dif_15=0;
int min_dif_15=0;
int hour_dif_30=0;
int min_dif_30=0;
int hour_dif_45=0;
int min_dif_45=0;
int hour_dif_60=0;
int min_dif_60=0;
//char* meses[]={"","JAN", "FEV", "MAR", "ABR", "MAI", "JUN", "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
int cont_15, cont_30, cont_45, cont_60;
int pin12 = 3, pin13 = 4, pin14 = 5, pin15=6, sinal=7;

void setup () {
  //Serial.begin(9600);
  lcd.begin(16, 2);
  Wire.begin();
  RTC.begin();
  pinMode(btt1, INPUT);
  pinMode(btt2, INPUT);
  pinMode(btt3, INPUT);
  pinMode(pin12, OUTPUT);
  pinMode(pin13, OUTPUT);
  pinMode(pin14, OUTPUT);
  pinMode(pin15, OUTPUT);
  pinMode(sinal, OUTPUT);
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  //attachInterrupt(digitalPinToInterrupt(btt1), ajusteData, RISING); 
}

void loop () {
    DateTime now = RTC.now();
    
    lcd.setCursor(0,0);
    lcd.print("TIME: ");
    lcd.print(now.hour(), DEC);
    //lcd.setCursor(8,0);
    lcd.print(":");
    if(now.minute()>9){
    lcd.print(now.minute(), DEC);
    lcd.print("  OFF");
    }
    else{
      lcd.print("0");
      lcd.print(now.minute(), DEC);
      lcd.print("  OFF");
    }
    //lcd.setCursor(11,0);
    //lcd.print(":");
    //lcd.print(now.second(), DEC); 
    
    lcd.setCursor(0,1);
    lcd.print("DATE: ");
    lcd.print(now.day(), DEC);
    lcd.print("/");
    lcd.print(now.month(), DEC);
    lcd.print("/");
    lcd.print(now.year(), DEC);

    btt1state = digitalRead(btt1);

    if (btt1state==HIGH){
      lcd.setCursor(0,0);
      lcd.print("   **AJUSTE**   ");
      delay(100);
     ajusteData();
   }
    hour_15=now.hour();
    min_15=now.minute();

    hour_30=now.hour();
    min_30=now.minute();

    hour_45=now.hour();
    min_45=now.minute();

    hour_60=now.hour();
    min_60=now.minute();

    btt2state = digitalRead(btt2);
    if (btt2state==HIGH){
     lcd.setCursor(0,0);
     lcd.print("GERADOR DE PULSO");
     lcd.setCursor(0,1);
     lcd.print("  INICIALIZADO  ");
     digitalWrite(sinal,HIGH);
     while(true){ 
        delay(1000);
        DateTime now = RTC.now();
    
        lcd.setCursor(0,0);
        lcd.print("TIME: ");
        lcd.print(now.hour(), DEC);
        //lcd.setCursor(8,0);
        lcd.print(":");
        if(now.minute()>9){
          lcd.print(now.minute(), DEC);
          lcd.print("   ON");
         }
        else{
          lcd.print("0");
          lcd.print(now.minute(), DEC);
          lcd.print("   ON");
         }
    //lcd.setCursor(11,0);
    //lcd.print(":");
    //lcd.print(now.second(), DEC); 
    
        lcd.setCursor(0,1);
        lcd.print("DATE: ");
        lcd.print(now.day(), DEC);
        lcd.print("/");
        lcd.print(now.month(), DEC);
        lcd.print("/");
        lcd.print(now.year(), DEC);

    //btt1state = digitalRead(btt1);

   // if (btt1state==HIGH){
     // lcd.setCursor(0,0);
      //lcd.print("   **AJUSTE**   ");
      //delay(100);
    // ajusteData();
   //}
        hour_teste=now.hour();
        min_teste=now.minute();
        day_teste=now.day();
        month_teste=now.month();
        year_teste=now.year();

        hour_dif_15=hour_teste-hour_15;
        min_dif_15=min_teste-min_15;

        hour_dif_30=hour_teste-hour_30;
        min_dif_30=min_teste-min_30;

        hour_dif_45=hour_teste-hour_45;
        min_dif_45=min_teste-min_45;
   
        hour_dif_60=hour_teste-hour_60;
        min_dif_60=min_teste-min_60;

        if (hour_dif_15==0){
          if(min_dif_15==15){
            digitalWrite(pin12,HIGH);
            cont_15=1;
            hour_15=hour_teste;
            min_15=min_teste;
          }
        }
        if (hour_dif_15==1){
            min_teste=min_teste+60;
            min_dif_15=min_teste-min_15;
            if(min_dif_15==15){
              digitalWrite(pin12,HIGH);
              cont_15=1;
              hour_15=now.hour();
              min_15=now.minute();
            }
          }
   if (cont_15==1){
    if(hour_dif_15==0){
      if(min_dif_15==1){
        digitalWrite(pin12,LOW);
        cont_15=0;
        hour_15=now.hour();
        min_15=now.minute();
      }
    }
    if(hour_dif_15==1){
      if(now.minute()==0){
        digitalWrite(pin12,LOW);
        cont_15=0;
        hour_15=now.hour();
        min_15=now.minute();
      }
      else{
        min_teste=now.minute()+60;
        min_dif_15=now.minute()-min_15;
        if(min_dif_15==1){
          digitalWrite(pin12,LOW);//15min
          cont_15=0;
          hour_15=now.hour();
          min_15=now.minute();
        }
      }
    }
   }
   
   // 30 min
   if (hour_dif_30==0){
    if(min_dif_30==30){
      digitalWrite(pin13,HIGH);
      cont_30=1;
      hour_30=hour_teste;
      min_30=min_teste;
    }
   }
   if (hour_dif_30==1){
    min_teste=min_teste+60;
    min_dif_30=min_teste-min_30;
    if(min_dif_30==30){
      digitalWrite(pin13,HIGH);
      cont_30=1;
      hour_30=now.hour();
      min_30=now.minute();
    }
   }
   if (cont_30==1){
    if(hour_dif_30==0){
      if(min_dif_30==1){
        digitalWrite(pin13,LOW);
        cont_30=0;
        hour_30=now.hour();
        min_30=now.minute();
      }
    }
    if(hour_dif_30==1){
      if(now.minute()==0){
        digitalWrite(pin13,LOW);
        cont_30=0;
        hour_30=now.hour();
        min_30=now.minute();
      }
      else{
        min_teste=now.minute()+60;
        min_dif_30=now.minute()-min_30;
        if(min_dif_30==1){
          digitalWrite(pin13,LOW);;//15min
          cont_30=0;
          hour_30=now.hour();
          min_30=now.minute();
        }
      }
    }
   }
   
   // 45 min
   if (hour_dif_45==0){
    if(min_dif_45==45){
      digitalWrite(pin14,HIGH);
      cont_45=1;
      hour_45=hour_teste;
      min_45=min_teste;
    }
   }
   if (hour_dif_45==1){
    min_teste=min_teste+60;
    min_dif_45=min_teste-min_45;
    if(min_dif_45==45){
      digitalWrite(pin14,HIGH);
      cont_45=1;
      hour_45=now.hour();
      min_45=now.minute();
    }
   }
   if (cont_45==1){
    if(hour_dif_45==0){
      if(min_dif_45==1){
        digitalWrite(pin14,LOW);
        cont_45=0;
        hour_45=now.hour();
        min_45=now.minute();
      }
    }
    if(hour_dif_45==1){
      if(now.minute()==0){
        digitalWrite(pin14,LOW);
        cont_45=0;
        hour_45=now.hour();
        min_45=now.minute();
      }
      else{
        min_teste=now.minute()+60;
        min_dif_45=now.minute()-min_45;
        if(min_dif_45==1){
          digitalWrite(pin14,LOW);;//15min
          cont_45=0;
          hour_45=now.hour();
          min_45=now.minute();
        }
      }
    }
   }
   
   // 60 min
   if (hour_dif_60==0){
    if(min_dif_60==60){
      digitalWrite(pin15,HIGH);
      cont_60=1;
      hour_60=hour_teste;
      min_60=min_teste;
    }
   }
   if (hour_dif_60==1){
    min_teste=min_teste+60;
    min_dif_60=min_teste-min_60;
    if(min_dif_60==60){
      digitalWrite(pin15,HIGH);
      cont_60=1;
      hour_60=now.hour();
      min_60=now.minute();
    }
   }
   if (cont_60==1){
    if(hour_dif_60==0){
      if(min_dif_60==1){
        digitalWrite(pin15,LOW);
        cont_60=0;
        hour_60=now.hour();
        min_60=now.minute();
      }
    }
    if(hour_dif_60==1){
      if(now.minute()==0){
        digitalWrite(pin15,LOW);
        cont_60=0;
        hour_60=now.hour();
        min_60=now.minute();
      }
      else{
        min_teste=now.minute()+60;
        min_dif_60=now.minute()-min_60;
        if(min_dif_60==1){
          digitalWrite(pin15,LOW);;//15min
          cont_60=0;
          hour_60=now.hour();
          min_60=now.minute();
        }
      }
    }
   }
   btt3state = digitalRead(btt3);

   if (btt3state==HIGH){
    lcd.setCursor(0,0);
  lcd.print("PARANDO DE GERAR");
  lcd.setCursor(0,1);
  lcd.print("     PULSOS     ");
  delay(1500);
  digitalWrite(sinal,LOW);
    break;
   }
   delay(1000);
   }
  }
  delay(1000);
}


void ajusteData(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("   Ajuste...   ");
  DateTime now = RTC.now();
  OldHour=(int)now.hour();
  OldMin=(int)now.minute();
  OldYear=now.year();
  OldMonth=now.month();
  OldDay=now.day();
  delay(5000);
  
   if (OldHour>9){
    lcd.setCursor(0,0);
    lcd.print("AJUSTE HORA:");
    lcd.setCursor(6,1);
    lcd.print(OldHour, DEC);
    }
    else {
      lcd.setCursor(0,0);
      lcd.print("AJUSTE HORA:");
      lcd.setCursor(6,1);
      lcd.print("0");
      lcd.print(OldHour, DEC);
    }
  
  btt1state = digitalRead(btt1);

   while(btt1state==LOW){ // Enquanto OK não acionado
    btt2state = digitalRead(btt2);
    btt3state = digitalRead(btt3);

    if (btt2state == HIGH){ // incrementa
     OldHour=OldHour+1;
    if (OldHour>23){
    OldHour=0;
    }
    if (OldHour>9){
    lcd.setCursor(0,0);
    lcd.print("AJUSTE HORA:");
    lcd.setCursor(6,1);
    lcd.print(OldHour, DEC);
    }
    else {
      lcd.setCursor(0,0);
      lcd.print("AJUSTE HORA:");
      lcd.setCursor(6,1);
      lcd.print("0");
      lcd.print(OldHour, DEC);
    }
    //lcd.print(OldMin, DEC);
   
    delay(500);
    }
    
    if (btt3state == HIGH){ // Decrementa
      OldHour=OldHour-1;
      if (OldHour<0){
    OldHour=23;
    }
    if (OldHour>9){
    lcd.setCursor(0,0);
    lcd.print("AJUSTE HORA:");
    lcd.setCursor(6,1);
    lcd.print(OldHour, DEC);
    }
    else {
      lcd.setCursor(0,0);
      lcd.print("AJUSTE HORA:");
      lcd.setCursor(6,1);
      lcd.print("0");
      lcd.print(OldHour, DEC);
    }
    delay(500);
    }
    btt1state = digitalRead(btt1);
   }

  if (OldMin>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE MINUTO:");
   lcd.setCursor(6,1);
   lcd.print(OldMin, DEC);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("AJUSTE MINUTO:");
    lcd.setCursor(6,1);
    lcd.print("0");
    lcd.print(OldMin, DEC);
  }
   delay(500);
   btt1state = digitalRead(btt1);
   
   while(btt1state==LOW){ // Enquanto OK não acionado
    btt2state = digitalRead(btt2);
    btt3state = digitalRead(btt3);
    
    if (btt2state == 1){ // incrementa
    
      OldMin=OldMin+1;
    
      if (OldMin>59){
        OldMin=00;
      }
      if (OldMin>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE MINUTO:");
   lcd.setCursor(6,1);
   lcd.print(OldMin, DEC);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("AJUSTE MINUTO:");
    lcd.setCursor(6,1);
    lcd.print("0");
    lcd.print(OldMin, DEC);
  }
      delay(500);
    }
    
    if (btt3state == 1){ // Decrementa
    
       OldMin=OldMin-1;
    
       if (OldMin<00){
         OldMin=59;
       }
      
      if (OldMin>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE MINUTO:");
   lcd.setCursor(6,1);
   lcd.print(OldMin, DEC);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("AJUSTE MINUTO:");
    lcd.setCursor(6,1);
    lcd.print("0");
    lcd.print(OldMin, DEC);
  }
      delay(500);
    }
    btt1state = digitalRead(btt1);
  }
  if(OldDay>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE DIA:     ");
   lcd.setCursor(6,1);
   lcd.print(OldDay, DEC);
  }
  else{
    lcd.setCursor(0,0);
   lcd.print("AJUSTE DIA:     ");
   lcd.setCursor(6,1);
   lcd.print("0");
   lcd.print(OldDay, DEC);
  }
   delay(500);
   btt1state = digitalRead(btt1);

   while(btt1state==LOW){ // Enquanto OK não acionado
    btt2state = digitalRead(btt2);
    btt3state = digitalRead(btt3);
    
    if (btt2state == HIGH){ // incrementa
    
      OldDay=OldDay+1;
      if (OldDay>31){
        OldDay=1;
      }
     
      if(OldDay>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE DIA:     ");
   lcd.setCursor(6,1);
   lcd.print(OldDay, DEC);
  }
  else{
    lcd.setCursor(0,0);
   lcd.print("AJUSTE DIA:     ");
   lcd.setCursor(6,1);
   lcd.print("0");
   lcd.print(OldDay, DEC);
  }
      delay(500);
    }
    
    if (btt3state == HIGH){ // decrementa
    
      OldDay=OldDay-1;
      if (OldDay<1){
        OldDay=31;
      }
     
      if(OldDay>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE DIA:     ");
   lcd.setCursor(6,1);
   lcd.print(OldDay, DEC);
  }
  else{
    lcd.setCursor(0,0);
   lcd.print("AJUSTE DIA:     ");
   lcd.setCursor(6,1);
   lcd.print("0");
   lcd.print(OldDay, DEC);
  }
      delay(500);
    }
    btt1state = digitalRead(btt1);
  }
   
  if(OldMonth>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE MES:     ");
   lcd.setCursor(6,1);
   lcd.print(OldMonth, DEC);
  }
  else{
    lcd.setCursor(0,0);
   lcd.print("AJUSTE MES:     ");
   lcd.setCursor(6,1);
   lcd.print("0");
   lcd.print(OldMonth, DEC);
  }
   delay(500);
   btt1state = digitalRead(btt1);

   while(btt1state==LOW){ // Enquanto OK não acionado
    btt2state = digitalRead(btt2);
    btt3state = digitalRead(btt3);
    
    if (btt2state == HIGH){ // incrementa
    
      OldMonth=OldMonth+1;
      if (OldMonth>12){
        OldMonth=1;
      }
     
      if(OldMonth>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE MES:     ");
   lcd.setCursor(6,1);
   lcd.print(OldMonth, DEC);
  }
  else{
    lcd.setCursor(0,0);
   lcd.print("AJUSTE MES:     ");
   lcd.setCursor(6,1);
   lcd.print("0");
   lcd.print(OldMonth, DEC);
  }
      delay(500);
    }
    
    if (btt3state == HIGH){ // decrementa
    
      OldMonth=OldMonth-1;
      if (OldMonth<1){
        OldMonth=12;
      }
     
      if(OldMonth>9){
   lcd.setCursor(0,0);
   lcd.print("AJUSTE MES:     ");
   lcd.setCursor(6,1);
   lcd.print(OldMonth, DEC);
  }
  else{
    lcd.setCursor(0,0);
   lcd.print("AJUSTE MES:     ");
   lcd.setCursor(6,1);
   lcd.print("0");
   lcd.print(OldMonth, DEC);
  }
      delay(500);
    }
    btt1state = digitalRead(btt1);
  }

lcd.setCursor(0,0);
   lcd.print("AJUSTE ANO:     ");
   lcd.setCursor(6,1);
   lcd.print(OldYear, DEC);
   delay(500);
   btt1state = digitalRead(btt1);

   while(btt1state==LOW){ // Enquanto OK não acionado
    btt2state = digitalRead(btt2);
    btt3state = digitalRead(btt3);
    
    if (btt2state == HIGH){ // incrementa
    
      OldYear=OldYear+1;
    
     
      lcd.setCursor(0,0);
      lcd.print("AJUSTE ANO:     ");
      lcd.setCursor(6,1);
      lcd.print(OldYear, DEC);
      delay(500);
    }
    
    if (btt3state == HIGH){ // decrementa
    
      OldYear=OldYear-1;
    
     
      lcd.setCursor(0,0);
      lcd.print("AJUSTE ANO:     ");
      lcd.setCursor(6,1);
      lcd.print(OldYear, DEC);
      delay(500);
    }
    btt1state = digitalRead(btt1);
  }
  
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
   RTC.adjust(DateTime(OldYear, OldMonth, OldDay, OldHour, OldMin,0));
   lcd.setCursor(0,0);
   lcd.print("   ATUALIZADO   ");
   lcd.setCursor(6,1);
   lcd.print("                ");
   delay(500);
 }
