# ESPL-LAB-A
 The actual assignment

In this simple assignment you will be writing a simple encoder program. The program has three functionalities:

    Parsing the command-line arguments and printing debug messages.
    The actual encoder.
    Redirecting the input and output according to the command-line arguments. 

Although you will be submitting a single program containing all the above, it is highly recommended that you implement each step in the above order and test it thoroughly before proceeding to the next one. There are several reasons for this. First, the step-by-step scheme is how physical labs will be run. But more in general, it is important to be able to partition the work and test functionalities separately, this leads to much more efficient and correct code development.
Part 1: Command-Line Arguments and Debugging
First, re-read and understand the arguments of main(argc, argv), which represent the command-line arguments in the line used to run any program using a "console". Recall that argv is the number of arguments, and that argv is an array of pointers to locations containing "null terminated strings" - the command line arguments, with argv[0] pointing to the program file name used in the command line to run the program.

Second, introduce a debug mode into your program. For this we will develop an easy debugging scheme which can be used with any program and allows for special debugging features for testing. The minimum implementation prints out important information to stderr when in debug mode. Printing out the command-line parameters allows for easy detection of errors in retrieving them. Henceforth, code you write in most labs and assignments will also require adding a debug mode, and it is a good idea to have this option in all programs you write, even if not required to do so!

For this scheme, you must simply loop over the command-line arguments, and if in debug mode, print each argument on a separate "line" to stderr. Debug mode is a variable that you can choose to initialize to "on" or "off" (default: off), but if there is a command line argument "+D" it turns debug mode on, and if there is a command-line argument "-D" it turns the debug mode off. Use fprintf( ) -- see manual -- for simple printing of "strings" on separate lines. Note, that the output should be to stderr, rather than stdout, to differentiate between regular program output (currently null) and debug/error messages from the program.
Part 2: The Encoder
In this part you will first use the command-line parsing to detect a possible encoding string, and use that to modify the output behavior. With no encoding string, every input character (from stdin) is simply sent to the output (stdout). That is, you read a character using fgetc( ), possibly encode it, and then print it after modification using fputc( ), until detecting an EOF condition in the input, at which point you should close the output stream and exit "normally". We recommend here that you use variables such as infile and outfile as arguments to fgetc() and fputc() respectively, initialized by default to stdin and stdout, respectively. This will allow you to do the last part with very little effort.

The encoding works as follows. The encryption key is of the following structure: +e{key}. The argument {key} stands for a sequence of digits whose value will be added to each input characters in sequence, in a cyclic manner.
This means that each digit in sequence received by the encoder is added to the corresponding character in sequence in the key. When and if the end of the key is reached, re-start reading encoding digits from the beginning of the key. You should support both addition and subtraction, +e{key} is for addition and -e{key} is for subtraction.

Implementation is as follows. The key value, if any, is provided as a command-line argument. As stated above, this is indicated by a command line argument such as "+e1234" or "-e13061". The first is a sequence of numbers to be added to the input characters before they are emitted, while the second is a sequence of numbers to be subtracted from the input characters. Assumptions are: only at most one of "+e" or "-e" are present, and the rest of the command line argument is always (only) a non-empty sequence of decimal digits, terminated as usual by a null character.

Encoding is as follows: to the first character of the input, add the numerical value of the first encoding digit, to the second input character add the (numerical value of the) second digit, etc. If you reach the end of the encoding string (null character!) before you reach EOF in the input, reset to the beginning of the encoding string. Observe that this is ASCII encoding, so it should be very simple to compute the numeric value of each digit, which you should do directly using no special functions. Note that we advance in the encoding key once for each input character, but encoding, if indicated, should only be applied to alpha-numeric characters, that is 0-9, A-Z, and a-z, and should use "wrap around", that is assume z+1 is a, and A-1 is Z. etc. Examples are provided below to fully clarify this.
Examples
In the first example below see how the A,B,C,D,E are encoded adding 1,2,3,4,5 respectively and then for the next character the encoding key is reset to 1 for the next character, Z. But Z+1 is wrapped around and becomes A. Then there is a newline character, which is output with no change (still advancing the encoding key) so to the next character 3 is added, and to the one after that 4 is added. The last 2 characters again are output with no change. The 2nd example below is similar but now with a key to subtract, rather than add.

