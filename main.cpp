#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h>
#include "markov_matrix.h"
#include "utils.h"

#define M_SIZE 27

int main(int argc, char **argv) {
    int length = 100;
    char *filename = "dataset/gullivers.txt";
    char start_char = 't';
    ifstream file(filename);
    Matrix m(M_SIZE);
    m.update(file);
    display(m);
}