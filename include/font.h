#pragma once

#include <Arduino.h>

const PROGMEM uint8_t fontHeight[2] = {7, 5};
const PROGMEM uint8_t fontWidth[2] = {5, 3};

const PROGMEM uint8_t font_7x5[256][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  0
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  1
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  2
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  3
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  4
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  5
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  6
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  7
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  8
    {0x00, 0x00, 0x00, 0x00, 0x00}, //  9
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 10
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 11
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 12
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 13
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 14
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 15
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 16
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 17
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 18
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 19
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 20
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 21
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 22
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 23
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 24
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 25
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 26
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 27
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 28
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 29
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 30
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 31
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 32
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // 33 !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // 34 "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // 35 #
    {0x24, 0x2A, 0x6B, 0x2A, 0x12}, // 36 $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // 37 %
    {0x36, 0x49, 0x59, 0x26, 0x50}, // 38 &
    {0x00, 0x00, 0x04, 0x03, 0x00}, // 39 '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // 40 (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // 41 )
    {0x24, 0x18, 0x7E, 0x18, 0x24}, // 42 *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // 43 +
    {0x00, 0x00, 0x58, 0x38, 0x00}, // 44 ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // 45 -
    {0x00, 0x00, 0x60, 0x60, 0x00}, // 46 .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // 47 /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 48 0
    {0x00, 0x04, 0x42, 0x7F, 0x40}, // 49 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 50 2
    {0x22, 0x41, 0x49, 0x49, 0x36}, // 51 3
    {0x18, 0x14, 0x52, 0x7F, 0x50}, // 52 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 53 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 54 6
    {0x61, 0x11, 0x09, 0x05, 0x03}, // 55 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 56 8
    {0x06, 0x49, 0x49, 0x49, 0x3E}, // 57 9
    {0x00, 0x00, 0x36, 0x36, 0x00}, // 58 :
    {0x00, 0x00, 0x56, 0x36, 0x00}, // 59 ;
    {0x00, 0x08, 0x14, 0x22, 0x41}, // 60 <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // 61 =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // 62 >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // 63 ?
    {0x3E, 0x41, 0x5D, 0x55, 0x1E}, // 64 @
    {0x7C, 0x12, 0x11, 0x12, 0x7C}, // 65 A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // 66 B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // 67 C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // 68 D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // 69 E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // 70 F
    {0x3E, 0x41, 0x49, 0x49, 0x3A}, // 71 G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 72 H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // 73 I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // 74 J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // 75 K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // 76 L
    {0x7F, 0x02, 0x04, 0x02, 0x7F}, // 77 M
    {0x7F, 0x02, 0x0C, 0x10, 0x7F}, // 78 N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 79 O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // 80 P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // 81 Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // 82 R
    {0x26, 0x49, 0x49, 0x49, 0x32}, // 83 S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // 84 T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // 85 U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // 86 V
    {0x3F, 0x40, 0x30, 0x40, 0x3F}, // 87 W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // 88 X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // 89 Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // 90 Z
    {0x00, 0x7F, 0x41, 0x41, 0x00}, // 91 [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // 92 BACKSLASH
    {0x00, 0x41, 0x41, 0x7F, 0x00}, // 93 ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // 94 ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // 95 _
    {0x00, 0x00, 0x03, 0x04, 0x00}, // 96 `
    {0x20, 0x54, 0x54, 0x54, 0x78}, // 97 a
    {0x7F, 0x44, 0x44, 0x44, 0x38}, // 98 b
    {0x38, 0x44, 0x44, 0x44, 0x44}, // 99 c
    {0x38, 0x44, 0x44, 0x44, 0x7F}, // 100 d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // 101 e
    {0x44, 0x7E, 0x45, 0x01, 0x02}, // 102 f
    {0x08, 0x54, 0x54, 0x54, 0x3C}, // 103 g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // 104 h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // 105 i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // 106 j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // 107 k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // 108 l
    {0x7C, 0x04, 0x7C, 0x04, 0x78}, // 109 m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // 110 n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // 111 o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // 112 p
    {0x08, 0x14, 0x14, 0x14, 0x7C}, // 113 q
    {0x00, 0x7C, 0x08, 0x04, 0x04}, // 114 r
    {0x48, 0x54, 0x54, 0x54, 0x24}, // 115 s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // 116 t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // 117 u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // 118 v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // 119 w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // 120 x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // 121 y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // 122 z
    {0x08, 0x08, 0x36, 0x41, 0x41}, // 123 {
    {0x00, 0x00, 0x77, 0x00, 0x00}, // 124 |
    {0x41, 0x41, 0x36, 0x08, 0x08}, // 125 }
    {0x08, 0x04, 0x04, 0x08, 0x08}, // 126 ~
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 127
    {0x1E, 0xA1, 0xE1, 0x21, 0x12}, /* 128 € */
    {0x3C, 0x41, 0x40, 0x21, 0x7C}, /* 129  */
    {0x38, 0x54, 0x56, 0x55, 0x18}, /* 130 ‚ */
    {0x20, 0x56, 0x55, 0x56, 0x78}, /* 131 ƒ */
    {0x20, 0x55, 0x54, 0x55, 0x78}, /* 132 „ */
    {0x20, 0x54, 0x55, 0x56, 0x78}, /* 133 … */
    {0x20, 0x54, 0x57, 0x57, 0x78}, /* 134 † */
    {0x1C, 0xA2, 0xE2, 0x22, 0x14}, /* 135 ‡ */
    {0x38, 0x56, 0x55, 0x56, 0x18}, /* 136 ˆ */
    {0x38, 0x55, 0x54, 0x55, 0x18}, /* 137 ‰ */
    {0x38, 0x54, 0x55, 0x56, 0x18}, /* 138 Š */
    {0x00, 0x45, 0x7C, 0x41, 0x00}, /* 139 ‹ */
    {0x00, 0x46, 0x7D, 0x42, 0x00}, /* 140 Œ */
    {0x00, 0x44, 0x7D, 0x42, 0x00}, /* 141  */
    {0x79, 0x14, 0x12, 0x14, 0x79}, /* 142 Ž */
    {0x78, 0x14, 0x17, 0x17, 0x78}, /* 143  */
    {0x7C, 0x54, 0x55, 0x56, 0x44}, /* 144  */
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 145
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 146
    {0x30, 0x4A, 0x49, 0x4A, 0x30}, /* 147 “ */
    {0x38, 0x45, 0x44, 0x45, 0x38}, /* 148 ” */
    {0x38, 0x45, 0x46, 0x44, 0x38}, /* 149 • */
    {0x38, 0x42, 0x41, 0x22, 0x78}, /* 150 – */
    {0x3C, 0x41, 0x42, 0x20, 0x7C}, /* 151 — */
    {0x0C, 0x51, 0x50, 0x51, 0x3C}, /* 152 ˜ */
    {0x3D, 0x42, 0x42, 0x42, 0x3D}, /* 153 ™ */
    {0x3C, 0x41, 0x40, 0x21, 0x7C}, /* 154 š */
    {0x1C, 0x22, 0x63, 0x22, 0x22}, /* 155 › */
    {0x68, 0x7E, 0x49, 0x42, 0x20}, /* 156 œ */
    {0x00, 0x00, 0x00, 0x00, 0x00}, /* 157  */
    {0x00, 0x00, 0x00, 0x00, 0x00}, /* 158 ž */
    {0x20, 0x48, 0x3e, 0x09, 0x02}, /* 159 Ÿ */
    {0x20, 0x54, 0x56, 0x55, 0x78}, /* 160   */
    {0x00, 0x46, 0x7D, 0x40, 0x00}, /* 161   */
    {0x38, 0x44, 0x46, 0x45, 0x38}, /* 162 ¢ */
    {0x3C, 0x40, 0x42, 0x21, 0x7C}, /* 163 £ */
    {0x78, 0x12, 0x09, 0x0A, 0x71}, /* 164 ¤ */
    {0x7C, 0x0A, 0x11, 0x22, 0x7D}, /* 165 ¥ */
    {0x00, 0x06, 0x09, 0x0F, 0x08}, /* 166 ¦ */
    {0x00, 0x06, 0x09, 0x09, 0x06}, /* 167 § */
    {0x20, 0x40, 0x45, 0x48, 0x30}, /* 168 ¨ */
    {0x00, 0x00, 0xF8, 0xF8, 0x18}, /* 169 © */
    {0x18, 0x18, 0xF8, 0xF8, 0x00}, /* 170 ª */
    {0x17, 0x08, 0x04, 0x76, 0x5D}, /* 171 « */
    {0x17, 0x08, 0x1C, 0x76, 0x11}, /* 172 ¬ */
    {0x00, 0x00, 0x7D, 0x00, 0x00}, /* 173 ­ */
    {0x08, 0x14, 0x2A, 0x14, 0x22}, /* 174 ® */
    {0x22, 0x14, 0x2A, 0x14, 0x08}, /* 175 ¯ */
    {0x44, 0x11, 0x44, 0x11, 0x44}, /* 176 ° */
    {0x55, 0xAA, 0x55, 0xAA, 0x55}, /* 177 ± */
    {0x55, 0xFF, 0x55, 0xFF, 0x55}, /* 178 ² */
    {0x00, 0x00, 0xFF, 0xFF, 0x00}, /* 179 ³ */
    {0x18, 0x18, 0xFF, 0xFF, 0x00}, /* 180 ´ */
    {0x24, 0x24, 0xFF, 0xFF, 0x00}, /* 181 µ */
    {0x18, 0xFF, 0x00, 0x00, 0xFF}, /* 182 ¶ */
    {0x18, 0xF8, 0x08, 0x08, 0xF8}, /* 183 · */
    {0x24, 0x24, 0xFF, 0xFF, 0x00}, /* 184 ¸ */
    {0x24, 0xE7, 0x00, 0x00, 0xE7}, /* 185 ¹ */
    {0x00, 0xFF, 0x00, 0x00, 0xFF}, /* 186 º */
    {0x24, 0xE4, 0x04, 0x04, 0xFC}, /* 187 » */
    {0x24, 0x27, 0x20, 0x20, 0x3F}, /* 188 ¼ */
    {0x18, 0x1F, 0x18, 0x18, 0x1F}, /* 189 ½ */
    {0x24, 0x24, 0x3F, 0x3F, 0x00}, /* 190 ¾ */
    {0x18, 0x18, 0xF8, 0xF8, 0x00}, /* 191 ¿ */
    {0x00, 0x00, 0x1F, 0x1F, 0x18}, /* 192 À */
    {0x18, 0x18, 0x1F, 0x1F, 0x18}, /* 193 Á */
    {0x18, 0x18, 0xF8, 0xF8, 0x18}, /* 194 Â */
    {0x00, 0x00, 0xFF, 0xFF, 0x18}, /* 195 Ã */
    {0x18, 0x18, 0x18, 0x18, 0x18}, /* 196 Ä */
    {0x18, 0x18, 0xFF, 0xFF, 0x18}, /* 197 Å */
    {0x00, 0x00, 0xFF, 0xFF, 0x24}, /* 198 Æ */
    {0x00, 0xFF, 0x00, 0x00, 0xFF}, /* 199 Ç */
    {0x00, 0x3F, 0x20, 0x20, 0x27}, /* 200 È */
    {0x00, 0xFC, 0x04, 0x04, 0xE4}, /* 201 É */
    {0x24, 0x27, 0x20, 0x20, 0x27}, /* 202 Ê */
    {0x24, 0xE4, 0x04, 0x04, 0xE4}, /* 203 Ë */
    {0x00, 0xFF, 0x00, 0x00, 0xE7}, /* 204 Ì */
    {0x24, 0x24, 0x24, 0x24, 0x24}, /* 205 Í */
    {0x24, 0xE7, 0x00, 0x00, 0xE7}, /* 206 Î */
    {0x24, 0x24, 0x27, 0x27, 0x24}, /* 207 Ï */
    {0x18, 0x1F, 0x18, 0x18, 0x1F}, /* 208 Ð */
    {0x24, 0x24, 0xE4, 0xE4, 0x24}, /* 209 Ñ */
    {0x18, 0xF8, 0x18, 0x18, 0xF8}, /* 210 Ò */
    {0x00, 0x1F, 0x18, 0x18, 0x1F}, /* 211 Ó */
    {0x00, 0x00, 0x3F, 0x3F, 0x24}, /* 212 Ô */
    {0x00, 0x00, 0xFC, 0xFC, 0x24}, /* 213 Õ */
    {0x00, 0xF8, 0x18, 0x18, 0xF8}, /* 214 Ö */
    {0x18, 0xFF, 0x18, 0x18, 0xFF}, /* 215 × */
    {0x24, 0x24, 0xFF, 0xFF, 0x24}, /* 216 Ø */
    {0x18, 0x18, 0x1F, 0x1F, 0x00}, /* 217 Ù */
    {0x00, 0x00, 0xF8, 0xF8, 0x18}, /* 218 Ú */
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, /* 219 Û */
    {0xF0, 0xF0, 0xF0, 0xF0, 0xF0}, /* 220 Ü */
    {0xFF, 0xFF, 0xFF, 0x00, 0x00}, /* 221 Ý */
    {0x00, 0x00, 0x00, 0xFF, 0xFF}, /* 222 Þ */
    {0x0F, 0x0F, 0x0F, 0x0F, 0x0F}, /* 223 ß */
    {0x38, 0x44, 0x44, 0x38, 0x44}, /* 224 à */
    {0x7e, 0x01, 0x09, 0x49, 0x36}, /* 225 á */
    {0x01, 0x7F, 0x01, 0x01, 0x03}, /* 226 â */
    {0x04, 0x7C, 0x04, 0x7C, 0x04}, /* 227 ã */
    {0x43, 0x65, 0x59, 0x41, 0x63}, /* 228 ä */
    {0x3C, 0x42, 0x42, 0x26, 0x1A}, /* 229 å */
    {0x40, 0x3E, 0x08, 0x08, 0x06}, /* 230 æ */
    {0x04, 0x06, 0x7F, 0x06, 0x04}, /* 231 Pfeil oben */
    {0x10, 0x30, 0x5F, 0x30, 0x10}, /* 232 Pfeil unten */
    {0x1C, 0x6B, 0x49, 0x6B, 0x1C}, /* 233 é */
    {0x5C, 0x62, 0x02, 0x62, 0x5C}, /* 234 ê */
    {0x00, 0x30, 0x4E, 0x49, 0x32}, /* 235 ë */
    {0x18, 0x24, 0x18, 0x24, 0x18}, /* 236 ì */
    {0x2C, 0x12, 0x2A, 0x24, 0x1A}, /* 237 í */
    {0x14, 0x2A, 0x49, 0x49, 0x41}, /* 238 î */
    {0x7E, 0x01, 0x01, 0x01, 0x7E}, /* 239 ï */
    {0x2A, 0x2A, 0x2A, 0x2A, 0x2A}, /* 240 ð */
    {0x00, 0x24, 0x2E, 0x24, 0x00}, /* 241 ñ */
    {0x40, 0x51, 0x4A, 0x44, 0x40}, /* 242 ò */
    {0x40, 0x44, 0x4A, 0x51, 0x40}, /* 243 ó */
    {0x00, 0x00, 0xFE, 0x01, 0x02}, /* 244 ô */
    {0x40, 0x80, 0x7F, 0x00, 0x00}, /* 245 õ */
    {0x08, 0x08, 0x2A, 0x08, 0x08}, /* 246 ö */
    {0x24, 0x12, 0x24, 0x12, 0x00}, /* 247 ÷ */
    {0x00, 0x07, 0x05, 0x07, 0x00}, /* 248 ø */
    {0x00, 0x18, 0x18, 0x00, 0x00}, /* 249 ù */
    {0x00, 0x10, 0x10, 0x10, 0x00}, /* 250 ú */
    {0x10, 0x30, 0x40, 0x38, 0x07}, /* 251 û */
    {0x15, 0x15, 0x1F, 0x00, 0x00}, /* 252 3 hoch */
    {0x1D, 0x15, 0x17, 0x00, 0x00}, /* 253 ý */
    {0x74, 0x54, 0x5C, 0x00, 0x00}, /* 254 2 tief */
    {0x1C, 0x10, 0x78, 0x00, 0x00}  /* 255 4 tief */
};

const PROGMEM uint8_t font_5x3[10][3] = {
    {0x1F, 0x11, 0x1F}, // 0
    {0x00, 0x1F, 0x00}, // 1
    {0x1D, 0x15, 0x17}, // 2
    {0x15, 0x15, 0x1F}, // 3
    {0x07, 0x04, 0x1F}, // 4
    {0x17, 0x15, 0x1D}, // 5
    {0x1F, 0x15, 0x1D}, // 6
    {0x01, 0x01, 0x1F}, // 7
    {0x1F, 0x15, 0x1F}, // 8
    {0x17, 0x15, 0x1F}, // 9
};

const PROGMEM uint8_t font_char[2][3] = {
    {0x11, 0x1F, 0x11}, // I
    {0x1F, 0x14, 0x1C}, // P
};