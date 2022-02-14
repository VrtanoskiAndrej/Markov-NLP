#ifndef MARKOV_MATRIX_H
#define MARKOV_MATRIX_H

enum axis {ROW, COL};

using namespace std;

class Matrix {
public:
    Matrix(int size);
    ~Matrix();
    int get(int row, int col) const;
    void set(int data, int row, int col) const;
    void add(int data, int row, int col) const;
    void add(Matrix &matrix) const;
    int max() const;
    int sum_axis(axis, int index) const;
    int size;
    int *m;
    void update(char *buffer) const;
    void update(ifstream &file) const;
    char *predict(char start_char, int length);
    double *stochastic();
};

#endif