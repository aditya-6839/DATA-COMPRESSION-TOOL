#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compressRLE(char *inputFile, char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening files.\n");
        return;
    }
    char current, previous;
    int count = 1;
    previous = fgetc(in);
    while ((current = fgetc(in)) != EOF) {
        if (current == previous) {
            count++;
        } else {
            fprintf(out, "%c%d", previous, count);
            previous = current;
            count = 1;
        }
    }
    fprintf(out, "%c%d", previous, count);
    fclose(in);
    fclose(out);
    printf("File compressed successfully.\n");
}

void decompressRLE(char *inputFile, char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (!in || !out) {
        printf("Error opening files.\n");
        return;
    }
    char character;
    int count;
    while (fscanf(in, "%c%d", &character, &count) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(character, out);
        }
    }
    fclose(in);
    fclose(out);
    printf("File decompressed successfully.\n");
}

int main() {
    int choice;
    char inputFile[100], outputFile[100];
    do {
        printf("\nData Compression Tool:\n");
        printf("1. Compress File (RLE)\n");
        printf("2. Decompress File (RLE)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1 || choice == 2) {
            printf("Enter input file name: ");
            scanf("%s", inputFile);
            printf("Enter output file name: ");
            scanf("%s", outputFile);
        }
        switch (choice) {
            case 1:
                compressRLE(inputFile, outputFile);
                break;
            case 2:
                decompressRLE(inputFile, outputFile);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);
    return 0;
}
