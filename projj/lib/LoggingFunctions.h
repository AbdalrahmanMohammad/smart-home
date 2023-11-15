#include "handlersFunctions.h"

/////////  you don't need to use update function here, you just use writeLog and it internally uses update if necessary
////////   i have three overloaded functions for writeLog, depending on the value (string, int, boolean)
////////   they all will be stored as text 

String currentLogData()
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

bool updatelog(String index, String value)
{
  File file = SPIFFS.open("/config.txt", "r");
  if (!file)
  {
    Serial.println("Failed to open file for updating");
    return false;
  }

  String updatedContent;
  bool indexFound = false;

  while (file.available())     // reads every line, if it finds the index it updates its value and saves the whole new file in updated content
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

  if (!indexFound)  // if it doesn't find the index it just goes back to writeLog function
  {
    return false;
  }

  file = SPIFFS.open("/config.txt", "w");  // if the it found the index it will write the new data to the file
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return false;
  }

  file.print(updatedContent);
  file.close();
  return true;
}

void writeLog(String index, const char* value) // keep it char* because if you make it string it will get confused with bool
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

void writeLog(String index, int value)
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

void writeLog(String index, boolean value)
{
  String val=value?"truee":"falsee"; // you keep it like this if you write them properly they'll be saved as 0,1
                                    // and in this way they work just fine with readLog func. and when it delete
                                    // the last string they will appear as true, false while in current content 
                                    // they appear as truee, falsee. i don't know how this happens, but it's just fine
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

String readLog(String index)
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
        value = value.substring(0, value.length() - 1);  // there is a hidden character at the end of the value here we delete it
        file.close();
        return value;
      }
    }
    file.close();
  }
  return value;
}