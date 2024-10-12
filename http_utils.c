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
    const char *curr_str = str;
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
            curr_str++;
            errnum++; 
            continue;
        }
        unsigned int charnum;
        sscanf(curr_str+1, "%2X", &charnum);
        if (charnum == 0)
            sscanf(curr_str+1, "%2x", &charnum);
        if (charnum == 0) {
            errnum++;
            curr_str++;
            continue;
        }
        *curr_res = (char) charnum;
        curr_res++;
        curr_str += 3;
    }
    *curr_res = 0;
    *res = realloc(result, (strlen(result) + 1) *sizeof(char));
    return errnum;
}

int decode_uri_l(const char* str, char **res, int len)
{
    char *result = malloc((len + 1) * sizeof(char));
    *res = result;
    if (result == NULL) {
        perror("Malloc Failed");
        return -1;
    }
    const char *curr_str = str;
    char *curr_res = *res;
    int errnum = 0;
    while (*curr_str && curr_str < str + len) {
        if (*curr_str != '%') {
            *curr_res = *curr_str;
            curr_str++;
            curr_res++;
            continue;
        }
        if (strlen(curr_str) < 3 || curr_str +3 > str + len) {
            curr_str++;
            errnum++; 
            continue;
        }
        unsigned int charnum;
        sscanf(curr_str+1, "%2X", &charnum);
        if (charnum == 0)
            sscanf(curr_str+1, "%2x", &charnum);
        if (charnum == 0) {
            errnum++;
            curr_str++;
            continue;
        }
        *curr_res = (char) charnum;
        curr_res++;
        curr_str += 3;
    }
    *curr_res = 0;
    *res = realloc(result, (strlen(result) + 1) *sizeof(char));
    return errnum;
}

int encode_uri(const char* str, char **res)
{
    char *result = malloc((strlen(str)* 3 + 1)* sizeof(char));
    *res = result; 
    if (result == NULL) {
        perror("malloc failed on encode_uri");
        return -1;
    }

    char *curr_str = str;
    char *curr_res = result;
    while (*curr_str) {
        if (    ('a' <= *curr_str && *curr_str <= 'z') ||
                ('A' <= *curr_str && *curr_str <= 'Z') ||
                ('0' <= *curr_str && *curr_str <= '9')) {
            *curr_res = *curr_str;
            curr_str++;
            curr_res++;
            continue;
        }
    }
    *res = realloc(result, (strlen(result) + 1) * sizeof(char));
    return 0;
}

int encode_uri_l(const char* str, char **res, int len)
{


    return 0;
}