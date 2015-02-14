#include "win.h"


// Define Basic Message functions

int Errmsg(char *str) {
  return(MessageBox(NULL, str, "", MB_OKCANCEL));
}

void Message(char *str1, char *str2) {
  MessageBox(NULL, str1, str2, MB_OK);
}


