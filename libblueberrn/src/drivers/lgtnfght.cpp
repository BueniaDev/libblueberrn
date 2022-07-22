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

#include "lgtnfght.h"
using namespace berrn;

namespace berrn
{
    berrn_rom_start(lgtnfght)
	berrn_rom_region("maincpu", 0x40000, 0)
	    berrn_rom_load16_byte("939k02.e11", 0x0000, 0x20000)
	    berrn_rom_load16_byte("939k03.e15", 0x0001, 0x20000)
	berrn_rom_region("k052109", 0x100000, 0)
	    berrn_rom_load32_word("939a07.k14", 0x0000, 0x80000)
	    berrn_rom_load32_word("939a08.k19", 0x0002, 0x80000)
	berrn_rom_region("k053245", 0x100000, 0)
	    berrn_rom_load32_word("939a06.k8", 0x0000, 0x80000)
	    berrn_rom_load32_word("939a05.k2", 0x0002, 0x80000)
    berrn_rom_end

    LightningM68K::LightningM68K(berrndriver &drv, LightningCore &core) : driver(drv), main_core(core)
    {

    }

    LightningM68K::~LightningM68K()
    {

    }

    void LightningM68K::init()
    {
	main_rom = driver.get_rom_region("maincpu");
	main_ram.fill(0);
    }

    void LightningM68K::shutdown()
    {
	main_rom.clear();
    }

    uint16_t LightningM68K::readCPU16(bool upper, bool lower, uint32_t addr)
    {
	uint16_t data = 0;

	if (addr < 0x40000)
	{
	    if (upper)
	    {
		data |= (main_rom.at(addr) << 8);
	    }

	    if (lower)
	    {
		data |= main_rom.at(addr + 1);
	    }
	}
	else if (inRange(addr, 0x80000, 0x81000))
	{
	    data = main_core.readPalette(upper, lower, addr);
	}
	else if (inRange(addr, 0x90000, 0x94000))
	{
	    uint32_t ram_addr = (addr & 0x3FFF);
	    if (upper)
	    {
		data |= (main_ram.at(ram_addr) << 8);
	    }

	    if (lower)
	    {
		data |= main_ram.at(ram_addr + 1);
	    }
	}
	else if (addr == 0xA0000)
	{
	    if (lower)
	    {
		data |= main_core.readDIP(0);
	    }
	}
	else if (addr == 0xA0002)
	{
	    if (lower)
	    {
		data |= main_core.readDIP(1);
	    }
	}
	else if (addr == 0xA0004)
	{
	    if (lower)
	    {
		data |= main_core.readDIP(2);
	    }
	}
	else if (addr == 0xA0006)
	{
	    if (lower)
	    {
		data |= main_core.readDIP(3);
	    }
	}
	else if (addr == 0xA0008)
	{
	    if (lower)
	    {
		data |= main_core.readDIP(4);
	    }
	}
	else if (addr == 0xA0010)
	{
	    if (lower)
	    {
		data |= main_core.readDIP(5);
	    }
	}
	else if (inRange(addr, 0xA0020, 0xA0024))
	{
	    // TODO: Expose BeeKonami's K053260 core to internal API
	    data = 0x80; // Temporary hack until the K053260 core is exposed to the internal API
	}
	else if (inRange(addr, 0xB0000, 0xB4000))
	{
	    data = main_core.readK053245(upper, lower, addr);
	}
	else if (inRange(addr, 0xC0000, 0xC0020))
	{
	    data = main_core.readK053244(upper, lower, addr);
	}
	else if (inRange(addr, 0x100000, 0x108000))
	{
	    data = main_core.readK052109(upper, lower, addr);
	}
	else
	{
	    data = BerrnInterface::readCPU16(upper, lower, addr);
	}

	return data;
    }

    void LightningM68K::writeCPU16(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	if (addr < 0x40000)
	{
	    return;
	}
	else if (inRange(addr, 0x80000, 0x81000))
	{
	    main_core.writePalette(upper, lower, addr, data);
	}
	else if (inRange(addr, 0x90000, 0x94000))
	{
	    uint32_t ram_addr = (addr & 0x3FFF);

	    if (upper)
	    {
		main_ram.at(ram_addr) = (data >> 8);
	    }

	    if (lower)
	    {
		main_ram.at(ram_addr + 1) = (data & 0xFF);
	    }
	}
	else if (addr == 0xA0018)
	{
	    if (lower)
	    {
		main_core.writeA0018((data & 0xFF));
	    }
	}
	else if (addr == 0xA0028)
	{
	    // Watchdog timer (unimplemented)
	    return;
	}
	else if (inRange(addr, 0xA0020, 0xA0024))
	{
	    // TODO: Expose BeeKonami's K053260 core to internal API
	    return;
	}
	else if (addr == 0x10E800)
	{
	    return;
	}
	else if (inRange(addr, 0xB0000, 0xB4000))
	{
	    main_core.writeK053245(upper, lower, addr, data);
	}
	else if (inRange(addr, 0xC0000, 0xC0020))
	{
	    main_core.writeK053244(upper, lower, addr, data);
	}
	else if (inRange(addr, 0xE0000, 0xE0020))
	{
	    main_core.writeK053251(upper, lower, addr, data);
	}
	else if (inRange(addr, 0x100000, 0x108000))
	{
	    main_core.writeK052109(upper, lower, addr, data);
	}
	else
	{
	    BerrnInterface::writeCPU16(upper, lower, addr, data);
	}
    }

