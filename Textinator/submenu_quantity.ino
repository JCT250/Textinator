void submenu_quantity()
{
  submenu_exit = 0;// set our exit menu variable

  lcd.clear(); // do some LCD setup stuff
  lcd.setCursor(0,0);
  lcd.print("Set Quantity");
  lcd.setCursor(0,1);
  lcd.print(quantity); 
  delay(250);

  while(submenu_exit == 0) // whilst the select key hasn't been pressed
  {
    lcd_key = read_LCD_buttons(); // check the keys
    switch (lcd_key)
    {
    case btnUP: // if the up key has been pressed
      {
        lcd.setCursor(0,1); // clear that section of the LCD
        lcd.print("                ");
        quantity ++; // increase the delay
        lcd.setCursor(0,1);
        lcd.print(quantity); // update the LCD with the new delay period
        delay(submenu_updateInterval); // and then delay the required ammount of time (interval between detected button presses)
        break;
      }

    case btnDOWN: // if the down key has been pressed
      {
        lcd.setCursor(0,1); // clear that section of the LCD
        lcd.print("                ");
        quantity --; // decrease the delay
        if(quantity < 0) quantity  = 0; // if the time is less than 1 then make it 1
        lcd.setCursor(0,1);
        lcd.print(quantity); // update the LCD with the new delay period 
        delay(submenu_updateInterval); // and then delay the required ammount of time (interval between detected button presses)
        break;
      }

    case btnSELECT: // if the select key has been pressed
      {
        submenu_exit = 1; // trigger a menu exit
        lcd_update = 1; // trigger a LCD update
        delay(submenu_updateInterval); // delay so that the select button press isn't carried onto the main menu
        break;
      }
    }
  }
}

