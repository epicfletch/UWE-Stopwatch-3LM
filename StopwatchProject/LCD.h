/*H ----------------------------------------------------------------------------
  FILENAME :  LCD.h

  DESCRIPTION :
              Header file contains number, character and symbol LCD mappings

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

// LCD memory map for numeric digits
static const uint8_t digit[10][2] =
{
    {0xFC, 0x28},  /* "0" LCD segments a+b+c+d+e+f+k+q */
    {0x60, 0x20},  /* "1" */
    {0xDB, 0x00},  /* "2" */
    {0xF3, 0x00},  /* "3" */
    {0x67, 0x00},  /* "4" */
    {0xB7, 0x00},  /* "5" */
    {0xBF, 0x00},  /* "6" */
    {0xE4, 0x00},  /* "7" */
    {0xFF, 0x00},  /* "8" */
    {0xF7, 0x00}   /* "9" */
};

// LCD memory map for uppercase letters
static const uint8_t alphabetBig[26][2] =
{
    {0xEF, 0x00},  /* "A" LCD segments a+b+c+e+f+g+m */
    {0xF1, 0x50},  /* "B" */
    {0x9C, 0x00},  /* "C" */
    {0xF0, 0x50},  /* "D" */
    {0x9F, 0x00},  /* "E" */
    {0x8F, 0x00},  /* "F" */
    {0xBD, 0x00},  /* "G" */
    {0x6F, 0x00},  /* "H" */
    {0x90, 0x50},  /* "I" */
    {0x78, 0x00},  /* "J" */
    {0x0E, 0x22},  /* "K" */
    {0x1C, 0x00},  /* "L" */
    {0x6C, 0xA0},  /* "M" */
    {0x6C, 0x82},  /* "N" */
    {0xFC, 0x00},  /* "O" */
    {0xCF, 0x00},  /* "P" */
    {0xFC, 0x02},  /* "Q" */
    {0xCF, 0x02},  /* "R" */
    {0xB7, 0x00},  /* "S" */
    {0x80, 0x50},  /* "T" */
    {0x7C, 0x00},  /* "U" */
    {0x0C, 0x28},  /* "V" */
    {0x6C, 0x0A},  /* "W" */
    {0x00, 0xAA},  /* "X" */
    {0x00, 0xB0},  /* "Y" */
    {0x90, 0x28}   /* "Z" */
};

static const uint8_t symbols[4][2] = 
{
    {0x04, 0x00},  /* ":" LCD segments Col */
    {0x02, 0x00},  /* "REC" LCD segments REC */
    {0x04, 0x00},  /* "ANT" LCD segments ANT */
    {0x01, 0x00}   /* "." LCD segments DP */ 
};

static const uint8_t dayOfWeek[7][4] =
{
    {0x6C, 0xA0, 0xFC, 0x00},  /* displays Mo for monday */
    {0x80, 0x50, 0x7C, 0x00},  /* displays Tu for tuesday */
    {0x6C, 0x0A, 0x9F, 0x00},  /* displays We for wednesday */
    {0x80, 0x50, 0x6F, 0x00},  /* displays Th for thursday */
    {0x8F, 0x00, 0xCF, 0x02},  /* displays Fr for friday */
    {0xB7, 0x00, 0xEF, 0x00},  /* displays Sa for saturday */
    {0xB7, 0x00, 0x7C, 0x00},  /* displays Su for sunday */
};

#endif
