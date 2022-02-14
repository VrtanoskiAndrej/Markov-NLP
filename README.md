# Markov-NLP

Markov chains are stochastic models with the property such that next states are solely determined by the current state. They
are very useful for modeling how basic language is constructed, through rough statistical approximations and a multitude of data. For implementations, a
Markov chain is backed by a Markov matrix, which is a stochastic matrix that is square and has the property such that the sum of the rows add up to one.
The transition between states can be set up such that for a given matrix P, the probability of transition from state f to state g is determined counter intuitively
by the P[i][j] th value in the matrix.

## Markov Model for Text Generation
character sequence = "hello world"
’h’ → ’e’ → ’l’ → l’ → ’o’ → ’ ’ → ’w’ → ’o’ → ’r’ → ’l’ → ’d’

The given sequence can be broken down into its individual characters, with the character to its right representing the next state of the Markov chain,
similar to a linked list. Firstly, we will need to convert the sequence into its frequency table, in order to generate the stochastic matrix. This can be done
by simple looping through the sequence and counting the occurrences of the current and next character pairs. The transition ’h’ → ’e’ is depicted as a 1 in
the matrix’s ’h’ column and ’e’ row, as there is only one occurrence of that pattern in the sequence, if there were to be more of that transition, the value in
the matrix will be incremented by each occurrence.

The frequency matrix is then converted to the following Markov matrix. This can be done by summing each column and them multiplying the entries
by the reciprocal of the sum, in order to get a probability vector that sums to 1. This is repeated for every vector in the matrix.

## Running the project

Requirments:
The project is build using mpic++, so you will need to install it. 
 
Mac - `brew install mpich`
Linux - `sudo apt install mpich`

To make the project just use the following command
`$ make `

Then to run the code on a given number of processors
`mpirun -np <num_processors> ./markov

