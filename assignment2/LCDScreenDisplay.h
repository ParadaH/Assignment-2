#ifndef __LCDSCREENDISPLAY__
#define __LCDSCREENDISPLAY__

// String pressOpenMsg = "PRESS OPEN TO ENTER WASTE";
// String pressCloseMsg = "PRESS CLOSE WHEN DONE";
// String wasteReceivedMsg = "WASTE RECEIVED";



void LCDInit();
void LCDupdate(String message);
void checkMessageLength(const String &input, String &line1, String &line2);

#endif