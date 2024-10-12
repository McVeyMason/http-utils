#include <stdio.h>
#include <stdlib.h>

#include "http_utils.h"


int main(int argc, char **argv)
{
    if (argc > 1) {
        char *result;
        int error = decode_uri(argv[1], &result);
        fprintf(stdout, "Decoded %s to %s with error code %d\n", argv[1], 
                result, error);
        free(result);
    }
    return 0;
}