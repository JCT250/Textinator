void send_message()
{
  serial_gsm.print("AT+CMGS=\"");
  serial_gsm.print(targetNumberParsed);
  serial_gsm.println("\"");
  delay(500);
  serial_gsm.print(targetMessageParsed);
  //serial_gsm.print(" ");
  //serial_gsm.print(messagesSent);
  delay(500);
  serial_gsm.println((char)26);
  delay(500);
  serial_gsm.println();
  delay(4000);
  if(serial_gsm.available())
  {
    while(serial_gsm.available()) 
    {
      Serial.write(serial_gsm.read());
      delay(1);
    }
  }
  Serial.print("Sent: ");
  Serial.println(messagesSent);
  // serial_gsm.println("AT+CMGDA=\"DEL ALL\""); // delete all SMS
}



