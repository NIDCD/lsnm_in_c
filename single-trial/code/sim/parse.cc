    
    #include <stdio.h>
    #include <string.h>
    
    #include "win.h"
    #include "simdefs.h"
    #include "classdef.h"
    #include "simproto.h"
    #include "externs.h"
    #include "macros.h"
    
    // #define BUGGY
    extern FILE      *buggy;
    
    // Macros for initializaion functions
    
    #define      NOT_NUM(x)      (x < '0' || x > '9')
    #define     IS_NUM(x)       (x >= '0' && x <= '9')
    #define     IS_NUMTYPE(x)   ((x >= '0' && x <= '9') || x=='+' || x=='-' || x=='.')
    #define     IS_DOT(x)       (x == '.')
    #define   NOT_CHAR(x)     (x < 'A' || x > 'z')
    #define IS_PATH(x) (x == '_' || x == '.' || x == '/' || x == '\\')
    #define IS_STRING(x) ((x >= 'A' && x <= 'z') || IS_NUM(x) || x == '#' || IS_PATH(x))
    #define IS_COMMENT(x)  (x == '%')
    #define IS_BLANK(x)     (x=='%' || x==' ' || x=='\t' || x=='\n' || x==',' || x==':' || x==';')
    #define IS_START_OBJECT(x)     (x == '(' || x == '[' || x == '{')
    #define IS_END_OBJECT(x)      (x == ')' || x == ']' || x == '}')
    
    int getcode(FILE *fd, char *codestr)
    
    {  int       inchar;
    
       inchar = getc(fd);
    
       while(inchar != EOF && IS_BLANK(inchar)) {
         if(inchar == '\n')
           n_line++;
         else if(IS_COMMENT(inchar)) {
           while(inchar != '\n' && inchar != EOF)
             inchar = getc(fd);
           if(inchar == EOF)
             return(EOF);
         }
         inchar = getc(fd);
       }
       *codestr = inchar; codestr[1] = 0;
       if(inchar == EOF)
         return(EOF);
       else if(IS_START_OBJECT(inchar))
         return(START_OBJECT);
       else if(IS_END_OBJECT(inchar))
         return(END_OBJECT);
       else if(IS_NUMTYPE(inchar))
         return(parse_number(fd, codestr));
       else if(IS_STRING(inchar))
         return(parse_string(fd, codestr));
       else
         return(getcode(fd, codestr));
    }
    
    /***********************************************************/
    //      parse_string
    /***********************************************************/
    
    int parse_string(FILE *fd, char *codestr)
    
    {
       char    *cs;
       int      length, i;
    
       cs = codestr;
    
       while(IS_STRING(*cs))
         *(++cs) = getc(fd);
       ungetc((int)(*cs), fd);
       *cs = 0;
       length = strlen(codestr);
       for (i=0; i<length; i++)
       {
           codestr[i] = tolower(codestr[i]);
       }
       return(A_STRING);
    }
         
    
    /***********************************************************/
    //      parse_number
    /***********************************************************/
    
    int parse_number(FILE *fd, char *codestr)
    {
       char  *cs;
       int      code;
    
       cs = codestr;
       cs++;
       *cs = getc(fd);
    
       while((IS_NUM(*cs) || IS_DOT(*cs)) && !IS_DOT(*cs)) {
         cs++;
         *cs = getc(fd);
       }
       if(IS_DOT(*cs)) {
         cs++;
         *cs = getc(fd);
       }
    
       while(IS_NUM(*cs)) {
         cs++;
         *cs = getc(fd);
       }
       ungetc((int)(*cs), fd);
       *cs = 0;
       return(A_NUMBER);
    }
    
    
    /***********************************************************/
    //      get string
    /***********************************************************/
    
    
    int getstring(FILE *fd, char *str)
    {
       char instring[40];
       int  code;
       int curline;
    
       curline = n_line;
       while((code = getcode(fd, instring)) != A_STRING) {
         if(code == EOF) {
           sprintf(MsgStr, "Error in line %d: string expected. Got EOF\n",
                curline);
           Errmsg(MsgStr);
           return(EOF);
         }
       }
       strcpy(str, instring);
       return(A_STRING);
    }
    
    
    /***********************************************************/
    //      get integer
    /***********************************************************/
    
    
    int getint(FILE *fd, int *num)
    {
       char instring[40];
       int  code;
       int curline;
    
       curline = n_line;
       while((code = getcode(fd, instring)) != A_NUMBER) {
         if(code == EOF) {
           sprintf(MsgStr, "Error in line %d: integer expected. Got EOF\n",
                curline);
           Errmsg(MsgStr);
           return(EOF);
         }
       }
       *num = atoi(instring);
       return(A_NUMBER);
    }
    
    
    /***********************************************************/
    //      get floating point number
    /***********************************************************/
    
    
    int getfnum(FILE *fd, float *num)
    {
       char instring[40];
       int curline, code;
    
       curline = n_line;
       while((code = getcode(fd, instring)) != A_NUMBER) {
         if(code == EOF) {
           sprintf(MsgStr, "Error in line %d: number expected. Got EOF\n",
              curline);
           Errmsg(MsgStr);
           return(EOF);
         }
       }
       *num = atof(instring);
       return(1);
    }
    
    
    /***********************************************************/
    //      find next opening brace or parenthesis
    /***********************************************************/
    
    
    int nextobject(FILE *fd)
    {
       char instring[40];
       int curline, code;
    
       curline = n_line;
       while((code = getcode(fd, instring)) != START_OBJECT) {
         if(code == EOF) {
           sprintf(MsgStr, "Error in line %d: new object expected. Got EOF\n",
                curline);
           Errmsg(MsgStr);
           return(EOF);
         }
       }
       return(1);
    }

