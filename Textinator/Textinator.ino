//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************
 * 
 * This program will test the LCD panel and the buttons
 * Mark Bramwell, July 2010
 * 
 ********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(10, 11, 2, 3, 4, 5);

// define the menu options
char* menu1_options[] = {
  "Target number:  ", "Target message: ", "Delay:          ", "Quantity:       ", "Start           ", "Status:         "};
int menu1_position = 0;
int lcd_update = 0; // whether we need to update the LCD based on whether any buttons have been pressed
unsigned long menu1_lastRead = 0; // time that the buttons were last read.
int menu1_updateInterval = 250; // interval at which we check for button presses

// define some global submenu variables
int submenu_exit = 0; // variable used to determine whether we should exit any particular submenu. This value should be changed in a submenu via a press of the select key
int submenu_updateInterval = 250;

// define some attack variables
unsigned long lastMessage_time = 0;
int messagesSent = 0;
int messagesToSend = 0;

// define some message submenu variables
int message_current_index = 0;
String str1 = "        "; // first string on second row
String str2 = " "; // second string on second row
String str3 = "       "; // third string on second row
String str4 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "; // available characters
int new_char_index = 0; // index in above array of chosen replacement character for the editable position in the target message

// define some number submenu variables
int number_current_index = 0;
String str5;
String str6 = " 0123456789";
String str7 = "0";
String str8;
int new_number_index = 0;


// define some variables to scroll the target message on menu1
int n = 0; //current start position in targetmessage
String scrollString;
unsigned long scrollLast = 0;
unsigned long scrollInterval = 500;

// define some quantity variables
int quantity = 0;

// define some delay variables
unsigned long delayMilliseconds = 1000;
long delaySeconds = 1;

// define some target variables
String targetMessage = "prepare to meet your doom patrick yes that is h m"; // used to store message to target
String targetNumber = "021809596     ";
String targetNumberParsed = "+64";

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in > 100 && adc_key_in < 200)  return btnUP; 
  if (adc_key_in > 250 && adc_key_in < 350)  return btnDOWN; 
  if (adc_key_in > 400 && adc_key_in < 500)  return btnLEFT; 
  if (adc_key_in > 670 && adc_key_in < 770)  return btnSELECT;  
  return btnNONE;  // when all others fail, return this...
}

void setup()
{
  lcd.begin(16, 2);              // start the library
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Textinator v0.1"); // print a simple message
  delay(1000);
  lcd.clear();
  targetMessage_clear();
  targetNumberParse();
  lcd.print(menu1_options[menu1_position]);
  lcd.setCursor(0,1);
  lcd.print(targetNumberParsed);
}

void targetMessage_clear()
{
  // for(int i=0; i<targetMessage.length(); i++)
  //  {
  //   targetMessage.setCharAt(i,0x20);
  //  }
  // targetMessage.setCharAt(49, 0x00); 
}

void loop()
{
  if(menu1_lastRead < millis() - menu1_updateInterval)
  {
    lcd_key = read_LCD_buttons();  // read the buttons

      switch (lcd_key)               // depending on which button was pushed, we perform an action
    {
    case btnUP:
      {
        menu1_position--;
        lcd_update = 1;
        break;
      }
    case btnDOWN:
      {
        menu1_position++;
        lcd_update = 1;
        break;
      }
    case btnSELECT:
      {
        if(menu1_position == 0) submenu_number();
        if(menu1_position == 1) submenu_message();
        if(menu1_position == 2) submenu_delay();
        if(menu1_position == 3) submenu_quantity();
        if(menu1_position == 4) submenu_start();
        break;
      }
    case btnNONE:
      {
        // lcd.print("NONE  ");
        break;
      }
    }
  }

  if(lcd_update == 1)
  {
    if(menu1_position < 0) menu1_position = 4;
    if(menu1_position > 4) menu1_position = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(menu1_options[menu1_position]);
    lcd_update = 0;
    menu1_lastRead = millis();
    if(menu1_position == 0)
    {
      lcd.setCursor(0,1);
      lcd.print(targetNumberParsed);
    }    
    if(menu1_position == 1) n = 0; // reset the scrolling index for the target message
    if(menu1_position == 2)
    {
      lcd.setCursor(0,1);
      lcd.print(delaySeconds);
      lcd.setCursor(9,1);
      lcd.print("seconds"); 
    }
    if(menu1_position == 3)
    {
      lcd.setCursor(0,1);
      lcd.print(quantity);
    }

  }



  /* if we have the message menu item selected then we need to check first if it is stime to update the position of the 
   characters that we are scrolling. If it is then we need to then check to see if out index position has exceeded the length
   of the String. This is to ensure that the message starts scrolling again once every character of the message has been printed 
   in the first position on the second row of the LCD. After that we clear the bottom row of the LCD to remove any old characters
   in positions that we are no longer using. Then a substring 16 characters long is selected from the message string. The Null
   character at the end of the string should terminate this automatically for us. This substring is then printed to the bottom row of the LCD.
   Finally we increment the index and reset the time that the scroll message was last updated.
   */
  if((menu1_position) == 1 && scrollLast < millis() - scrollInterval)
  {
    if(n > targetMessage.length()) n=0;
    lcd.setCursor(0,1);
    lcd.print("                ");
    scrollString = targetMessage.substring(n,n+16);
    lcd.setCursor(0,1);
    lcd.print(scrollString);
    n++;
    scrollLast = millis();
  }


}


/*
 serial_gsm.println("AT+CMGF=1\r");
 delay(1000);
 serial_gsm.println("AT+CMGS=\"+6421809596\"");
 delay(1000);
 serial_gsm.print("http://google.com/#q=");
 serial_gsm.println(Str1);
 delay(1000);
 serial_gsm.println((char)26);
 delay(1000);
 serial_gsm.println();
 delay(1000);
 //while(serial_gsm.available()) Serial.write(serial_gsm.read());
 serial_gsm.println("AT+CMGDA=\"DEL ALL\""); // delete all SMS
 flash();
 for(int i=0; i<49; i++)
 {
 Str1[i] = 0x20;
 }
 Str1[49] = 0x00;
 
 */