    LightningCore::LightningCore(berrndriver &drv) : driver(drv)
    {
	main_inter = new LightningM68K(driver, *this);
	main_cpu = new BerrnM68KCPU(driver, 12000000, *main_inter);

	video = new lightningvideo(driver);
    }

    LightningCore::~LightningCore()
    {

    }

    bool LightningCore::init_core()
    {
	if (!driver.loadROM(berrn_rom_name(lgtnfght)))
	{
	    return false;
	}

	auto screen = driver.get_screen();
	screen->set_refresh_hz(60);
	screen->set_vblank_time(time_in_usec(2500));
	screen->set_size(512, 256);
	screen->set_visarea(96, 415, 16, 239);

	screen->set_vblank_callback([&](bool line) -> void
	{
	    // Video is updated AFTER VBlank
	    if (line)
	    {
		return;
	    }

	    if (video->isIRQEnabled())
	    {
		main_cpu->fireInterruptLevel(5, true);
	    }

	    video->updatePixels();
	});

	auto &scheduler = driver.get_scheduler();
	screen->init();
	main_inter->init();
	main_cpu->init();
	video->init();
	scheduler.add_device(main_cpu);
	return true;
    }

    void LightningCore::stop_core()
    {
	auto screen = driver.get_screen();
	screen->shutdown();
	video->shutdown();
	main_inter->shutdown();
	main_cpu->shutdown();
    }

    void LightningCore::run_core()
    {
	driver.run_scheduler();
    }

    void LightningCore::key_changed(BerrnInput key, bool is_pressed)
    {
	string key_state = (is_pressed) ? "pressed" : "released";

	switch (key)
	{
	    case BerrnInput::BerrnCoin:
	    {
		cout << "Coin button has been " << key_state << endl;
	    }
	    break;
	    case BerrnInput::BerrnStartP1:
	    {
		cout << "P1 start button has been " << key_state << endl;
	    }
	    break;
	    case BerrnInput::BerrnLeftP1:
	    {
		cout << "P1 left button has been " << key_state << endl;
	    }
	    break;
	    case BerrnInput::BerrnRightP1:
	    {
		cout << "P1 right button has been " << key_state << endl;
	    }
	    break;
	    case BerrnInput::BerrnUpP1:
	    {
		cout << "P1 up button has been " << key_state << endl;
	    }
	    break;
	    case BerrnInput::BerrnDownP1:
	    {
		cout << "P1 down button has been " << key_state << endl;
	    }
	    break;
	    case BerrnInput::BerrnButton1P1:
	    {
		cout << "P1 button 1 has been " << key_state << endl;
	    }
	    break;
	    default: break;
	}
    }

    void LightningCore::writeA0018(uint8_t data)
    {
	string z80_str = testbit(data, 2) ? "Asserting" : "Clearing";
	cout << z80_str << " bit 2..." << endl;
	video->setRMRD(testbit(data, 3));
    }

    uint16_t LightningCore::readPalette(bool upper, bool lower, uint32_t addr)
    {
	return video->readPalette(upper, lower, addr);
    }

    void LightningCore::writePalette(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	video->writePalette(upper, lower, addr, data);
    }

    uint8_t LightningCore::readDIP(int bank)
    {
	uint8_t data = 0;
	switch (bank)
	{
	    case 0: data = 0xFB; break; // COINS
	    case 1: data = 0xFF; break; // P1
	    case 2: data = 0xFF; break; // P2
	    case 3: data = 0x5E; break; // DSW1
	    case 4: data = 0xFF; break; // DSW2
	    case 5: data = 0xFD; break; // DSW3
	    default:
	    {
		cout << "Reading from DIP switch of " << dec << int(bank) << endl;
		exit(0);
	    }
	    break;
	}

	return data;
    }

    uint16_t LightningCore::readK052109(bool upper, bool lower, uint32_t addr)
    {
	return video->tileRead(upper, lower, addr);
    }

    void LightningCore::writeK052109(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	video->tileWrite(upper, lower, addr, data);
    }

    uint16_t LightningCore::readK053244(bool upper, bool lower, uint32_t addr)
    {
	return video->readK053244(upper, lower, addr);
    }

    void LightningCore::writeK053244(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	video->writeK053244(upper, lower, addr, data);
    }

    uint16_t LightningCore::readK053245(bool upper, bool lower, uint32_t addr)
    {
	return video->readK053245(upper, lower, addr);
    }

    void LightningCore::writeK053245(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	video->writeK053245(upper, lower, addr, data);
    }

    void LightningCore::writeK053251(bool upper, bool lower, uint32_t addr, uint16_t data)
    {
	video->writePriority(upper, lower, addr, data);
    }

    driverlgtnfght::driverlgtnfght()
    {
	core = new LightningCore(*this);
    }

    driverlgtnfght::~driverlgtnfght()
    {

    }

    string driverlgtnfght::drivername()
    {
	return "lgtnfght";
    }

    uint32_t driverlgtnfght::get_flags()
    {
	return berrn_rot_90;
    }

    bool driverlgtnfght::drvinit()
    {
	return core->init_core();
    }

    void driverlgtnfght::drvshutdown()
    {
	core->stop_core();
    }
  
    void driverlgtnfght::drvrun()
    {
	core->run_core();
    }

    void driverlgtnfght::keychanged(BerrnInput key, bool is_pressed)
    {
	core->key_changed(key, is_pressed);
    }
};