void submenu_message()
{
  submenu_exit = 0;// set our exit menu variable
  lcd.clear(); // do some LCD setup stuff
  lcd.setCursor(0,0);
  lcd.print("Set Message");
  submenu_message_update();
  delay(250);

  while(submenu_exit == 0) // whilst the select key hasn't been pressed
  {
    lcd_key = read_LCD_buttons(); // check the keys
    switch (lcd_key)
    {

    case btnRIGHT:
      {
        message_current_index ++;
        if(message_current_index < targetMessage.length()) // check that the current index does not exceed the length of the string
        {
          submenu_message_update();
        }
        else
        {
          message_current_index --; 
        }
        delay(submenu_updateInterval);
        break;
      }

    case btnLEFT: // see the above btnRIGHT section for most comments
      {
        message_current_index --;
        if(message_current_index >= 0) // this is the only part that is different, it checks that the current index is not less than the first position in the string
        {
          submenu_message_update();
        }
        else
        {
          message_current_index = 0; 
        }
        delay(submenu_updateInterval);
        break;
      }

    case btnUP:
      {
        new_char_index = str4.indexOf(targetMessage.charAt(message_current_index));
        new_char_index --;
        if(new_char_index < 0) new_char_index = str4.length() - 1;      
        targetMessage.setCharAt(message_current_index, str4.charAt(new_char_index));
        submenu_message_update();
        delay(200);
        break;
      }

    case btnDOWN:
      {
        new_char_index = str4.indexOf(targetMessage.charAt(message_current_index));
        new_char_index ++;
        if(new_char_index > str4.length() - 1) new_char_index = 0;      
        targetMessage.setCharAt(message_current_index, str4.charAt(new_char_index));
        submenu_message_update();
        delay(200);
        break;
      }

    case btnSELECT:
      {
        targetMessageParse();
        submenu_exit = 1; // trigger a menu exit
        lcd_update = 1;
        lcd.noCursor();
        delay(submenu_updateInterval); // delay so that the select button press isn't carried onto the main menu
        break;
      } 
    }
  }
}

void submenu_message_update()
{
  lcd.setCursor(0,1); // clear that section of the LCD
  lcd.print("                ");
  if(message_current_index >= 8)
  {
    str1 = targetMessage.substring(message_current_index-8, message_current_index);
    lcd.setCursor(0,1);
    lcd.print(str1);
  }
  else if(message_current_index < 8)
  {
    str1 = targetMessage.substring(0, message_current_index);
    lcd.setCursor(8-message_current_index,1);
    lcd.print(str1);
  }
  str2 = targetMessage.substring(message_current_index, message_current_index + 1);
  str3 = targetMessage.substring(message_current_index + 1,message_current_index + 8);
  lcd.setCursor(8,1);
  lcd.print(str2);
  lcd.setCursor(9,1);
  lcd.print(str3);
  lcd.setCursor(8,1);
  lcd.cursor();
}


void targetMessageParse()
{
  targetMessageParsed = targetMessage;
  targetMessageParsed.trim(); 
}










