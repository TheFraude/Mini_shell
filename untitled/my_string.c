#include "my_string.h"

void my_strlen_V2(const char *str, size_t *lengthPtr) {
    size_t length = 0;
    const char *p = str;
    while(*p != '\0'){
        length++;
        p++;
    }
    *lengthPtr = length;
}

void *my_memcpy(void *dest, const void *src, size_t n) {
    /*Vérification des pointeurs non nuls*/
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    /* Conversion des pointeurs en tableau d'octets (unsigned char*)*/
    unsigned char *destination = (unsigned char *)dest;
    const unsigned char *source = (const unsigned char *)src;

    /*Copie des données*/
    size_t i;
    for (i=0; i < n; ++i) {
        destination[i] = source[i];
    }

    return dest;
}

char *my_strcpy(char *dest, const char *src){
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; /* Ajout du caractère nul de fin de chaîne*/
    return dest;
}

int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char *my_Mstrcpy1(char *dest, const char *src) {
    int length = 0;
    while (src[length] != '\0') {
        length++;
    }
    dest = (char *)malloc((length + 1) * sizeof(char));
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_Mstrcpy2(const char *src) {
    int length = 0;
    while (src[length] != '\0') {
        length++;
    }
    char *dest = (char *)malloc((length + 1) * sizeof(char));
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_MstrNcpy(const char *src, size_t count) {
    size_t length = 0;
    while (src[length] != '\0') {
        length++;
    }

    char *dest = (char *)malloc((length - count + 1) * sizeof(char));
    size_t i;
    for (i = 0; i < length - count; i++) {
        dest[i] = src[count + i];
    }
    dest[length - count] = '\0';

    return dest;
}

char *my_strdupN(const char *src, int nb_de_fois){
    int length = 0;
    while (src[length] != '\0') {
        length++;
    }
    int totalLength = nb_de_fois * length;
    char *dest = (char *)malloc((totalLength + 1) * sizeof(char));

    int i, j;
    for (i = 0; i < nb_de_fois; i++) {
        for (j = 0; j < length; j++) {
            dest[i * length + j] = src[j];
        }
    }
    dest[totalLength] = '\0';
    return dest;
}

char *my_strtrim(char *src){
    size_t length;
    my_strlen_V2(src, &length);
    int count = 0;
    int i;
    for (i = 0; i < length; i++) {
        if (src[i] != '\0')
        {
            src[count++] = src[i];
        }
    }
    src[count] = '\0';
    return src;
}

char *my_strtrimCar(char *src, char *asup) {
    size_t srcLength = 0;
    size_t asupLength = 0;
    my_strlen_V2(src, &srcLength);
    my_strlen_V2(asup, &asupLength);
    size_t count = 0;
    size_t i;
    for (i = 0; i < srcLength; i++) {
        char c = src[i];
        int found = 0;
        size_t j;
        for (j = 0; j < asupLength; j++) {
            if (c == asup[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            src[count++] = c;
        }
    }
    src[count] = '\0';
    return src;
}


char *my_strcat(char *dest, const char *src) {
    size_t destLength = 0;
    size_t srcLength = 0;
    my_strlen_V2(dest, &destLength);
    my_strlen_V2(src, &srcLength);
    size_t totalLength = destLength + srcLength;
    char *result = (char *)malloc((totalLength + 1) * sizeof(char));
    size_t i;
    for (i = 0; i < destLength; i++) {
        result[i] = dest[i];
    }
    for (i = 0; i < srcLength; i++) {
        result[destLength + i] = src[i];
    }
    result[totalLength] = '\0';
    return result;
}

char *my_strncat(char *dest, const char *src, size_t count) {
    size_t destLength = 0;
    size_t srcLength = 0;
    my_strlen_V2(dest, &destLength);
    my_strlen_V2(src, &srcLength);
    size_t totalLength = destLength + count;
    char *result = (char *)malloc((totalLength + 1) * sizeof(char));
    size_t i;
    for ( i = 0; i < destLength; i++) {
        result[i] = dest[i];
    }
    for ( i = 0; i < count; i++) {
        result[destLength + i] = src[i];
    }
    result[totalLength] = '\0';
    return result;
}

int my_strcspn(const char *str, const char *charset) {
    const char *s1, *s2;
    int count = 0;
    /*Parcours de la chaîne principale*/
    for (s1 = str; *s1 != '\0'; s1++) {
        /* Parcours de l'ensemble de caractères à éviter*/
        for (s2 = charset; *s2 != '\0'; s2++) {
            /* Vérifie si le caractère actuel de la chaîne est présent dans l'ensemble*/
            if (*s1 == *s2) {
                /* Caractère trouvé, retourne la longueur jusqu'à ce point*/
                return count;
            }
        }
        /*Aucun caractère de l'ensemble trouvé, incrémente la longueur du préfixe*/
        count++;
    }
    /* Tous les caractères de la chaîne sont valides, retourne la longueur totale*/
    return count;
}


int my_strcmp(char *str1, char *str2) {
    while(*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char *my_strdup(const char *src){
    if (src==NULL){
        return NULL;
    }
    size_t taille = 0;
    while (src[taille] !='\0') {
        taille++;
    }
    char *dest = (char *)malloc((taille+1)); /* Alloc de la chaine à dup*/
    if (dest==NULL) {
        return NULL;
    }
    size_t i;
    for ( i=0; i<=taille; i++){ /* Copie de src dans dest*/
        dest[i]=src[i];
    }

    return dest;

}
char *my_strtok(char *str, const char *delim) {
    static char* buffer;
    if(str != NULL) buffer = str;
    if(buffer == NULL) return NULL;

    char *ret = buffer, *b;
    const char *d;

    for(b = buffer; *b !='\0'; b++) {
        for(d = delim; *d != '\0'; d++) {
            if(*b == *d) {
                *b = '\0';
                buffer = b + 1;

                if(b == ret) {
                    ret++;
                    continue;
                }
                return ret;
            }
        }
    }

    buffer = NULL;
    return ret;
}

#include <time.h>
#include <stdio.h>

char* my_strftime(struct tm *timeinfo) {
    char *buffer = (char *)malloc(sizeof(char) * 80);

    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", timeinfo);
    return buffer;
}
