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

#ifndef BERRN_TEMPLATE
#define BERRN_TEMPLATE

#include <libblueberrn_api.h>
#include <driver.h>
using namespace berrn;
using namespace std;

namespace berrn
{
    class LIBBLUEBERRN_API drivertemplate : public berrndriver
    {
	public:
	    drivertemplate();
	    ~drivertemplate();

	    string drivername();

	    bool drvinit();
	    void drvshutdown();
	    void drvrun();

	    void keychanged(BerrnInput key, bool is_pressed);
    };
};


#endif // BERRN_TEMPLATE