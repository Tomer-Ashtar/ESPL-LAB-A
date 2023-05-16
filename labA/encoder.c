#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main (int argc, char** argv) {
    bool debug=false;
    bool minus=false;
    bool plus=false;
    int changeLen=0;
    int changeIndex=0;
    char* change;
    FILE * outfile=stdout;
    FILE * infile=stdin;
    char c;
    char* filename;
    for(int i=1;i<argc;i++) {
        //cheking debug mode
        if(strcmp(argv[i],"+D")==0)
            debug=true;
        else if(strcmp(argv[i],"-D")==0)
            debug=false;

        //checking addition or subtraction mode
        //intialiazing 'change' with the digits to change
        else if(argv[i][0]=='-' && argv[i][1]=='e') {
            change=argv[i]+2;
            for(int j=2; argv[i][j]!='\0';j++) {
                changeLen++;
            }
            minus=true;
             }
        else if(argv[i][0]=='+' && argv[i][1]=='e') {
            change=argv[i]+2;
            for(int j=2;argv[i][j]!='\0';j++) {
                changeLen++;
            }
            plus=true;

        }//part 3 checking -i -o cases
        else if(argv[i][0]=='-' && argv[i][1]=='i') {
            filename=argv[i]+2;
            if(!(infile= fopen(filename,"r"))){
                fprintf(stderr,"ERROR, no file %s",filename);
                return 1;}
        }
        else if(argv[i][0]=='-' && argv[i][1]=='o') {
            filename=argv[i]+2;
            outfile= fopen(filename,"w");
        }
        if (debug) {//if in debug mode
            fprintf(stderr, "%s ", argv[i]);
        }
    }
    ///////get input from user
    int temp;
    while((c= fgetc(infile))!=EOF) {
        if (minus) {////substraction case
            if (c >= 'a' && c <= 'z') {
                temp=change[changeIndex] - '0';
                if (c - temp < 'a')
                    c = 'z' + c - temp+1 - 'a';
                else
                    c = c - temp;
            } else if (c >= 'A' && c <= 'Z') {
                if (c - temp < 'A')
                    c = 'Z' + c - temp+1 - 'A';
                else
                    c = c - temp;
            } else if (c >= '0' && c <= '9') {
                if (c - temp < '0')
                    c = '9' + c - temp+1 - '0';
                else
                    c = c - temp;
            }

        }
        else if(plus){////addition case
            if (c >= 'a' && c <= 'z'){
                temp=change[changeIndex] - '0';
                if(c+temp>'z')
                    c = 'a' + c + temp-1 - 'z';
                else
                    c=c+temp;
            }

            else if (c >= 'A' && c <= 'Z' ){
                if( c + temp > 'Z')
                    c = 'A' + c + temp -1 - 'Z';
                else
                    c=c+temp;
            }

            else if (c >= '0' && c <= '9' ){
                if( c + temp > '9')
                    c = '0' + c + temp-1 - '9';
                else
                    c=c+temp;
            }

        }
        changeIndex++;
        if(changeIndex==changeLen) {
            changeIndex = 0;

        }
        fputc(c, outfile);
        }

    if(outfile!=stdout)
        fclose(outfile);
    if(infile!=stdin)
        fclose(infile);
    return 0;
}
