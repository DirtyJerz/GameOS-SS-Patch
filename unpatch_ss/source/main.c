/*
 * Copyright (C) DirtyJerz 2011 (word to ya motha)
 * modified from git://git.gitbrew.org/ps3/otheros-utils/increase_bootmem_size.git
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <unistd.h>

#include <psl1ght/lv2/net.h>

#include <lv2_syscall.h>
#include <udp_printf.h>

/*
 * GameOS system manager object in HV process 9
 */
#define GAMEOS_SYSMGR_OFFSET				0x0075bdd0ull /* 0x000a5dd0ull */

/*
 * 3.55 offsets
 */

#define DISPMGR_SET_LAID_OFFSET_355 			(GAMEOS_SYSMGR_OFFSET + 0x0016f3bcull)
#define DISPMGR_SS_ID_OFFSET_355			(GAMEOS_SYSMGR_OFFSET + 0x0016f3e0ull)
#define DISPMGR_SEND_SPM_REQ_OFFSET_355 		(GAMEOS_SYSMGR_OFFSET + 0x0016f458ull)

#define DISPMGR_LAID_ENABLE				0xf8010098ull
#define DISPMGR_SS_ID_ENABLE				0x4bfff0e5ull
#define DISPMGR_SPM_ENABLE1				0x38a10070ull
#define DISPMGR_SPM_ENABLE2				0x9be10070ull
#define DISPMGR_SPM_ENABLE3				0x48005fa5ull

/*
 * main
 */
int main(int argc, char **argv)
{
	netInitialize();

	udp_printf_init();

	PRINTF("%s:%d: start\n", __func__, __LINE__);

	
	PRINTF("%s:%d: unpatching overwriting of LAID\n", __func__, __LINE__);

	lv2_lv1_poke(DISPMGR_SET_LAID_OFFSET_355, DISPMGR_LAID_ENABLE);

	PRINTF("%s:%d: end\n", __func__, __LINE__);


	PRINTF("%s:%d: enabling SS ID check\n", __func__, __LINE__);

        lv2_lv1_poke(DISPMGR_SS_ID_OFFSET_355, DISPMGR_SS_ID_ENABLE);

        PRINTF("%s:%d: end\n", __func__, __LINE__);


	PRINTF("%s:%d: enabling SPM\n", __func__, __LINE__);

        lv2_lv1_poke(DISPMGR_SEND_SPM_REQ_OFFSET_355, DISPMGR_SPM_ENABLE1);
	lv2_lv1_poke(DISPMGR_SEND_SPM_REQ_OFFSET_355 + 4, DISPMGR_SPM_ENABLE2);
	lv2_lv1_poke(DISPMGR_SEND_SPM_REQ_OFFSET_355 + 8, DISPMGR_SPM_ENABLE3);

        PRINTF("%s:%d: end\n", __func__, __LINE__);


	udp_printf_deinit();

	netDeinitialize();

	return 0;
}
