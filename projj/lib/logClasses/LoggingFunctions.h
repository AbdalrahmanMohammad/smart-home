#ifndef LoggingFunctions_h
#define LoggingFunctions_h

#include <Arduino.h>

class LoggingFunctions
{
  /////////  you don't need to use update function here, you just use writeLog and it internally uses update if necessary
  ////////   i have three overloaded functions for writeLog, depending on the value (string, int, boolean)
  ////////   they all will be stored as text
private:
  static bool updatelog(String index, String value)
  {
    if(readLog(index)==value)// if the same pair is found then do not do anything
    {
      return true;
    }

    File file = SPIFFS.open("/config.txt", "r");
    if (!file)
    {
      Serial.println("Failed to open file for updating");
      return false;
    }

    String updatedContent;
    bool indexFound = false;

    while (file.available()) // reads every line, if it finds the index it updates its value and saves the whole new file in updated content
    {
      String line = file.readStringUntil('\n');
      if (line.startsWith(index + ":"))
      {
        line = index + ":" + value; // Update the line with the new value
        indexFound = true;
      }
      updatedContent += line + "\n";
    }

    file.close();

    if (!indexFound) // if it doesn't find the index it just goes back to writeLog function
    {
      return false;
    }

    file = SPIFFS.open("/config.txt", "w"); // if it found the index it will write the new data to the file
    if (!file)
    {
      Serial.println("Failed to open file for writing");
      return false;
    }

    file.print(updatedContent);
    file.close();
    return true;
  }

public:
  static String currentLogData()
  {
    String data;
    File file = SPIFFS.open("/config.txt", "r");
    if (file)
    {
      while (file.available())
      {
        data += (char)file.read();
      }
      file.close();
    }
    else
    {
      Serial.println("Failed to open file for reading");
    }
    return data;
  }

  static void writeLog(String index, String value) 
  {
    if (!updatelog(index, value)) // if update fails it appends a new line
    {
      File file = SPIFFS.open("/config.txt", "a");
      if (file)
      {
        file.print(index + ":");
        file.println(value);
        file.close();
      }
      else
      {
        Serial.println("Failed to open file for appending");
      }
    }
  }

  static void writeLog(String index, int value)
  {
    String val = String(value);
    if (!updatelog(index, val)) // if update fails it appends a new line
    {
      File file = SPIFFS.open("/config.txt", "a");
      if (file)
      {
        file.print(index + ":");
        file.println(value);
        file.close();
      }
      else
      {
        Serial.println("Failed to open file for appending");
      }
    }
  }

  static String readLog(String index)
  {
    File file = SPIFFS.open("/config.txt", "r");
    String value = "not existed!!";
    if (file)
    {
      while (file.available())
      {
        String line = file.readStringUntil('\n');
        if (line.startsWith(index))
        {
          value = (line.substring(line.indexOf(':') + 1)); // get the value
          file.close();
          return value;
        }
      }
      file.close();
    }
    return value;
  }

 static void clear() {// clears file content
    File file = SPIFFS.open("/config.txt", "w");// when i open the file in writing mode (w) it clears everything
    if (file) {
      file.close();
      Serial.println("Logging file cleared.");
    } else {
      Serial.println("Failed to open file for clearing");
    }
  }
  

};
#endif
