#include <cstdlib>
#include <string>
#include "markov_matrix.h"
#include "utils.h"

/** Matrix
 * Initializes a matrix from a given size, mallocing a flat backing array
 * @param s int size of square matrix
 */
Matrix::Matrix(int s) {
    size = s;
    m = (int *) malloc(sizeof(int) * size * size);
    memset(m, 0, size * size * sizeof(int));
}

/** ~Matrix
 * Deletes the matrix and frees the associated backing array
 */
Matrix::~Matrix(){
    free(m);
}

/** get
 * Gets data from a given element
 * @param row row index
 * @param cow column index
 * @return data returned from the array
 */
inline int Matrix::get(int row, int col) const {
    return m[row * size + col];
}

/** set
 * Assigns data to a given element in the matrix
 * @param data int data to set to the element specified
 * @param row row index
 * @param cow column index
 */
inline void Matrix::set(int data, int row, int col) const {
    m[row * size + col] = data;
}

/** add
 * Adds some data into an element in the matrix
 * @param data int data to add to the element specified
 * @param row row index
 * @param cow column index

 */
inline void Matrix::add(int data, int row, int col) const {
    set(m[row * size + col] + data, row, col);
}

/** add
* Element wise add each element in the input matrix to the given matrix
* @param other_matrix other matrix to element wise add
*/
void Matrix::add(Matrix &other_matrix) const {
    for (int i = 0; i < size*size; i++){
        m[i] += other_matrix.m[i];
    }
}

/** max
 * Finds the maximum integer in the matrix
 * @return maximum int
 */
int Matrix::max() const {
    int greatest = 0;
    for (int i = 0; i < size*size; i++) {
        if (m[i] > greatest) {
            greatest = m[i];
        }
    }
    return greatest;
}

/** sum_axis
 * Sums all the entries in the given axis and index
 * @param ax row or column sum
 * @param index point in the matrix through which to sum
 * @return int summed count
 */
int Matrix::sum_axis(axis ax, int index) const {
    int sum = 0;
    switch (ax) {
        case ROW:
            for (int d = 0; d < size; d++) {
                sum += get(index, d);
            }
            break;

        case COL:
            for (int d = 0; d < size; d++) {
                sum += get(d, index);
            }
            break;
    }
    return sum;
}

/** update
 * Generates the markov matrix while looping through a null-terminated character array
 * @param buffer null-terminated characters to add into the matrix
 */
void Matrix::update(char *buffer) const {
    for(char *next = buffer + 1; *next != '\0'; next++, buffer++){
        int a = ctoi(*buffer);
        int b = ctoi(*next);
        // TODO: optimize character validation
        // If you know that a is invalid, then the next does not need to be checked becuase then b will be invalid
        if (a != -1 && b != -1) {
            add(1, a, b);
        }
    }
}

/** update
 * Generates the markov table while looping through an input stream
 * @param infile input file stream
 */
void Matrix::update(ifstream &infile) const {
    if (infile == nullptr) {
        return;
    }
    int buffer_size = 500;
    char buf[buffer_size];
    while (infile.getline(buf, buffer_size) != nullptr) {
        update(buf);
    }
    infile.close();
}


/** predict
 * Generates a string sequence based off of the markov chain of a given length
 * @param init_state first character to initialize the sequence
 * @param length size of the sequence generated
 * @return character array
 */
char *Matrix::predict(char init_state, int length) {
    if (length == 0 || ctoi(init_state) == -1){
        return nullptr;
    }
    char *output;
    if ((output = (char *) malloc(sizeof (char)*(length+1))) == nullptr) {
        return nullptr;
    }

    // initialize singleton seed
    static long seed = 0;
    if (seed == 0){
        seed = time(0);
        srand(seed);
    }

    int current_state = ctoi(init_state);
    output[0] = init_state;
    for (int i = 0; i < length-1; i++) {
        int row_sum = sum_axis(ROW, current_state);
        if (row_sum == 0) {
            printf("\n reached empty state");
            return NULL;
        }
        int choice = rand() % row_sum;
        int rolling_sum = get(current_state, 0);
        int next_state = 0;

        while (rolling_sum < choice) {
            rolling_sum += get(current_state, next_state);
            next_state++;
        }
        output[i+1] = itoc(next_state);
        current_state = next_state;
    }
    output[length+1] = '\0';
    return output;
}

/** stochastic
 * Converts markov frequency matrix into its stochastic matrix form
 * @return double * stochastic matrix
 */
double *Matrix::stochastic(){
    double *stochastic_matrix;
    if ((stochastic_matrix = (double *) malloc(sizeof(double *) * size)) == nullptr) {
        return nullptr;
    }

    int freq_table[size];
    for(int i = 0; i < size; i++) {
        freq_table[i] = sum_axis(ROW, i);
    }

    for(int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
            if (freq_table[i] == 0) {
                stochastic_matrix[i * size + j] = 0;
            } else {
                stochastic_matrix[i * size + j] = (double) get(i, j) / freq_table[i];
            }
        }
    }
    return stochastic_matrix;
}

