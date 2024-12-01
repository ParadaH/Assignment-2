#ifndef __LCD_SCREEN_DISPLAY__
#define __LCD_SCREEN_DISPLAY__

extern String pressCloseMsg;
extern String wasteReceivedMsg;
extern String containerFullMsg;
extern String pressOpenMsg;
extern String containerAlarm;

void LCDInit();
void LCDupdate(String message);
void checkMessageLength(const String &input, String &line1, String &line2);
void LCDTurnOff();
void LCDTurnOn();

#endif