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

#ifndef BERRN_LIGHTNING_FIGHTERS
#define BERRN_LIGHTNING_FIGHTERS

#include <libblueberrn_api.h>
#include <driver.h>
#include <cpu/motorola68k.h>
#include <video/lgtnfght.h>
using namespace berrn;
using namespace std;

namespace berrn
{
    class LightningCore;

    class LIBBLUEBERRN_API LightningM68K : public BerrnInterface
    {
	public:
	    LightningM68K(berrndriver &drv, LightningCore &core);
	    ~LightningM68K();

	    void init();
	    void shutdown();

	    uint16_t readCPU16(bool upper, bool lower, uint32_t addr);
	    void writeCPU16(bool upper, bool lower, uint32_t addr, uint16_t data);

	private:
	    vector<uint8_t> main_rom;
	    array<uint8_t, 0x4000> main_ram;
	    berrndriver &driver;
	    LightningCore &main_core;

	    // TODO: Implement video system
	    array<uint8_t, 0x1000> palette_ram;
    };

    class LIBBLUEBERRN_API LightningCore
    {
	public:
	    LightningCore(berrndriver &drv);
	    ~LightningCore();

	    bool init_core();
	    void stop_core();
	    void run_core();
	    void key_changed(BerrnInput key, bool is_pressed);

	    uint8_t readDIP(int bank);

	    void writeA0018(uint8_t data);

	    uint16_t readK052109(bool upper, bool lower, uint32_t addr);
	    void writeK052109(bool upper, bool lower, uint32_t addr, uint16_t data);

	    void writeK053251(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint16_t readPalette(bool upper, bool lower, uint32_t addr);
	    void writePalette(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint16_t readK053244(bool upper, bool lower, uint32_t addr);
	    void writeK053244(bool upper, bool lower, uint32_t addr, uint16_t data);

	    uint16_t readK053245(bool upper, bool lower, uint32_t addr);
	    void writeK053245(bool upper, bool lower, uint32_t addr, uint16_t data);

	private:
	    berrndriver &driver;

	    LightningM68K *main_inter = NULL;
	    BerrnM68KCPU *main_cpu = NULL;

	    lightningvideo *video = NULL;
    };

    class LIBBLUEBERRN_API driverlgtnfght : public berrndriver
    {
	public:
	    driverlgtnfght();
	    ~driverlgtnfght();

	    string drivername();
	    uint32_t get_flags();

	    bool drvinit();
	    void drvshutdown();
	    void drvrun();

	    void keychanged(BerrnInput key, bool is_pressed);

	private:
	    LightningCore *core = NULL;
    };
};


#endif // BERRN_LIGHTNING_FIGHTERS