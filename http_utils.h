/**
 * http_utils.h
 * Copyright (C) 2024 Mason McVey
 * 
 * Mason McVey
 * mason.mcvey@columbia.edu
 */
#ifndef FILE_REQUEST_SEEN
#define FILE_REQUEST_SEEN

int decode_uri(const char* str, char **res);

int decode_uri_l(const char* str, char **res, int len);

int encode_uri(const char* str, char **res);

int encode_uri_l(const char* str, char **res, int len);

//int parse_uri

#endif