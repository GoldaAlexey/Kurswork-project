void loop() {
  byte flag = 0;
  if (sleep_flag) {  // если проснулись  после сна, инициализировать дисплей и вывести текст, сумму и валюту
    delay(500);
    lcd.init();
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print(L"На курсач СИФО");
    lcd.setCursor(0, 1); lcd.print(summ_money);
    lcd.setCursor(13, 1); lcd.print(currency);
    empty_signal = analogRead(IRsens);
    sleep_flag = false;
  }

  // далее работаем в бесконечном цикле
  flag=false;
  last_sens_signal = empty_signal;
  while (1) {
    while(1){
      if(!digitalRead(calibr_button))
      {
        Serial.println("Reboot Button");
        flag=true;
      }
    }
    while(1){
        if(!digitalRead(button))
        {
          
          Serial.println("Normal Button");
          flag=false;
          break;
        }
        sens_signal = analogRead(IRsens);  // далее такой же алгоритм, как при калибровке
        if (sens_signal > last_sens_signal) last_sens_signal = sens_signal;
        if (sens_signal - empty_signal > 3) coin_flag = true;
        if (coin_flag && (abs(sens_signal - empty_signal)) < 2) {
          Serial.println(last_sens_signal);
          recogn_flag = false;  // флажок ошибки, пока что не используется
          // в общем нашли максимум для пролетевшей монетки, записали в last_sens_signal
          // далее начинаем сравнивать со значениями для монет, хранящимися в памяти
          for (byte i = 0; i < coin_amount; i++) {
            int delta = abs(last_sens_signal - coin_signal[i]);   // вот самое главное! ищем АБСОЛЮТНОЕ (то бишь по модулю)
            // значение разности полученного сигнала с нашими значениями из памяти
 
              if (delta < 30) {   // и вот тут если эта разность попадает в диапазон, то считаем монетку распознанной
                Serial.println("Дельта");
                Serial.println(delta);
                summ_money += coin_value[i];  // к сумме тупо прибавляем цену монетки (дада, сумма считается двумя разными способами. При старте системы суммой всех монет, а тут прибавление
                lcd.setCursor(0, 1); lcd.print(summ_money);
                coin_quantity[i]++;  // для распознанного номера монетки прибавляем количество
                recogn_flag = true;
                break;
            }
         // }
      }
      coin_flag = false;
      standby_timer = millis();  // сбросить таймер
      break;
        }
      }
//
    while(1){
          if(!digitalRead(button))
          {
            
            Serial.println("Normal Button");
            flag=false;
            break;
          }
        }
    
    

    // если ничего не делали, времят аймера вышло, спим
    if (millis() - standby_timer > stb_time) {
      good_night();
      break;
    }

    // если монетка вставлена (замыкает контакты) и удерживается 2 секунды
    while (!digitalRead(button)) {
      if( flag == 1) {
        lcd.init();
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print(L"На курсач СИФО");
        lcd.setCursor(0, 1); lcd.print(summ_money);
        lcd.setCursor(13, 1); lcd.print(currency);
        empty_signal = analogRead(IRsens);
      }
      if (millis() - standby_timer > 2000) {
        lcd.clear();
        flag = 1;
        // отобразить на дисплее: сверху цены монет (округлено до целых!!!!), снизу их количество
        for (byte i = 0; i < coin_amount; i++) {
          lcd.setCursor(i * 3, 0); lcd.print((int)coin_value[i]);
          lcd.setCursor(i * 3, 1); lcd.print(coin_quantity[i]);
        }
      }
    }
  }
}