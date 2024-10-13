#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "http_utils.h"

void test_encode_uri(int *passed, int *total, const char *input, const char *output)
{
    char *result;
    (*total)++;
    encode_uri(input, &result);
    if (!strcmp(result, output)) 
        (*passed)++;
    else 
        fprintf(stderr, "Test case %d FAILED with result \"%s\", should be \"%s\"\n", *total,  result, output);
    free(result);
}

void test_decode_uri(int *passed, int *total, const char *input, const char *output)
{
    char *result;
    (*total)++;
    int error = decode_uri(input, &result);
    if (!error) {
        if (!strcmp(result, output)) 
            (*passed)++;
        else
            fprintf(stderr, "Test case %d FAILED with result \"%s\", should be \"%s\"\n", *total,  result, output);
    }
    else { 
        if (!strcmp(result, output)) {
            (*passed)++;
            fprintf(stderr, "Test case %d PASSED with error, input was %s, errno was %d\n", 
                    *total, input, error);
        }
        else
            fprintf(stderr, "Test case %d FAILED with result \"%s\", should be \"%s\" and error %d\n", 
                    *total,  result, output, error);
    }
    free(result);
}

void test_decode_uri_l(int *passed, int *total, const char *input, int len, const char *output)
{
    char *result;
    (*total)++;
    int error = decode_uri_l(input, &result, len);
    if (!error) {
        if (!strcmp(result, output)) 
            (*passed)++;
        else
            fprintf(stderr, "Test case %d FAILED with result \"%s\", should be \"%s\"\n", *total,  result, output);
    }
    else { 
        if (!strcmp(result, output)) {
            (*passed)++;
            fprintf(stderr, "Test case %d PASSED with error, input was %s, errno was %d\n", 
                    *total, input, error);
        }
        else
            fprintf(stderr, "Test case %d FAILED with result \"%s\", should be \"%s\" and error %d\n", 
                    *total,  result, output, error);
    }
    free(result);
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        char *result;
        int error = decode_uri(argv[1], &result);
        fprintf(stdout, "Decoded %s to %s with error code %d\n", argv[1], 
                result, error);
        free(result);
        error = decode_uri_l(argv[1], &result, 6);
        fprintf(stdout, "Decoded %s to %s with error code %d\n", argv[1], 
                result, error);
        free(result);
    }

    /**
     * Unit tests
     */
    int passed = 0;
    int total = 0;
    fprintf(stderr, "\n------BEGIN decode_uri UNIT TEST------\n");

    test_decode_uri(&passed, &total, "", "");
    test_decode_uri(&passed, &total, "Hello World", "Hello World");
    test_decode_uri(&passed, &total, "%25", "%");
    test_decode_uri(&passed, &total, "A%25", "A%");
    test_decode_uri(&passed, &total, "%25HI", "%HI");
    test_decode_uri(&passed, &total, "%2", "2");
    test_decode_uri(&passed, &total, "%00", "00");

    fprintf(stderr, "------END UNIT TEST------\n"
            "Passed %d of %d cases\n\n", passed, total);
    
    passed = 0;
    total = 0;

    fprintf(stderr, "\n------BEGIN decode_uri_l UNIT TEST------\n");

    test_decode_uri_l(&passed, &total, "", 1, "");
    test_decode_uri_l(&passed, &total, "Hello World", 5, "Hello");
    test_decode_uri_l(&passed, &total, "%25",3, "%");
    test_decode_uri_l(&passed, &total, "A%25",4, "A%");
    test_decode_uri_l(&passed, &total, "%25HI",3, "%");
    test_decode_uri_l(&passed, &total, "%2",3, "2");
    test_decode_uri_l(&passed, &total, "%00",1, "");
    test_decode_uri_l(&passed, &total, "%00",2, "0");
    test_decode_uri_l(&passed, &total, "%00",3, "00");

    fprintf(stderr, "------END UNIT TEST------\n"
            "Passed %d of %d cases\n", passed, total);
 
    passed = 0;
    total = 0;
    fprintf(stderr, "\n------BEGIN encode_uri UNIT TEST------\n");

    test_encode_uri(&passed, &total, "", "");
    test_encode_uri(&passed, &total, "Hello", "Hello");
    test_encode_uri(&passed, &total, "Hello World", "Hello%20World");
    test_encode_uri(&passed, &total, "%", "%25");

    fprintf(stderr, "------END UNIT TEST------\n"
            "Passed %d of %d cases\n\n", passed, total);
 

    return 0;
}