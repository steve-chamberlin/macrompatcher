#include <stdlib.h>
#include <string.h>

#include "macrompatcher.h"
#include "romdrv.h"

/* romdrv.h defines a ROM disk driver that will present a disk image starting
 * at 0x00880000 (512kb in to the ROM) and is 512kb in size, as a bootable
 * drive.
 * This function installs the driver in place of the .Sony floppy driver,
 * DRVR resource ID 4.
 */

RomErr InstallRomdiskDrvr(RomCtx *rom) {
	RomErr err;
	uint32_t sonyoffset;
	uint8_t *tmpptr;

	if(!rom || !rom->data) return eParmErr;

	err = GetDRVROffset(rom, 4, &sonyoffset);
	if(err != eSuccess) return err;

	tmpptr = rom->data + sonyoffset;

	memcpy(tmpptr, romdrv, sizeof(romdrv));

	return eSuccess;
}
