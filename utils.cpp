#include <iostream>
#include "utils.h"

/** ctoi
 * Converts a character into an integer representation
 * with space = 0, a = 1 and z = 26
 * @param c character input
 * @return integer representation
 */
int ctoi(char c) {
    return ((c | 32) >= 'a' && (c | 32) <= 'z') ? c % 32 : -1 + (c == 32);
}


/** itoc
 * Converts an integer back to a character
 * @param i integer to be converted
 * @return character representation
 */
char itoc(int i) {
    return (i == 0) ? ' ' : i + 'a' - 1;
}

/** digit_count
 * Finds the amount of digits required to represent a number in decimal
 * @param i integer to be converted
 * @return int number of digits
 */
int digit_count(int i) {
    int digits = 1;
    while (i > 10) {
        digits++;
        i /= 10;
    }
    return digits;
}

/** display
 * Outputs the markov table
 * @param arr pointer to the markov matrix
 */
void display(Matrix &m) {
    int d = digit_count(m.max()) + 1;
    printf("--- MATRIX TABLE --- [FROM ^] [TO >]\n");
    printf("%-*c%-*c", d, '*', d, '_');
    for (int h = 1; h < m.size; h++) {
        printf("%-*c", d, itoc(h));
    }
    printf("  @\n");

    for (int i = 0; i < m.size; i++) {
        printf("%-*c", d, itoc(i));
        for (int j = 0; j < m.size; j++) {
            printf("%-*d", d, m.get(i, j));
        }
        printf("%-*d \n", d, m.sum_axis(ROW, i));
    }
}

/** display_stochastic
 * Outputs the markov table in decimal format
 * @param arr pointer to the markov matrix
 */
void display_stochastic(Matrix &m) {
    printf("--- MATRIX TABLE --- [FROM ^] [TO >]\n");
    printf("%-8c", '*');
    for (int h = 0; h < m.size; h++) {
        printf("%-6c", itoc(h));
    }
    printf("\n");

    for (int i = 0; i < m.size; i++) {
        printf("%-6c", itoc(i));
        for (int j = 0; j < m.size; j++) {
            int freq = m.sum_axis(ROW, i);
            if (freq != 0) {
                printf("%-6.3f", (double)  m.get(i, j) / freq);
            } else {
                printf("%-6.3f", 0.0);
            }
        }
        printf("\n");
    }
}

/** write_csv
 * Writes the data of the matrix to a csv file
 * @param matrix pointer to the markov matrix
 * @param file name of the file to write
 */
void write_csv(Matrix &matrix, ofstream &file){
    //TODO: implement character buffer to reduce fprintf calls
    for(int i = 0; i < matrix.size; i++) {
        for(int j = 0; j < matrix.size-1; j++){
            file << matrix.get(i, j) << ", ";
        }
        file << matrix.get(i, matrix.size-1) << endl;
    }
    file.close();
}

/** read_csv
 * Writes the data of the matrix to a csv file
 * @param matrix pointer to the markov matrix
 * @param file input file stream to read from
 * @return MarkovMatrix containing information from the csv file
 */
Matrix *read_csv(ifstream &file){
    // TODO: create support for different sized input types
    Matrix *matrix = new Matrix(27);

    char line[4098];
    int i = 0;
    while (file.getline(line, 4098, '\n') != nullptr) {
        char* tmp = strdup(line);
        printf("line %d - %s", i, line);
        int j = 0;
        const char* tok;
        for (tok = strtok(line, ","); tok && *tok; j++, tok = strtok(NULL, ",\n")) {
            matrix->set(atoi(tok), i, j);
        }
        free(tmp);
        i++;
    }
    file.close();
    return matrix;
}
