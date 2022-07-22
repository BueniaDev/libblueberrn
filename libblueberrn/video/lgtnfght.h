/*
    This file is part of libblueberrn.
    Copyright (C) 2022 BueniaDev.

    libblueberrn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libblueberrn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libblueberrn.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef BERRN_LIGHTNING_FIGHTERS_VIDEO
#define BERRN_LIGHTNING_FIGHTERS_VIDEO

#include <libblueberrn_api.h>
#include <utils.h>
#include <graphics.h>
#include <driver.h>
#include <video/k052109.h>
#include <video/k053245.h>
#include <video/k053251.h>
using namespace berrn;
using namespace std;

namespace berrn
{
    class lightningvideo
    {
	public:
	    lightningvideo(berrndriver &drv);
	    ~lightningvideo();

	    void init();
	    void shutdown();

	    uint16_t tileRead(bool upper, bool lower, uint32_t addr);
	    void tileWrite(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint16_t readK053244(bool upper, bool lower, uint32_t addr);
	    void writeK053244(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint16_t readK053245(bool upper, bool lower, uint32_t addr);
	    void writeK053245(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint16_t readPalette(bool upper, bool lower, uint32_t addr);
	    void writePalette(bool upper, bool lower, uint32_t addr, uint16_t data);

	    void writePriority(bool upper, bool lower, uint32_t addr, uint16_t data);

	    bool isIRQEnabled();
	    void setRMRD(bool line);

	    void updatePixels();

	private:
	    berrndriver &driver;

	    BerrnBitmapRGB *bitmap = NULL;

	    k052109video *tilemap = NULL;
	    k053245video *spritemap = NULL;
	    k053251video *priormap = NULL;

	    array<int, (512 * 256)> layer0;
	    array<int, (512 * 256)> layer1;
	    array<int, (512 * 256)> layer2;

	    array<uint8_t, 0x1000> palette_ram;

	    berrnRGBA getColor();
    };
};

#endif // BERRN_LIGHTNING_FIGHTERS_VIDEO