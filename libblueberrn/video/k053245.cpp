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

#include "k053245.h"
using namespace berrn;
using namespace std;

namespace berrn
{
    // K053244/K053245 high-level implementation (WIP)
    // TODO list:
    // Implement sprite rendering
    // Implement K053244 register reads/writes

    k053245video::k053245video(berrndriver &drv) : driver(drv)
    {

    }

    k053245video::~k053245video()
    {

    }

    void k053245video::init()
    {
	obj_ram_scattered.fill(0);
	obj_ram.fill(0);
    }

    void k053245video::setROM(vector<uint8_t> &rom)
    {
	obj_rom = vector<uint8_t>(rom.begin(), rom.end());
    }

    void k053245video::shutdown()
    {
	obj_rom.clear();
    }

    uint16_t k053245video::k053245_read16_scattered(bool upper, bool lower, uint32_t addr)
    {
	uint16_t data = 0;
	addr &= 0x3FFF;
	if ((addr & 0x62) != 0)
	{
	    if (upper)
	    {
		data |= (obj_ram_scattered.at(addr) << 8);
	    }

	    if (lower)
	    {
		data |= obj_ram_scattered.at(addr + 1);
	    }
	}
	else
	{
	    uint32_t offs = (addr >> 1);
	    offs = ((offs & 0xE) >> 1) | ((offs & 0x1FC0) >> 3);
	    data = k053245_read16(upper, lower, (offs << 1));
	}

	return data;
    }

    void k053245video::k053245_write16_scattered(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	addr &= 0x3FFF;
	if (upper)
	{
	    obj_ram_scattered.at(addr) = (data >> 8);
	}

	if (lower)
	{
	    obj_ram_scattered.at(addr + 1) = (data & 0xFF);
	}

	if ((addr & 0x62) == 0)
	{
	    uint32_t offs = (addr >> 1);
	    offs = ((offs & 0xE) >> 1) | ((offs & 0x1FC0) >> 3);
	    k053245_write16(upper, lower, (offs << 1), data);
	}
    }

    uint16_t k053245video::k053245_read16(bool upper, bool lower, uint32_t addr)
    {
	addr &= 0x7FF;
	uint16_t data = 0;

	if (upper)
	{
	    data |= (k053245_read(addr) << 8);
	}

	if (lower)
	{
	    data |= k053245_read(addr + 1);
	}

	return data;
    }

    void k053245video::k053245_write16(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	if (upper)
	{
	    k053245_write(addr, (data >> 8));
	}

	if (lower)
	{
	    k053245_write((addr + 1), (data & 0xFF));
	}
    }

    uint8_t k053245video::k053245_read(uint16_t addr)
    {
	addr &= 0x7FF;
	return obj_ram.at(addr);
    }

    void k053245video::k053245_write(uint16_t addr, uint8_t data)
    {
	addr &= 0x7FF;
	obj_ram.at(addr) = data;
    }

    uint16_t k053245video::k053244_read16(bool upper, bool lower, uint32_t addr)
    {
	addr = ((addr >> 1) & 0xF);
	addr &= ~1;
	uint16_t data = 0;

	if (upper)
	{
	    data |= (k053244_read(addr) << 8);
	}

	if (lower)
	{
	    data |= k053244_read(addr + 1);
	}

	return data;
    }

    void k053245video::k053244_write16(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	addr = ((addr >> 1) & 0xF);
	addr &= ~1;

	if (upper)
	{
	    k053244_write(addr, (data >> 8));
	}

	if (lower)
	{
	    k053244_write((addr + 1), (data & 0xFF));
	}
    }

    uint8_t k053245video::k053244_read(uint16_t addr)
    {
	addr &= 0xF;
	cout << "Reading value from K053244 address of " << hex << int(addr) << endl;
	return 0;
    }

    void k053245video::k053244_write(uint16_t addr, uint8_t data)
    {
	addr &= 0xF;
	cout << "Writing value of " << hex << int(data) << " to K053244 address of " << hex << int(addr) << endl;
    }
};