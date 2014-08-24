void submenu_start()
{
  submenu_exit = 0; // set our exit menu variable (in this case to stop the attack) to 0
  messagesSent = 0; // reset the number of messages sent
  messagesToSend = 1;
  if(quantity > 0) messagesToSend = quantity;

  lcd.clear(); // do some LCD setup stuff
  lcd.setCursor(0,0);
  lcd.print("Beginning attack");
  lcd.setCursor(0,1);
  lcd.print("Select to stop");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Messages sent:  ");

  while(submenu_exit == 0) // whilst the select key hasn't been pressed
  {
    lcd_key = read_LCD_buttons(); // check the keys
    switch (lcd_key)
    case btnSELECT: // if the select key has been pressed
    {
      submenu_exit = 1; // then exit the menu (stop the attack)
      lcd_update = 1; // and trigger an lcd update
      break;
    }

    if(messagesToSend > 0 && quantity != 0)
    {
      if(lastMessage_time < millis() - delayMilliseconds) // otherwise if it is time to send a message (defined by the last time a message was sent and the interval at which we send a message)
      {
        messagesSent ++; // increment the counter recording how many messages have been sent
        send_message(); // then send the message
        lastMessage_time = millis(); // update the time that a message was last sent
        lcd.setCursor(0,1); // and then in the right place
        lcd.print(messagesSent); // display the number of messages sent on the LCD
        messagesToSend --;
      }
    }

    else if(messagesToSend == 0  && quantity != 0)
    {
      delay(1000);
      submenu_exit = 1; // then exit the menu (stop the attack)
      lcd_update = 1; // and trigger an lcd update
    }

    if(quantity == 0)
    {
      if(lastMessage_time < millis() - delayMilliseconds) // otherwise if it is time to send a message (defined by the last time a message was sent and the interval at which we send a message)
      {
        send_message(); // then send the message
        lastMessage_time = millis(); // update the time that a message was last sent
        messagesSent ++; // increment the counter recording how many messages have been sent
        lcd.setCursor(0,1); // and then in the right place
        lcd.print(messagesSent); // display the number of messages sent on the LCD
      }
    }
  }
}












