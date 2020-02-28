/***************************************************************************//**
    \file          uds-util.c
    \author        
    \mail          
    \version       0.00
    \date          2016-09-27
    \description   uds network code, base on ISO 14229
*******************************************************************************/

/*******************************************************************************
    Include Files
*******************************************************************************/
#include <stdlib.h>
//#include "ucos_ii.h"
#include "Type.h"
#include "uds_type.h"
#include "uds_util.h"
/*******************************************************************************
    Type Definition
*******************************************************************************/

/*******************************************************************************
    Function  Definition
*******************************************************************************/
/**
 * rand_u8 - get a random u8
 *
 * @void  :
 *
 * returns:
 *     a uint8
 */
uint8
rand_u8 (void)
{
	uint32 ticks;
//	ticks = OSTimeGet();
	srand(ticks);

	return (rand() % 255);
}

/**
 * host_to_canl - transmit a long or short int to can-net endian
 *
 * @buf: ther buffer to storage the result
 * @val: the value to be transformed
 *
 * returns:
 *     0 - ok, -1 - err
 */
int
host_to_canl (uint8 buf[], uint32 val)
{
	if (buf == NULL) return -1;

	buf[0] = (val>>24) & 0xff;
	buf[1] = (val>>16) & 0xff;
	buf[2] = (val>>8) & 0xff;
	buf[3] = (val>>0) & 0xff;

	return 0;
}

int
host_to_cans (uint8 buf[], uint16 val)
{
	if (buf == NULL) return -1;

	buf[0] = (val>>8) & 0xff;
	buf[1] = (val>>0) & 0xff;

	return 0;
}


/**
 * can_to_hostl - transmit  can-net endian buffer to long or short int
 *
 * @buf: ther buffer to be transformed
 * @pval: 
 *
 * returns:
 *     0 - ok, -1 - err
 */
int
can_to_hostl (uint8 buf[], uint32 *pval)
{
	uint32 val;
	if (buf == NULL || pval == NULL) return -1;

    val = 0;
	val |= ((uint32)buf[0]) << 24;
	val |= ((uint32)buf[1]) << 16;
	val |= ((uint32)buf[2]) << 8;
	val |= ((uint32)buf[3]) << 0;

    *pval = val;
	return 0;
}
void
* memcpy(void* dst,const void* src,int n)
{
	char* pdst = (char *)dst;
	char* psrc = (char *)src;
    if (dst == NULL || src == NULL || n <= 0)
    {
        //void* 一定要有返回值 void可以没有返回值 void*和void不相同
        return NULL;
    }
    
    if (psrc < pdst && pdst < psrc + n)
    {
        pdst = pdst + n - 1;
        psrc = psrc + n - 1;
        while (n--)
        {
            *pdst = *psrc;
            pdst--;
            psrc--;
        }
    }
    else
    {
        while (n--)
        {
            *pdst = *psrc;
            pdst++;
            psrc++;
        }
    }
    return dst;
}

/****************EOF****************/
