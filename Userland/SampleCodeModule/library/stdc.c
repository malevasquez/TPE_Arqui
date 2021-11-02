#include <stdc.h>
#include <stdint.h>
#include <stdarg.h>

int atoi(char * str){
  int aux = 0;
  while (*str!=0){
    aux = aux*10 + (*str)+'0';
    str++;
  }
  return aux;
}

int atohex(char * str) {
  int aux = 0;
  while (*str!= 0) {
    int value = 0;
    if (*str >= '0' && *str <= '9') {
      value = *str - '0';
    } else if (*str >= 'A' && *str <= 'F') {
      value = 10 + *str - 'A';
    } else if (*str >= 'a' && *str <= 'f') {
      value = 10 + *str - 'a';
    } else {
      return -1;
    }
    str++;
    aux *= 16;
    aux += value;
  }
  return aux;
}
char toLower(char letter){
  if (letter<='Z' && letter>='A'){
    return letter+'a'-'A';
  }
  return letter;
}

char toUpper(char letter){
  if (letter<='z' && letter>='a'){
    return letter+'A'-'a';
  }
  return letter;
}

int intToBase(unsigned long long num, int base, char*buffer){
    if (num == 0) {
      buffer[0] = '0';
      buffer[1] = 0;
      return 2;
    }
    char stack[11];
    int c = 0;
    int i=0;
    int remainder = 0;
    if(num==0) stack[i++]='0';
    while(num!=0){
        remainder = num % base;
        stack[i]=remainder>=10? remainder+'A'-10:remainder+'0';
        num = num/base;
        i++;
    }
    c=i;
    i--;
    while(i>=0){
        *buffer=stack[i];
        buffer++;
        i--;
    }
    *buffer=0;
    return c;
}

int iabs(int num){
  if (num < 0){
   return -num;
  }
  return num;
}


int intToString(unsigned long long num, char * buffer){
  return intToBase(num,10,buffer);
}

int strlen(char *str){
  int i =0;
  for ( i = 0; *(str+i); i++)
  {

  }
  return i;
}

int strcmp(char * str1, char * str2){
    int i =0;
    while(str1[i] != 0 && str2[i] != 0 ){
        if(str1[i] != str2[i]){
            return str1[i]-str2[i];
        }
        i++;
    }
    return str1[i]-str2[i];
}

char * strcpy(char * dest, char * src) {
  for (int i = 0; src[i] != 0; i++) {
    dest[i] = src[i];
  }
  return dest;
}

/*
***************************************************
***************************************************
*/

void (*updateConsolePointer)(char *, int);
uint8_t updateConsoleInitialized = 0;

void scanf(char * buff) {
  int ch = 0;
  int index = 0;
  while(ch != '\n') {
    if(ch)
      buff[index++] = ch;
      putChar(ch);
      ch = getChar();
  }
  putChar('\n');
}

void printf(char * str, ...) {
  va_list vl;
  va_start(vl, str);
  char * auxPtr;
  char buffer[128] = {0};
  char tmp[20];
  int i = 0, j = 0;
  while (str && str[i]) {
    if (str[i] == '%') {
      i++;
      switch(str[i]) {
        case 'c':
        buffer[j++] = (char)va_arg( vl, int );
        break;
        case 'd':
        intToString(va_arg( vl, int ), tmp);
        strcpy(&buffer[j], tmp);
        j+=strlen(tmp);
        break;
        case 's':
        auxPtr = va_arg(vl, char*);
        strcpy(&buffer[j],auxPtr);
        j+=strlen(auxPtr);
        break;
        case 'x':
        intToBase(va_arg( vl, int ),16, tmp);
        strcpy(&buffer[j], tmp);
        j+=strlen(tmp);
        break;
        case 'X': //long hexa
        intToBase(va_arg( vl, uint64_t ),16, tmp);
        strcpy(&buffer[j], tmp);
        j+=strlen(tmp);
        break;
      }
    } else {
      buffer[j++] = str[i];
    }
    i++;
  }
  updateConsolePointer(buffer, j);
}

void putChar(char ch) {
  updateConsolePointer(&ch, 1);
}

int readKeyboard(char * buffer, int size) {
  if (size == 0) return 0;
  uint64_t aux;
  //isKeyboardEmptySyscall(&aux);
  uint64_t count = 0;
  if (aux) {
    //readKeyboardSysCall(buffer, (uint8_t) size, &count);
    return 1;
  }
  return 0;
}

void setConsoleUpdateFunction(void (*f)(char *, int)) {
  updateConsolePointer = f;
  updateConsoleInitialized = 1;
}

char getChar() {
  char ch = 0;
  uint64_t count;
  while(ch == 0 || count == 0) {
    //readKeyboardSysCall(&ch, 1, &count);
  }
  return ch;
}

int getError() {
  uint64_t err = 32;
  //readErrorSyscall(&err);
  return err;
}
