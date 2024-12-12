#include "base64.h"
#include <stdlib.h>
#include <string.h>

const char* base64_map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int Base64CharValue(char c) {
    if ('A' <= c && c <= 'Z')
        return c - 'A';

    if ('a' <= c && c <= 'z')
        return c - 'a' + 26;

    if ('0' <= c && c <= '9')
        return c - '0' + 52;

    if (c == '+')
        return 62;

    if (c == '/')
        return 63;

    return -1;
}

int Base64Encoding(const unsigned char* inputData, char* outputData) {

    if (!inputData || !outputData)
        return -1;

    int dataLength = strlen((const char*)inputData);
    int outputLength = 4 * ((dataLength + 2) / 3);
    int i, j;

    for (i = 0, j = 0; i < dataLength;) {
        unsigned int octet_a = i < dataLength ? inputData[i++] : 0;
        unsigned int octet_b = i < dataLength ? inputData[i++] : 0;
        unsigned int octet_c = i < dataLength ? inputData[i++] : 0;

        unsigned int triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        outputData[j++] = base64_map[(triple >> 18) & 0x3F];
        outputData[j++] = base64_map[(triple >> 12) & 0x3F];
        outputData[j++] = (i > dataLength + 1) ? '=' : base64_map[(triple >> 6) & 0x3F];
        outputData[j++] = (i > dataLength) ? '=' : base64_map[triple & 0x3F];
    }

    int mod = dataLength % 3;

    if (mod == 1) {
        outputData[outputLength - 1] = '=';
        outputData[outputLength - 2] = '=';
    } else if (mod == 2) {
        outputData[outputLength - 1] = '=';
    }

    outputData[outputLength] = '\0';
    return outputLength;
}



int Base64Decoding(const unsigned char* inputData, char* outputData) {

    if (!inputData || !outputData)
        return -1;

    int dataLength = strlen((const char*)inputData);

    if (dataLength % 4 != 0)
        return -1;

    int outputLength = dataLength / 4 * 3;

    if (inputData[dataLength - 1] == '=')
        outputLength--;

    if (inputData[dataLength - 2] == '=')
        outputLength--;

    int i, j;

    for (i = 0, j = 0; i < dataLength;) {
        unsigned int group_a = inputData[i] == '=' ? 0 & i++ : Base64CharValue(inputData[i++]);
        unsigned int group_b = inputData[i] == '=' ? 0 & i++ : Base64CharValue(inputData[i++]);
        unsigned int group_c = inputData[i] == '=' ? 0 & i++ : Base64CharValue(inputData[i++]);
        unsigned int group_d = inputData[i] == '=' ? 0 & i++ : Base64CharValue(inputData[i++]);

        if (group_a == -1 || group_b == -1 || group_c == -1 || group_d == -1) return -1;

        unsigned int triple = (group_a << 18) | (group_b << 12) | (group_c << 6) | group_d;

        if (j < outputLength)
            outputData[j++] = (triple >> 16) & 0xFF;

        if (j < outputLength)
            outputData[j++] = (triple >> 8) & 0xFF;

        if (j < outputLength)
            outputData[j++] = triple & 0xFF;
    }

    outputData[j] = '\0';
    return outputLength;
}
