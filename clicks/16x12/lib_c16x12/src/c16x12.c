/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "c16x12.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t leds[ C16X12G_SW * C16X12G_CS / 8 ];

static const uint16_t demo_matrix[ 127 ][ 12 ] =
{
    {  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char
    {  0x0000, 0x0000, 0x0000, 0x0000, 0x03F4, 0x03F4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char !
    {  0x0000, 0x0000, 0x0000, 0x0700, 0x0700, 0x0000, 0x0700, 0x0700, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char "
    {  0x0000, 0x0000, 0x0000, 0x0018, 0x00DE, 0x00F8, 0x03D8, 0x00DE, 0x00F8, 0x03D8, 0x00C0, 0x0000},   // Code for char #
    {  0x0000, 0x0000, 0x0000, 0x00C8, 0x01E4, 0x013F, 0x07E4, 0x013C, 0x0098, 0x0000, 0x0000, 0x0000},   // Code for char $
    {  0x01C0, 0x03E0, 0x0220, 0x03E0, 0x01CC, 0x0030, 0x00C0, 0x0338, 0x007C, 0x0044, 0x007C, 0x0038},   // Code for char %
    {  0x0000, 0x0000, 0x01B8, 0x03FC, 0x0244, 0x03E4, 0x01B4, 0x0018, 0x006C, 0x0044, 0x0000, 0x0000},   // Code for char &
    {  0x0000, 0x0000, 0x0700, 0x0700, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char '
    {  0x0000, 0x0000, 0x00F8, 0x03FE, 0x0707, 0x0401, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char (
    {  0x0000, 0x0000, 0x0401, 0x0707, 0x03FE, 0x00F8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char )
    {  0x0000, 0x0000, 0x0280, 0x0100, 0x07C0, 0x07C0, 0x0100, 0x0280, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char *
    {  0x0000, 0x0000, 0x0000, 0x0020, 0x0020, 0x0020, 0x01FC, 0x0020, 0x0020, 0x0020, 0x0000, 0x0000},   // Code for char +
    {  0x0000, 0x0000, 0x000F, 0x000E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char ,
    {  0x0000, 0x0000, 0x0020, 0x0020, 0x0020, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char -
    {  0x0000, 0x0000, 0x000C, 0x000C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char .
    {  0x0000, 0x0000, 0x0000, 0x0003, 0x000C, 0x0070, 0x0180, 0x0600, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char /
    {  0x0000, 0x0000, 0x0000, 0x01F8, 0x03FC, 0x0204, 0x0204, 0x03FC, 0x01F8, 0x0000, 0x0000, 0x0000},   // Code for char 0
    {  0x0000, 0x0000, 0x0000, 0x0000, 0x0104, 0x03FC, 0x03FC, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char 1
    {  0x0000, 0x0000, 0x0000, 0x010C, 0x031C, 0x0234, 0x0264, 0x03C4, 0x0184, 0x0000, 0x0000, 0x0000},   // Code for char 2
    {  0x0000, 0x0000, 0x0000, 0x0108, 0x030C, 0x0244, 0x0244, 0x03FC, 0x01B8, 0x0000, 0x0000, 0x0000},   // Code for char 3
    {  0x0000, 0x0000, 0x0000, 0x0030, 0x0050, 0x0090, 0x01FC, 0x03FC, 0x0010, 0x0000, 0x0000, 0x0000},   // Code for char 4
    {  0x0000, 0x0000, 0x0000, 0x0008, 0x03CC, 0x03C4, 0x0244, 0x027C, 0x0238, 0x0000, 0x0000, 0x0000},   // Code for char 5
    {  0x0000, 0x0000, 0x0000, 0x01F8, 0x03FC, 0x0244, 0x0244, 0x027C, 0x0038, 0x0000, 0x0000, 0x0000},   // Code for char 6
    {  0x0000, 0x0000, 0x0000, 0x0200, 0x0200, 0x021C, 0x02FC, 0x03E0, 0x0300, 0x0000, 0x0000, 0x0000},   // Code for char 7
    {  0x0000, 0x0000, 0x0000, 0x01B8, 0x03FC, 0x0244, 0x0244, 0x03FC, 0x01B8, 0x0000, 0x0000, 0x0000},   // Code for char 8
    {  0x0000, 0x0000, 0x0000, 0x01C0, 0x03E4, 0x0224, 0x0224, 0x03FC, 0x01F8, 0x0000, 0x0000, 0x0000},   // Code for char 9
    {  0x0000, 0x0000, 0x0000, 0x00CC, 0x00CC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char :
    {  0x0000, 0x0000, 0x0000, 0x00CF, 0x00CE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char ;
    {  0x0000, 0x0000, 0x0000, 0x0020, 0x0050, 0x0050, 0x0088, 0x0088, 0x0104, 0x0104, 0x0000, 0x0000},   // Code for char <
    {  0x0000, 0x0000, 0x0000, 0x0090, 0x0090, 0x0090, 0x0090, 0x0090, 0x0090, 0x0090, 0x0000, 0x0000},   // Code for char =
    {  0x0000, 0x0000, 0x0000, 0x0104, 0x0104, 0x0088, 0x0088, 0x0050, 0x0050, 0x0020, 0x0000, 0x0000},   // Code for char >
    {  0x0000, 0x0000, 0x0000, 0x0100, 0x0234, 0x0274, 0x03C0, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char ?
    {  0x0000, 0x0000, 0x00F8, 0x0104, 0x0272, 0x02FA, 0x028A, 0x02F2, 0x02FA, 0x0108, 0x00F0, 0x0000},   // Code for char @
    {  0x0000, 0x0000, 0x0000, 0x001C, 0x00FC, 0x03F0, 0x0310, 0x03F0, 0x00FC, 0x001C, 0x0000, 0x0000},   // Code for char A
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0244, 0x0244, 0x03FC, 0x01B8, 0x0000, 0x0000, 0x0000},   // Code for char B
    {  0x0000, 0x0000, 0x0000, 0x01F8, 0x03FC, 0x0204, 0x0204, 0x0204, 0x0204, 0x0000, 0x0000, 0x0000},   // Code for char C
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0204, 0x0204, 0x030C, 0x01F8, 0x00F0, 0x0000, 0x0000},   // Code for char D
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0244, 0x0244, 0x0244, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char E
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0240, 0x0240, 0x0240, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char F
    {  0x0000, 0x0000, 0x0000, 0x01F8, 0x03FC, 0x0204, 0x0204, 0x0224, 0x023C, 0x023C, 0x0000, 0x0000},   // Code for char G
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0040, 0x0040, 0x0040, 0x03FC, 0x03FC, 0x0000, 0x0000},   // Code for char H
    {  0x0000, 0x0000, 0x0000, 0x0204, 0x03FC, 0x03FC, 0x0204, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char I
    {  0x0000, 0x0000, 0x0000, 0x0004, 0x0204, 0x0204, 0x03FC, 0x03F8, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char J
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x00F0, 0x0198, 0x030C, 0x0204, 0x0000, 0x0000, 0x0000},   // Code for char K
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0004, 0x0004, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char L
    {  0x0000, 0x0000, 0x03FC, 0x0380, 0x01C0, 0x00E0, 0x0060, 0x00C0, 0x0180, 0x03FC, 0x03FC, 0x0000},   // Code for char M
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x0380, 0x01C0, 0x00E0, 0x0070, 0x03FC, 0x0000, 0x0000, 0x0000},   // Code for char N
    {  0x0000, 0x0000, 0x0000, 0x01F8, 0x03FC, 0x0204, 0x0204, 0x0204, 0x03FC, 0x01F8, 0x0000, 0x0000},   // Code for char O
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0220, 0x0220, 0x03E0, 0x01C0, 0x0000, 0x0000, 0x0000},   // Code for char P
    {  0x0000, 0x0000, 0x0000, 0x01F8, 0x03FC, 0x0204, 0x0206, 0x0207, 0x03FD, 0x01F9, 0x0000, 0x0000},   // Code for char Q
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x0220, 0x0230, 0x03F8, 0x01CC, 0x0004, 0x0000, 0x0000},   // Code for char R
    {  0x0000, 0x0000, 0x0000, 0x01C4, 0x03E4, 0x0264, 0x0264, 0x027C, 0x0238, 0x0000, 0x0000, 0x0000},   // Code for char S
    {  0x0000, 0x0000, 0x0000, 0x0200, 0x0200, 0x03FC, 0x03FC, 0x0200, 0x0200, 0x0000, 0x0000, 0x0000},   // Code for char T
    {  0x0000, 0x0000, 0x0000, 0x03F8, 0x03FC, 0x0004, 0x0004, 0x0004, 0x03FC, 0x03F8, 0x0000, 0x0000},   // Code for char U
    {  0x0000, 0x0000, 0x0000, 0x0380, 0x03F0, 0x007C, 0x007C, 0x03F0, 0x0380, 0x0000, 0x0000, 0x0000},   // Code for char V
    {  0x0000, 0x0380, 0x03F0, 0x007C, 0x003C, 0x03E0, 0x03E0, 0x003C, 0x007C, 0x03F0, 0x0380, 0x0000},   // Code for char W
    {  0x0000, 0x0000, 0x0000, 0x030C, 0x039C, 0x00F0, 0x00F0, 0x039C, 0x030C, 0x0000, 0x0000, 0x0000},   // Code for char X
    {  0x0000, 0x0000, 0x0000, 0x0300, 0x03C0, 0x00FC, 0x00FC, 0x03C0, 0x0300, 0x0000, 0x0000, 0x0000},   // Code for char Y
    {  0x0000, 0x0000, 0x0000, 0x021C, 0x023C, 0x0274, 0x02E4, 0x03C4, 0x0384, 0x0000, 0x0000, 0x0000},   // Code for char Z
    {  0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x0401, 0x0401, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char [
    {  0x0000, 0x0000, 0x0000, 0x0600, 0x0180, 0x0070, 0x000C, 0x0003, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char BackSlash
    {  0x0000, 0x0000, 0x0000, 0x0401, 0x0401, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char ]
    {  0x0000, 0x0000, 0x0000, 0x0040, 0x0080, 0x0100, 0x0200, 0x0100, 0x0080, 0x0040, 0x0000, 0x0000},   // Code for char ^
    {  0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000},   // Code for char _
    {  0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0600, 0x0200, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char `
    {  0x0000, 0x0000, 0x0000, 0x0018, 0x00BC, 0x00A4, 0x00A4, 0x00FC, 0x007C, 0x0000, 0x0000, 0x0000},   // Code for char a
    {  0x0000, 0x0000, 0x0000, 0x07FC, 0x07FC, 0x0084, 0x0084, 0x00FC, 0x0078, 0x0000, 0x0000, 0x0000},   // Code for char b
    {  0x0000, 0x0000, 0x0000, 0x0078, 0x00FC, 0x0084, 0x0084, 0x0084, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char c
    {  0x0000, 0x0000, 0x0000, 0x0078, 0x00FC, 0x0084, 0x0084, 0x07FC, 0x07FC, 0x0000, 0x0000, 0x0000},   // Code for char d
    {  0x0000, 0x0000, 0x0000, 0x0078, 0x00FC, 0x00A4, 0x00A4, 0x00E4, 0x0064, 0x0000, 0x0000, 0x0000},   // Code for char e
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x07FC, 0x0480, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char f
    {  0x0000, 0x0000, 0x0000, 0x0078, 0x00FD, 0x0085, 0x0085, 0x00FF, 0x00FE, 0x0000, 0x0000, 0x0000},   // Code for char g
    {  0x0000, 0x0000, 0x0000, 0x07FC, 0x07FC, 0x0080, 0x0080, 0x00FC, 0x007C, 0x0000, 0x0000, 0x0000},   // Code for char h
    {  0x0000, 0x0000, 0x0000, 0x02FC, 0x02FC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char i
    {  0x0000, 0x0000, 0x0000, 0x0081, 0x02FF, 0x02FE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char j
    {  0x0000, 0x0000, 0x0000, 0x07FC, 0x07FC, 0x0030, 0x0078, 0x00CC, 0x0084, 0x0000, 0x0000, 0x0000},   // Code for char k
    {  0x0000, 0x0000, 0x0000, 0x07FC, 0x07FC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char l
    {  0x0000, 0x00FC, 0x00FC, 0x0080, 0x0080, 0x00FC, 0x007C, 0x0080, 0x0080, 0x00FC, 0x007C, 0x0000},   // Code for char m
    {  0x0000, 0x0000, 0x0000, 0x00FC, 0x00FC, 0x0080, 0x0080, 0x00FC, 0x007C, 0x0000, 0x0000, 0x0000},   // Code for char n
    {  0x0000, 0x0000, 0x0000, 0x0078, 0x00FC, 0x0084, 0x0084, 0x00FC, 0x0078, 0x0000, 0x0000, 0x0000},   // Code for char o
    {  0x0000, 0x0000, 0x0000, 0x00FF, 0x00FF, 0x0084, 0x0084, 0x00FC, 0x0078, 0x0000, 0x0000, 0x0000},   // Code for char p
    {  0x0000, 0x0000, 0x0000, 0x0078, 0x00FC, 0x0084, 0x0084, 0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000},   // Code for char q
    {  0x0000, 0x0000, 0x0000, 0x00FC, 0x00FC, 0x0040, 0x00C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char r
    {  0x0000, 0x0000, 0x0000, 0x0064, 0x00F4, 0x00B4, 0x00BC, 0x0098, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char s
    {  0x0000, 0x0000, 0x0000, 0x03F8, 0x03FC, 0x0084, 0x0084, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char t
    {  0x0000, 0x0000, 0x0000, 0x00F8, 0x00FC, 0x0004, 0x0004, 0x00FC, 0x00FC, 0x0000, 0x0000, 0x0000},   // Code for char u
    {  0x0000, 0x0000, 0x0000, 0x00C0, 0x00F0, 0x003C, 0x003C, 0x00F0, 0x00C0, 0x0000, 0x0000, 0x0000},   // Code for char v
    {  0x0000, 0x0000, 0x00F0, 0x00FC, 0x001C, 0x00F0, 0x00F0, 0x001C, 0x00FC, 0x00F0, 0x0000, 0x0000},   // Code for char w
    {  0x0000, 0x0000, 0x0000, 0x00CC, 0x00FC, 0x0030, 0x0030, 0x00FC, 0x00CC, 0x0000, 0x0000, 0x0000},   // Code for char x
    {  0x0000, 0x0000, 0x0000, 0x00C0, 0x00F3, 0x003F, 0x003C, 0x00F0, 0x00C0, 0x0000, 0x0000, 0x0000},   // Code for char y
    {  0x0000, 0x0000, 0x0000, 0x008C, 0x009C, 0x00B4, 0x00E4, 0x00C4, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char z
    {  0x0000, 0x0000, 0x0000, 0x0020, 0x0020, 0x03FE, 0x07DF, 0x0401, 0x0401, 0x0000, 0x0000, 0x0000},   // Code for char {
    {  0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},   // Code for char |
    {  0x0000, 0x0000, 0x0000, 0x0401, 0x0401, 0x07DF, 0x03FE, 0x0020, 0x0020, 0x0000, 0x0000, 0x0000},   // Code for char }
    {  0x0000, 0x0000, 0x0030, 0x0040, 0x0040, 0x0060, 0x0030, 0x0010, 0x0010, 0x0060, 0x0000, 0x0000},   // Code for char ~
    {  0x0000, 0x0000, 0x0000, 0x03FC, 0x03FC, 0x03FC, 0x03FC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}    // Code for char 
};

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c16x12_cfg_setup ( c16x12_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->sdb = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x50;
}

C16X12_RETVAL c16x12_init ( c16x12_t *ctx, c16x12_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C16X12_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->sdb, cfg->sdb );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return C16X12_OK;
}

void c16x12_default_cfg ( c16x12_t *ctx )
{
    // Click default configuration 

    c16x12g_write_page_byte( ctx, C16X12G_CR, C16X12G_CR_SSD );
    c16x12g_set_all_leds( ctx, C16X12G_LED_STATE_OFF );
    c16x12g_set_stand_by( ctx, 1 );
}

void c16x12_generic_write ( c16x12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void c16x12_generic_read ( c16x12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, &reg, 1 ); 
    i2c_master_read( &ctx->i2c, data_buf, len );
}

void c16x12g_write_reg ( c16x12_t *ctx, uint8_t reg, uint8_t data_ )
{
    uint8_t write_reg[ 2 ];
    
    write_reg[ 0 ] = data_;
    
    c16x12_generic_write( ctx, reg, write_reg, 1 );
}

void c16x12g_select_page ( c16x12_t *ctx, uint8_t page )
{
    c16x12g_write_reg( ctx, C16X12G_PSWL, C16X12G_PSWL_ENABLE );
    c16x12g_write_reg( ctx, C16X12G_PSR, page );
}

void c16x12g_write_page_byte ( c16x12_t *ctx, uint16_t reg_addr, uint8_t reg_value )
{
    c16x12g_select_page( ctx, reg_addr >> 8 );
    c16x12g_write_reg( ctx, reg_addr &  0x00FF, reg_value );
}

void c16x12g_write_page_data ( c16x12_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t n_data )
{
    c16x12g_write_reg( ctx, C16X12G_PSWL, C16X12G_PSWL_ENABLE );
    c16x12g_write_reg( ctx, C16X12G_PSR, reg >> 8 );

    c16x12_generic_write( ctx, reg & 0x00FF, data_buf, n_data );
}

uint8_t c16x12g_read_reg ( c16x12_t *ctx, uint8_t reg )
{
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 1 ];
    
    c16x12_generic_read( ctx, reg, write_reg, 1 );

    return read_reg[ 0 ];
}

void c16x12g_set_stand_by ( c16x12_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->sdb, state );
}

void c16x12g_device_reset ( c16x12_t *ctx )
{
    digital_out_write( &ctx->rst, 0 );
    Delay_10ms( );
    digital_out_write( &ctx->rst, 1 );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_write( &ctx->rst, 0 );
    Delay_100ms( );
}

uint8_t c16x12g_get_interrupt ( c16x12_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void c16x12g_set_all_leds( c16x12_t *ctx, uint8_t state )
{
    uint8_t offset;
    uint8_t cnt;

    for ( cnt = 0; cnt < 24; cnt++ )
    {
        leds[ cnt ] = state;
    }
    c16x12g_write_page_data( ctx, C16X12G_LEDONOFF, leds, 24 );
    c16x12g_write_page_byte( ctx, C16X12G_CR, C16X12G_CR_BEN | C16X12G_CR_SSD );
}

void c16x12g_set_global_current_control ( c16x12_t *ctx, uint8_t gcc )
{
    c16x12g_write_page_byte( ctx, C16X12G_GCC, gcc );
}

void c16x12g_clear_display( c16x12_t *ctx )
{
    c16x12g_set_all_leds( ctx, 0x00 );
}

void c16x12g_set_column_state ( c16x12_t *ctx, uint8_t col, uint16_t state, uint8_t c_end )
{
    uint8_t sw;
    uint8_t cs;
    uint8_t offset;
    uint8_t Tcol;
    uint8_t cnt;

    Tcol = (col * 2) - 2;
    leds[ Tcol + 1] |= (state >> 8);
    leds[ Tcol ] |= (state & 0x00FF);

    if ( c_end == 1 )
    {
        c16x12g_write_page_data( ctx, C16X12G_LEDONOFF, leds, 24 );
        c16x12g_write_page_byte( ctx, C16X12G_CR, C16X12G_CR_BEN | C16X12G_CR_SSD );
    }
}

void c16x12g_set_leds_mode ( c16x12_t *ctx, uint8_t mode )
{
    uint8_t cnt;
    uint8_t led_mode[ 192 ];
    
    for ( cnt = 0; cnt < 192; cnt++ )
    {
        led_mode[ cnt ] = mode;
    }
    c16x12g_write_page_data( ctx, C16X12G_LEDABM, led_mode, 192 );
}

void c16x12g_set_pmw ( c16x12_t *ctx, uint8_t pwm_value )
{
    uint8_t cnt;
    uint8_t led_pmw[ 192 ];

    for ( cnt = 0; cnt < 192; cnt++ )
    {
        led_pmw[ cnt ] = pwm_value;
    }
    c16x12g_write_page_data( ctx, C16X12G_LEDABM, led_pmw, 192 );
}

void c16x12g_set_led ( c16x12_t *ctx, uint8_t x_pos, uint8_t y_pos, uint8_t state, uint8_t c_end )
{
    uint16_t led = 0x0000;
    
    if ( state == 1 )
    {
        led = C16X12G_LED_STATE_ON << ( y_pos - 1 );
    }
    else
    {
        led = C16X12G_LED_STATE_OFF << ( y_pos - 1 );
    }
    
    c16x12g_set_column_state( ctx, x_pos, led, c_end );
}

void c16x12g_display_byte ( c16x12_t *ctx, char ch )
{
    uint8_t cnt_position;
    uint16_t demo_display;
    uint8_t demo_byte;

    demo_byte = ch - 32;

    c16x12g_clear_display( ctx );
    
    for ( cnt_position = 0; cnt_position < 12; cnt_position++ )
    {
        demo_display = demo_matrix[ demo_byte ][ cnt_position ];

        if ( cnt_position == 11 )
        {
            c16x12g_set_column_state( ctx, 12 - cnt_position , demo_display, C16X12G_STOP_SETTINGS );
        }
        else
        {
            c16x12g_set_column_state( ctx, 12 - cnt_position , demo_display, C16X12G_CONTINUE_SETTINGS );
        }
    }
}

void c16x12g_display_image ( c16x12_t *ctx, uint16_t *p_image )
{
    uint8_t cnt_position;
    uint16_t demo_display;
    
    c16x12g_clear_display( ctx );
    
    for ( cnt_position = 0; cnt_position <= 12; cnt_position++ )
    {
        demo_display = p_image[ cnt_position ];

        if ( cnt_position == 11 )
        {
            c16x12g_set_column_state( ctx, 12 - cnt_position , demo_display, C16X12G_STOP_SETTINGS );
        }
        else
        {
            c16x12g_set_column_state( ctx, 12 - cnt_position , demo_display, C16X12G_CONTINUE_SETTINGS );
        }
    }
}

void c16x12g_display_text ( c16x12_t *ctx, char *p_text, uint8_t n_char, uint8_t speed )
{
    uint16_t demo_buffer[ 1000 ];
    uint8_t demo_byte;
    uint16_t buffer_cnt = 0;
    uint8_t cnt_position;
    uint8_t cnt;
    uint16_t display_cnt = 0;
    uint16_t speed_cnt = 0;
    
    // 1-st character
    for ( cnt = 0; cnt < 12; cnt++ )
    {
        demo_buffer[ buffer_cnt++ ] = 0x0000;
    }
    
    for ( cnt = 0; cnt < n_char; cnt++ )
    {
        demo_byte = p_text[ cnt ] - 32;
        for ( cnt_position = 0; cnt_position < 12; cnt_position++ )
        {
            if ( ( demo_matrix[ demo_byte ][ cnt_position ] == 0x0000 && demo_matrix[ demo_byte ][ cnt_position + 1 ] == 0x0000 ) != 1 )
            {
                demo_buffer[ buffer_cnt++ ] = demo_matrix[ demo_byte ][ cnt_position ];
            }
        }
    }
    
    // Last character
    for ( cnt = 0; cnt < 12; cnt++ )
    {
        demo_buffer[ buffer_cnt++ ] = 0x0000;
    }
    
    for ( display_cnt = 0; display_cnt < buffer_cnt - 12 ; display_cnt++ )
    {
        c16x12g_clear_display( ctx );
        c16x12g_display_image( ctx, &demo_buffer[ display_cnt ] );
        
        // SPEED - DELAY
        for ( speed_cnt = 0; speed_cnt < speed; speed_cnt++ )
        {
            Delay_1ms( );
        }
    }
}

void c16x12g_config_abm ( c16x12_t *ctx, uint16_t n_abm, c16x12_abm_t *config )
{
    c16x12g_write_page_byte( ctx, n_abm, config->time_1 | config->time_2 );
    c16x12g_write_page_byte( ctx, n_abm + 1, config->time_3 | config->time_4 );
    c16x12g_write_page_byte( ctx, n_abm + 2,config->loop_end | config->loop_begin | ( ( config->loop_times >> 8 ) & 0x0F ) );
    c16x12g_write_page_byte( ctx, n_abm + 3, config->loop_times & 0xFF );
}

void c16x12g_start_abm ( c16x12_t *ctx )
{
    c16x12g_write_page_byte( ctx, C16X12G_CR, C16X12G_CR_SSD );
    c16x12g_write_page_byte( ctx, C16X12G_CR, C16X12G_CR_BEN | C16X12G_CR_SSD );
    c16x12g_write_page_byte( ctx, C16X12G_TUR, 0x01);
}

// ------------------------------------------------------------------------- END
