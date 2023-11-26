#ifndef BABEL_PARSER_CHARCODES_H_
#define BABEL_PARSER_CHARCODES_H_

namespace charcodes
{
    /**
     * Char codes constants
     * https=//github.com/xtuc/charcodes
     */
    const int backSpace = 8;
    const int tab = 9;             //  '\t'
    const int lineFeed = 10;       //  '\n'
    const int carriageReturn = 13; //  '\r'
    const int shiftOut = 14;
    const int space = 32;
    const int exclamationMark = 33;    //  '!'
    const int quotationMark = 34;      //  '"'
    const int numberSign = 35;         //  '#'
    const int dollarSign = 36;         //  '$'
    const int percentSign = 37;        //  '%'
    const int ampersand = 38;          //  '&'
    const int apostrophe = 39;         //  '''
    const int leftParenthesis = 40;    //  '('
    const int rightParenthesis = 41;   //  ')'
    const int asterisk = 42;           //  '*'
    const int plusSign = 43;           //  '+'
    const int comma = 44;              //  ','
    const int dash = 45;               //  '-'
    const int dot = 46;                //  '.'
    const int slash = 47;              //  '/'
    const int digit0 = 48;             //  '0'
    const int digit1 = 49;             //  '1'
    const int digit2 = 50;             //  '2'
    const int digit3 = 51;             //  '3'
    const int digit4 = 52;             //  '4'
    const int digit5 = 53;             //  '5'
    const int digit6 = 54;             //  '6'
    const int digit7 = 55;             //  '7'
    const int digit8 = 56;             //  '8'
    const int digit9 = 57;             //  '9'
    const int colon = 58;              //  '='
    const int semicolon = 59;          //  ';'
    const int lessThan = 60;           //  '<'
    const int equalsTo = 61;           // '='
    const int greaterThan = 62;        //  '>'
    const int questionMark = 63;       //  '?'
    const int atSign = 64;             //  '@'
    const int uppercaseA = 65;         //  'A'
    const int uppercaseB = 66;         //  'B'
    const int uppercaseC = 67;         //  'C'
    const int uppercaseD = 68;         //  'D'
    const int uppercaseE = 69;         //  'E'
    const int uppercaseF = 70;         //  'F'
    const int uppercaseG = 71;         //  'G'
    const int uppercaseH = 72;         //  'H'
    const int uppercaseI = 73;         //  'I'
    const int uppercaseJ = 74;         //  'J'
    const int uppercaseK = 75;         //  'K'
    const int uppercaseL = 76;         //  'L'
    const int uppercaseM = 77;         //  'M'
    const int uppercaseN = 78;         //  'N'
    const int uppercaseO = 79;         //  'O'
    const int uppercaseP = 80;         //  'P'
    const int uppercaseQ = 81;         //  'Q'
    const int uppercaseR = 82;         //  'R'
    const int uppercaseS = 83;         //  'S'
    const int uppercaseT = 84;         //  'T'
    const int uppercaseU = 85;         //  'U'
    const int uppercaseV = 86;         //  'V'
    const int uppercaseW = 87;         //  'W'
    const int uppercaseX = 88;         //  'X'
    const int uppercaseY = 89;         //  'Y'
    const int uppercaseZ = 90;         //  'Z'
    const int leftSquareBracket = 91;  //  '['
    const int backslash = 92;          //  '\    '
    const int rightSquareBracket = 93; //  ']'
    const int caret = 94;              //  '^'
    const int underscore = 95;         //  '_'
    const int graveAccent = 96;        //  '`'
    const int lowercaseA = 97;         //  'a'
    const int lowercaseB = 98;         //  'b'
    const int lowercaseC = 99;         //  'c'
    const int lowercaseD = 100;        //  'd'
    const int lowercaseE = 101;        //  'e'
    const int lowercaseF = 102;        //  'f'
    const int lowercaseG = 103;        //  'g'
    const int lowercaseH = 104;        //  'h'
    const int lowercaseI = 105;        //  'i'
    const int lowercaseJ = 106;        //  'j'
    const int lowercaseK = 107;        //  'k'
    const int lowercaseL = 108;        //  'l'
    const int lowercaseM = 109;        //  'm'
    const int lowercaseN = 110;        //  'n'
    const int lowercaseO = 111;        //  'o'
    const int lowercaseP = 112;        //  'p'
    const int lowercaseQ = 113;        //  'q'
    const int lowercaseR = 114;        //  'r'
    const int lowercaseS = 115;        //  's'
    const int lowercaseT = 116;        //  't'
    const int lowercaseU = 117;        //  'u'
    const int lowercaseV = 118;        //  'v'
    const int lowercaseW = 119;        //  'w'
    const int lowercaseX = 120;        //  'x'
    const int lowercaseY = 121;        //  'y'
    const int lowercaseZ = 122;        //  'z'
    const int leftCurlyBrace = 123;    //  '{'
    const int verticalBar = 124;       //  '|'
    const int rightCurlyBrace = 125;   //  '}'
    const int tilde = 126;             //  '~'
    const int nonBreakingSpace = 160;
    const int oghamSpaceMark = 5760;
    const int lineSeparator = 8232;
    const int paragraphSeparator = 8233;

    bool isDigit(int code)
    {
        return code >= 48 && code <= 57;
    };
}

#endif // BABEL_PARSER_CHARCODES_H_
