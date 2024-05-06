// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 44      /* Bytes for the header in .wav */
#define ARGC_AMOUNT 4       /* Amount of parameters when called file */

enum {
    ARGV_PATH,
    ARGV_INPUT,
    ARGV_OUTPUT,
    ARGV_FACTOR
};

void copyHeader(FILE *, FILE **);
void ampWav(FILE *, FILE **, float);

int main(int argc, char *argv[]) {
    if (argc != ARGC_AMOUNT) {
        printf("Usage: ./volume input.wav output.wav factor\n");

        return 1;
    }

    FILE *pInput = fopen(argv[ARGV_INPUT], "rb");
    FILE *pOutput = fopen(argv[ARGV_OUTPUT], "wb");

    if (pInput == NULL || pOutput == NULL) {
        printf("Could not open file.\n");

        return 1;
    }

    float factor = atof(argv[ARGV_FACTOR]);

    copyHeader(pInput, &pOutput);
    ampWav(pInput, &pOutput, factor);

    fclose(pInput);
    fclose(pOutput);
}

void copyHeader(FILE *pInput, FILE **pOutput) {
    uint8_t *header;

    if((header = malloc(HEADER_SIZE * sizeof(uint8_t))) == NULL) {
        printf("There is no more space in memory.\n");

        exit(1);
    }

    fread(header, sizeof(uint8_t), HEADER_SIZE, pInput);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, *pOutput);

    free(header);
}

void ampWav(FILE *pInput, FILE **pOutput, float factor) {
    int16_t *buffer;

    if((buffer = malloc(sizeof(int16_t))) == NULL) {
        printf("There is no more space in memory.\n");

        exit(1);
    }

    while(fread(buffer, sizeof(int16_t), 1, pInput)) {
        (*buffer) *= factor;

        fwrite(buffer, sizeof(int16_t), 1, *pOutput);
    }

    free(buffer);
}