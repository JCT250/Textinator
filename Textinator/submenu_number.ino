void submenu_number()
{
  submenu_exit = 0;// set our exit menu variable
  lcd.clear(); // do some LCD setup stuff
  lcd.setCursor(0,0);
  lcd.print("Set Number");
  submenu_number_update();
  delay(250);

  while(submenu_exit == 0) // whilst the select key hasn't been pressed
  {
    lcd_key = read_LCD_buttons(); // check the keys
    switch (lcd_key)
    {

    case btnRIGHT:
      {
        number_current_index ++;
        if(number_current_index < 16) // check that the current index does not exceed the length of the screen
        {
          lcd.setCursor(number_current_index, 0);
          submenu_number_update();
        }
        else
        {
          number_current_index --; 
        }
        delay(submenu_updateInterval);
        break;
      }

    case btnLEFT: // see the above btnRIGHT section for most comments
      {
        number_current_index --;
        if(number_current_index >= 0) // check that the current index does not exceed the length of the screen
        {
          lcd.setCursor(number_current_index, 0);
          submenu_number_update();
        }
        else
        {
          number_current_index++; 
        }
        delay(submenu_updateInterval);
        break;
      }

    case btnUP:
      {
        new_number_index = str6.indexOf(targetNumber.charAt(number_current_index));
        new_number_index ++;
        if(new_char_index > str6.length() - 1) new_char_index = 0;       
        targetNumber.setCharAt(number_current_index, str6.charAt(new_number_index));
        submenu_number_update();
        delay(200);
        break;
      }

    case btnDOWN:
      {
        new_number_index = str6.indexOf(targetNumber.charAt(number_current_index));
        new_number_index --;
        if(new_number_index < 0) new_number_index = str6.length() - 1;     
        targetNumber.setCharAt(number_current_index, str6.charAt(new_number_index));
        submenu_number_update();
        delay(200);
        break;
      }

    case btnSELECT:
      {
        submenu_exit = 1; // trigger a menu exit
        lcd_update = 1;
        lcd.noCursor();
        targetNumberParse();
        delay(submenu_updateInterval); // delay so that the select button press isn't carried onto the main menu
        break;
      } 
    }
  }

}

void submenu_number_update()
{
  lcd.setCursor(0,1); // clear that section of the LCD
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print(targetNumber);
  lcd.cursor();
  lcd.setCursor(number_current_index, 1);
}

void targetNumberParse()
{
  str8 = targetNumber;
  if(targetNumber.startsWith(str7))
  {
    str8.setCharAt(0,' ');
  }
  str8.trim();
  targetNumberParsed = "+64";
  targetNumberParsed += str8;
}



