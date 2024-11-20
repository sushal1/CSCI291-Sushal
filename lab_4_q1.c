#include <stdio.h>

int main() {
    FILE *fptr;
    FILE *outp;
    char content[1000];
    float value;
    int invalidCount = 0;

    fptr = fopen("data.txt", "r");
    if (fptr == NULL) {
        printf("could not open input file\n");
        return 1;
    }
    printf("File is open\n");

    outp = fopen("output.txt", "w");
    if (outp == NULL) {
        printf("could not create output file.\n");
        fclose(fptr);
        return 1;
    }

    while (fscanf(fptr, "%s", content) != EOF) {
        if (sscanf(content, "%f", &value) == 1) {
            fprintf(outp, "%.1f\n", value);
        } else {
            invalidCount++;
        }
    }

    printf("Number of invalid float values: %d\n", invalidCount);

    fclose(fptr);
    fclose(outp);

    return 0;
}