#ifndef UTILS_H
#define UTILS_H
#include <fstream>
#include <iostream>
#include "markov_matrix.h"

int ctoi(char c);
char itoc(int i);
void display(Matrix &matrix);
void display_stochastic(Matrix &matrix);
void write_csv(Matrix &matrix, ofstream &file);
Matrix *read_csv(ifstream &file);

#endif