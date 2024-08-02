/*****************************************************************************
 File Name	: displayDemoScreen.h
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

#ifndef __DISPLAYDEMOSCREEN_H
#define __DISPLAYDEMOSCREEN_H

#include "stm32f4xx_hal.h"

void testSultanAhmetCamiiImg(uint8_t color);
void testIcons(uint8_t color);
void testSmallFonts(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void testMiddleFonts(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void testMiddleFontsNoImg(uint8_t color);
void testBigFonts1(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void testBigFonts2(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void demoScreenBigSmallFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void demoScreenBigMiddleFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void demoScreenSmallFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void demoScreenMiddleFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine);
void demoScreenMiddleFontNoImg(uint8_t color);

#endif  //__DISPLAYDEMOSCREEN_H
