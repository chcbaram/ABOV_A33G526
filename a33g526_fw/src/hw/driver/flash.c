/*
 * flash.c
 *
 *  Created on: 2021. 8. 1.
 *      Author: baram
 */


#include "flash.h"
#include "cli.h"

#ifdef _USE_HW_FLASH


#define FLASH_SECTOR_ADDR         0x00000000
#define FLASH_SECTOR_MAX          256
#define FLASH_SECTOR_SIZE         1024






static bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length);
static void flashUnlock(void);
static void flashLock(void);



#ifdef _USE_HW_CLI
static void cliFlash(cli_args_t *args);
#endif


bool flashInit(void)
{

#ifdef _USE_HW_CLI
  cliAdd("flash", cliFlash);
#endif

  return true;
}

bool flashErase(uint32_t addr, uint32_t length)
{
  bool ret = false;

  int16_t  start_sector_num = -1;
  uint32_t sector_count = 0;



  for (int i=0; i<FLASH_SECTOR_MAX; i++)
  {
    if (flashInSector(i, addr, length) == true)
    {
      if (start_sector_num < 0)
      {
        start_sector_num = i;
      }
      sector_count++;
    }
  }


  if (sector_count > 0)
  {
    flashUnlock();


    for (int i=0; i<sector_count; i++)
    {
      FLASH_Self_EraseSector(FMC, ((start_sector_num + i) * FLASH_SECTOR_SIZE));
    }

    ret = true;

    flashLock();
  }

  return ret;
}

bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret = true;


  if (addr%4 != 0)
  {
    return false;
  }

  flashUnlock();

  for (int i=0; i<length; i+=4)
  {
    uint32_t data;

    data  = p_data[i+0] << 0;
    data |= p_data[i+1] << 8;
    data |= p_data[i+2] <<16;
    data |= p_data[i+3] <<24;

    FLASH_Self_ProgramWORD(FMC, addr + i, data);
  }

  flashLock();

  return ret;
}

bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret = true;
  uint8_t *p_byte = (uint8_t *)addr;


  for (int i=0; i<length; i++)
  {
    p_data[i] = p_byte[i];
  }

  return ret;
}

bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length)
{
  bool ret = false;

  uint32_t sector_start;
  uint32_t sector_end;
  uint32_t flash_start;
  uint32_t flash_end;


  sector_start = FLASH_SECTOR_ADDR + (sector_num * FLASH_SECTOR_SIZE);
  sector_end   = sector_start + FLASH_SECTOR_SIZE - 1;
  flash_start  = addr;
  flash_end    = addr + length - 1;


  if (sector_start >= flash_start && sector_start <= flash_end)
  {
    ret = true;
  }

  if (sector_end >= flash_start && sector_end <= flash_end)
  {
    ret = true;
  }

  if (flash_start >= sector_start && flash_start <= sector_end)
  {
    ret = true;
  }

  if (flash_end >= sector_start && flash_end <= sector_end)
  {
    ret = true;
  }

  return ret;
}

void flashUnlock(void)
{
  uint32_t protect;
  uint32_t reg_val;


  protect = 1;


  // extended
  FMC->TEST =  (FMTEST_WRITE_KEY|FMTEST_EX);

  // protection
  reg_val = FMC->PROTECT;

  if (protect == 1)
  {
    reg_val |= (FMPROTECT_BP5|FMPROTECT_BP4|FMPROTECT_BP3|FMPROTECT_BP2|FMPROTECT_BP1|FMPROTECT_BP0|FMPROTECT_SP3|FMPROTECT_SP2|FMPROTECT_SP1|FMPROTECT_SP0);
  }
  else
  {
    reg_val &= ~(FMPROTECT_BP5|FMPROTECT_BP4|FMPROTECT_BP3|FMPROTECT_BP2|FMPROTECT_BP1|FMPROTECT_BP0|FMPROTECT_SP3|FMPROTECT_SP2|FMPROTECT_SP1|FMPROTECT_SP0);
  }

  FMC->PROTECT = reg_val;
}

void flashLock(void)
{

}




#ifdef _USE_HW_CLI
void cliFlash(cli_args_t *args)
{
  bool ret = false;



  if (args->argc == 1 && args->isStr(0, "info") == true)
  {
    for (int i=0; i<FLASH_SECTOR_MAX; i++)
    {
      cliPrintf("0x%X : %dKB\n", flash_tbl[i].addr, flash_tbl[i].length/1024);
    }

    ret = true;
  }

  if (args->argc == 3 && args->isStr(0, "read") == true)
  {
    uint32_t addr;
    uint32_t length;

    addr   = (uint32_t)args->getData(1);
    length = (uint32_t)args->getData(2);

    for (int i=0; i<length; i++)
    {
      cliPrintf("0x%X : 0x%X\n", addr+i, *((uint8_t *)(addr+i)));
    }

    ret = true;
  }

  if (args->argc == 3 && args->isStr(0, "erase") == true)
  {
    uint32_t addr;
    uint32_t length;

    addr   = (uint32_t)args->getData(1);
    length = (uint32_t)args->getData(2);

    if (flashErase(addr, length) == true)
    {
      cliPrintf("Erase OK\n");
    }
    else
    {
      cliPrintf("Erase Fail\n");
    }
  }

  if (args->argc == 3 && args->isStr(0, "write") == true)
  {
    uint32_t addr;
    uint32_t data;

    addr   = (uint32_t)args->getData(1);
    data   = (uint32_t)args->getData(2);

    if (flashWrite(addr, (uint8_t *)&data, 4) == true)
    {
      cliPrintf("Write OK\n");
    }
    else
    {
      cliPrintf("Write Fail\n");
    }

    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("flash info\n");
    cliPrintf("flash read  addr length\n");
    cliPrintf("flash erase addr length\n");
    cliPrintf("flash write addr data\n");
  }
}
#endif

#endif
