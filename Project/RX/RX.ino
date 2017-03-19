/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
     данных, который генерируется согласно показаниям с кнопки и с
     двух потенциомтеров. Приёмник (RX) получает массив, и записывает
     данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte recieved_data[7]; // массив принятых данных
byte relay0 = 2; // реле на 2 цифровом
byte relay1 = 3; // реле на 2 цифровом
byte relay2 = 4; // реле на 2 цифровом
byte relay3 = 5; // реле на 2 цифровом
byte relay4 = 6; // реле на 2 цифровом
byte relay5 = 7; // реле на 2 цифровом
byte relay6 = 8; // реле на 2 цифровом

byte beep = A0; // beep


byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

void setup() {
  Serial.begin(9600); //открываем порт для связи с ПК

  pinMode(relay0, OUTPUT); // настроить пин реле как выход
  pinMode(relay1, OUTPUT); // настроить пин реле как выход
  pinMode(relay2, OUTPUT); // настроить пин реле как выход
  pinMode(relay3, OUTPUT); // настроить пин реле как выход
  pinMode(relay4, OUTPUT); // настроить пин реле как выход
  pinMode(relay5, OUTPUT); // настроить пин реле как выход
  pinMode(relay6, OUTPUT); // настроить пин реле как выход

  pinMode(beep, OUTPUT); // настроить пин реле как выход

  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openReadingPipe(1, address[0]);     //хотим слушать трубу 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
}

void loop() {
  byte pipeNo;
  while ( radio.available(&pipeNo)) {  // слушаем эфир со всех труб
    radio.read( &recieved_data, sizeof(recieved_data) );         // чиатем входящий сигнал
    
    digitalWrite(relay0, recieved_data[0]); // подать на реле сигнал с 0 места массива
    digitalWrite(relay1, recieved_data[1]); // подать на реле сигнал с 0 места массива
    digitalWrite(relay2, recieved_data[2]); // подать на реле сигнал с 0 места массива
    digitalWrite(relay3, recieved_data[3]); // подать на реле сигнал с 0 места массива
    digitalWrite(relay4, recieved_data[4]); // подать на реле сигнал с 0 места массива
    digitalWrite(relay5, recieved_data[5]); // подать на реле сигнал с 0 места массива
    digitalWrite(relay6, recieved_data[6]); // подать на реле сигнал с 0 места массива


    if (recieved_data[0] == 1 || recieved_data[1] == 1 || recieved_data[2] == 1 || recieved_data[3] == 1 || recieved_data[4] == 1 ||  recieved_data[5] == 1 || recieved_data[6] == 1 || recieved_data[7] == 1){
      digitalWrite(beep,1);
       }
else 
{
  digitalWrite(beep,0);
  }
        
    //то бишь 0 или 1


  }
}