#> encoder +e12345
ABCDEZ
BDFHJA
12#<
46#<
^D
#> encoder -e4321
GDUQP523
CASPL202
^D

Part 3: Input and/or Output to Specific Files

The default operation of your program is to read characters from stdin (the "console" keyboard), encode them as needed, and output the results to stdout (the "console" display). After checking correctness of all the previous parts, now add the option for reading the input from a specified input file: if command-line argument "-ifname" is present, the input should be read from a file called "fname" instead of stdin (or in general the file name starts immediately after the "-i" and ends at the null character). Likewise, if command-line argument "-ofname" is present, the output should go to a file name "fname" (or in general, file name immediately after the "o").

Observe that if you did things right and heeded our advice above, this part is only a few lines of code: while scanning the command-line arguments simply check for "-i" and "-o" and open input and/or output files as needed using fopen( ), and use the file descriptor it returns for the value of "infile" and/or "outfile". The rest of the program does not need to change at all. Just make sure that if fopen( ) fails, print an error message to stderr and exit. Note that your program should support encoding keys, input file setting, output file setting, and debug flag setting, in any combination or order. You may assume that at most one of each will be given (e.g. no more than one encoding key, and no more than one output file setting).
Helpful Information and Hints

    stdin and stdout are FILE* constants than can be used with fgetc and fputc.
    Make sure you know how to recognize end of file ( EOF ).
    Control-D causes the Unix terminal driver to signal the EOF condition to the process running in this terminal foreground, using this key combination (shown in the above example as ^D) will cause fgetc() to return an EOF constant and in response your program should terminate itself "normally".
    Refer to ASCII table for more information on how to convert characters to lower-case or upper-case.
    In every do-at-home lab, we designate some issues as "may obtain help". By this we mean there will be an optional task in a concurrent physical-attendance lab (in this case lab 1), where you may obtain help from a TA and make sure you are doing things correctly. This does not mean that you can expect the lab TA to do your work for you, only help to clarify misconceptions and difficulties. In this assignment the following issues are so designated:
        Correctly detecting the end-of-file condition in the input file
        Correct use of makefiles 

Mandatory requirements

    You must read and process the input character by character, there is no need to store the characters you read at all, except for the character currently being processed.
    Important - you cannot make any assumption about the line lengths.
    Check whether a character is an lowercase (letter resp. uppercase, or number) by using a single "if" statement with two conditions. How?
    You are not allowed to use any library function for the purpose of recognizing whether a character is a letter, and its case.
    Read your program parameters in the same way as in Part 0's: main.c. First, set default values to the variables holding the program configuration and then scan through argv to update those values. Points will be reduced for failing to do so.
    Program arguments may arrive in an arbitrary order. Your program must support this feature.
    Output to stdout (or ofname) must contain only the (possibly encoded) characters from the input, this will undergo automated checking so any deviation will cause failing automated tests and a grade reduction. For the debug printouts (in stderr) we will not enforce a specific format. 

Submission
In the following submission instructions and deliverables as well as point distribution.
Submission instructions

    Create a zip file with the relevant files (only).
    Upload zip file to the submission system.
    Download the zip file from the submission system and extract its content to an empty folder.
    Compile and test the code to make sure that it still works.
    In this case the makefile should be set so that "make encoder" generates an executable file of your program with the name "encoder" in its current directory, and with no additional directory structure. 

Deliverables

All required subtask solutions are to be submitted within a single C file (encoder.c) inclusive makefile. I.e., a zip folder containing exactly the following files:

    makefile
    encoder.c 

Credit Points per Part
Part	Points
1 	20
2 	40
3 	40
