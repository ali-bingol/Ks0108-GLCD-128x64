/*****************************************************************************
 File Name	: KS0108.h
 Author		: Ali Bingöl - Copyright (C) 2024
 Date		: 24/07/2024
 Revised	: 24/07/2024
 Version	: 1.000
 Target MCU	: STM32

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
   BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
   OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
   WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
   ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
   SOFTWARE.
   
 This code is distributed under the GNU Public License
		which can be found at http://www.gnu.org/licenses/gpl.txt

*****************************************************************************/

#ifndef __KS0108_H
#define __KS0108_H

#include "stm32f4xx_hal.h"

#define KS0108_SCREEN_WIDTH		128
#define KS0108_SCREEN_HEIGHT	64

#define DISPLAY_SET_Y			0x40
#define DISPLAY_SET_X			0xB8
#define DISPLAY_START_LINE		0xC0
#define DISPLAY_ON_CMD			0x3E
#define ON						0x01
#define OFF						0x00

void GLCD_Start(void);
void GLCD_WriteData(unsigned char);  
void GLCD_WriteCommand(unsigned char, unsigned char);
void GLCD_FillOrCleanAllScreen(uint8_t val);
void GLCD_GoTo(unsigned char, unsigned char);
void GLCD_DrawImg(const unsigned char *data, uint16_t length, uint8_t startX, uint8_t startY, uint8_t width, uint8_t height, uint8_t color);
void GLCDInit(void);void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color);
void GLCD_FlushBuffer(void);
void GLCD_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color);
void GLCD_DrawRectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color);void GLCD_Circle(unsigned char cx, unsigned char cy ,unsigned char radius);
void GLCD_DrawCircle(int x0, int y0, int radius, unsigned char color);
void GLCD_DrawChar(unsigned char x, unsigned char y, char c, unsigned char color);
void GLCD_DrawString(unsigned char x, unsigned char y, char *str, unsigned char color);
void GLCD_DrawTextInRectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, char *str, unsigned char color);

unsigned char GLCD_DrawCharImg(const unsigned char *font, unsigned char x, unsigned char y, char c, unsigned char color, unsigned char extraSpace);
void GLCD_DrawStringImg(const unsigned char *font, unsigned char x, unsigned char y, const char *str, unsigned char color, unsigned char extraSpace, unsigned char drawLineToTop);
	
#endif /* __KS0108_H */


