#initialize variables
MATRIX_SIZE=500
NUMBER_OF_THREADS=10
BIN_DIR=./bin
OUTPUT_DIR=./output
LOCATION_OF_A=$OUTPUT_DIR/A.txt
LOCATION_OF_B=$OUTPUT_DIR/B.txt
LOCATION_OF_C1=$OUTPUT_DIR/C1.txt
LOCATION_OF_C2=$OUTPUT_DIR/C2.txt

#create directories if they don't exist
mkdir -p $BIN_DIR
mkdir -p $OUTPUT_DIR

#compile programs
cc -o $BIN_DIR/prog0 Prog0.c
cc -o $BIN_DIR/prog1 Prog1.c
cc -o $BIN_DIR/prog2 Prog2.c -pthread
cc -o $BIN_DIR/prog3 Prog3.c

#call prog0 to generate random matrices. We pass size of matrix, output file for A and output file for C.
$BIN_DIR/prog0 $MATRIX_SIZE $LOCATION_OF_A $LOCATION_OF_B

#we call prog1 to do matrix multiplication with one thread. We pass input file for A, input file for B, output file for C and size of matrix.
echo ""
echo "Starting Single threaded program. Current time:"
date "+%a %b %d %T.%3N"
$BIN_DIR/prog1 $LOCATION_OF_A $LOCATION_OF_B $LOCATION_OF_C1 $MATRIX_SIZE
echo ""
echo "Single threaded program finished. Current time:"
date "+%a %b %d %T.%3N"
echo ""

#we call prog2 to do matrix multiplication with multiple threads. We pass input file for A, input file for B, output file for C, number of threads and size of matrix.
echo "Starting multi-threaded program. Current time:"
date "+%a %b %d %T.%3N"
$BIN_DIR/prog2 $LOCATION_OF_A $LOCATION_OF_B $LOCATION_OF_C2 $NUMBER_OF_THREADS $MATRIX_SIZE
echo ""
echo "Multi threaded program finished. Current time:"
date "+%a %b %d %T.%3N"
echo ""

# we call prog3 to compare the two matrices. We pass the size of matrix, input file for C1 and input file for C2.
$BIN_DIR/prog3 $MATRIX_SIZE $LOCATION_OF_C1 $LOCATION_OF_C2
echo ""
exit

