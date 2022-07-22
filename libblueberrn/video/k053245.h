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

#ifndef BERRN_K053245_VIDEO_H
#define BERRN_K053245_VIDEO_H

#include <libblueberrn_api.h>
#include <utils.h>
#include <graphics.h>
#include <driver.h>
using namespace berrn;
using namespace std;

namespace berrn
{
    using objbuffer = array<int, (512 * 256)>;
    class k053245video
    {
	public:
	    k053245video(berrndriver &drv);
	    ~k053245video();

	    void init();
	    void setROM(vector<uint8_t> &rom);
	    void shutdown();

	    uint16_t k053245_read16_scattered(bool upper, bool lower, uint32_t addr);
	    void k053245_write16_scattered(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint16_t k053245_read16(bool upper, bool lower, uint32_t addr);
	    void k053245_write16(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint8_t k053245_read(uint16_t addr);
	    void k053245_write(uint16_t addr, uint8_t data);

	    uint16_t k053244_read16(bool upper, bool lower, uint32_t addr);
	    void k053244_write16(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint8_t k053244_read(uint16_t addr);
	    void k053244_write(uint16_t addr, uint8_t data);

	    void render();

	private:
	    berrndriver &driver;

	    vector<uint8_t> obj_rom;
	    vector<uint8_t> obj_tiles;

	    array<uint8_t, 0x4000> obj_ram_scattered;

	    array<uint8_t, 0x800> obj_ram;

	    uint32_t num_tiles = 0;
    };
};

#endif // BERRN_K053245_VIDEO_H