#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdlib.h>
#include <stddef.h>
#include <time.h>


void *my_memcpy(void *dest, const void *src, size_t n);
void my_strlen_V2(const char *str, size_t *lengthPtr);
char *my_strcpy(char *dest, const char *src);
int my_strlen(const char *str);
char *my_Mstrcpy1(char *dest, const char *src);
char *my_Mstrcpy2(const char *src);
char *my_MstrNcpy(const char *src, size_t count);
char *my_strdupN(const char *src, int nb_de_fois);
char *my_strtrim(char *src);
char *my_strtrimCar(char *src, char *asup);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, size_t count);
int my_strcspn(const char *str, const char *charset);
int my_strcmp(char *str1, char *str2);
char *my_strdup(const char *src);
char *my_strtok(char *str, const char *delim);
char* my_strftime(struct tm *timeinfo);
#endif /*MY_STRING_H*/
