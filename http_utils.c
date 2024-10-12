#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "http_utils.h"

int decode_uri(const char* str, char **res)
{
    char *result = malloc((strlen(str) + 1) * sizeof(char));
    *res = result;
    if (result == NULL) {
        perror("Malloc Failed");
        return -1;
    }
    char *curr_str = str;
    char *curr_res = *res;
    int errnum = 0;
    while (*curr_str) {
        if (*curr_str != '%') {
            *curr_res = *curr_str;
            curr_str++;
            curr_res++;
            continue;
        }
        if (strlen(curr_str) < 3) {
            *curr_str = '%';
            errnum++; 
        }
        int charnum;
        sscanf(curr_str, "%%%x2.", &charnum);
        

    }
    curr_res = 0;
    *res = realloc(result, (strlen(result) + 1) *sizeof(char));
    return errnum;
}

int decode_uri_l(const char* str, char **res, int len)
{


    return 0;
}

int encode_uri(const char* str, char **res)
{


    return 0;
}

int encode_uri_l(const char* str, char **res, int len)
{


    return 0;
}