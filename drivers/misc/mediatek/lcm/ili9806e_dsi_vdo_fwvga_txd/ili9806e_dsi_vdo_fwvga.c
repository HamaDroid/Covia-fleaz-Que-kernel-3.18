/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (480)
#define FRAME_HEIGHT (854)

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#define REGFLAG_DELAY                                       0XFFE
#define REGFLAG_END_OF_TABLE                                0xFFF   // END OF REGISTERS MARKER

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))


#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)   


#define   LCM_DSI_CMD_MODE						0

struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};



static struct LCM_setting_table lcm_initialization_setting[] = {

{0xFF,5,{0xFF,0x98,0x06,0x04,0x01}},
         
{0x08,1,{0x10}},
         
{0x21,1,{0x01}},
         
{0x30,1,{0x01}},
         
{0x31,1,{0x02}},
         
{0x40,1,{0x18}},
         
{0x41,1,{0x73}},
         
{0x42,1,{0x03}},
         
{0x43,1,{0x0d}},
         
{0x44,1,{0x06}},
         
{0x50,1,{0x78}},
         
{0x51,1,{0x78}},
         
{0x52,1,{0x00}},
         
{0x53,1,{0x18}},//0x18
         
{0x60,1,{0x07}},
         
{0x61,1,{0x00}},
         
{0x62,1,{0x07}},
         
{0x63,1,{0x00}},
         
{0xA0,1,{0x00}},
         
{0xA1,1,{0x0a}},
         
{0xA2,1,{0x13}},
         
{0xA3,1,{0x0d}},
         
{0xA4,1,{0x06}},
         
{0xA5,1,{0x0c}},
         
{0xA6,1,{0x07}},
         
{0xA7,1,{0x05}},
         
{0xA8,1,{0x08}},
         
{0xA9,1,{0x0C}},
         
{0xAA,1,{0x11}},
         
{0xAB,1,{0x07}},
         
{0xAC,1,{0x0e}},
         
{0xAD,1,{0x17}},
         
{0xAE,1,{0x10}},
         
{0xAF,1,{0x00}},
         
{0xC0,1,{0x00}},
         
{0xC1,1,{0x0b}},
         
{0xC2,1,{0x13}},
         
{0xC3,1,{0x0c}},
         
{0xC4,1,{0x06}},
         
{0xC5,1,{0x0d}},
         
{0xC6,1,{0x07}},
         
{0xC7,1,{0x04}},
         
{0xC8,1,{0x08}},
         
{0xC9,1,{0x0C}},
         
{0xCA,1,{0x11}},
         
{0xCB,1,{0x07}},
         
{0xCC,1,{0x0e}},
         
{0xCD,1,{0x17}},
         
{0xCE,1,{0x10}},
         
{0xCF,1,{0x00}},
         
{0xFF,5,{0xFF,0x98,0x06,0x04,0x06}},
         
{0x00,1,{0x21}},
         
{0x01,1,{0x06}},
         
{0x02,1,{0xA0}},    
         
{0x03,1,{0x02}},
         
{0x04,1,{0x01}},
         
{0x05,1,{0x01}},
         
{0x06,1,{0x80}},    
         
{0x07,1,{0x03}},  
         
{0x08,1,{0x06}},  
         
{0x09,1,{0x80}},    
         
{0x0A,1,{0x00}},    
         
{0x0B,1,{0x00}},    
         
{0x0C,1,{0x20}},
         
{0x0D,1,{0x20}},
         
{0x0E,1,{0x09}},
         
{0x0F,1,{0x00}},
         
{0x10,1,{0xFF}},
         
{0x11,1,{0xE0}},
         
{0x12,1,{0x00}},
         
{0x13,1,{0x00}},
         
{0x14,1,{0x00}},
         
{0x15,1,{0xC0}},
         
{0x16,1,{0x08}},
         
{0x17,1,{0x00}},
         
{0x18,1,{0x00}},
         
{0x19,1,{0x00}},
         
{0x1A,1,{0x00}},
         
{0x1B,1,{0x00}},
         
{0x1C,1,{0x00}},
         
{0x1D,1,{0x00}},
         
{0x20,1,{0x01}},
         
{0x21,1,{0x23}},
         
{0x22,1,{0x45}},
         
{0x23,1,{0x67}},
         
{0x24,1,{0x01}},
         
{0x25,1,{0x23}},
         
{0x26,1,{0x45}},
         
{0x27,1,{0x67}},
         
{0x30,1,{0x12}},
         
{0x31,1,{0x22}},
         
{0x32,1,{0x22}},
         
{0x33,1,{0x22}},
         
{0x34,1,{0x87}},
         
{0x35,1,{0x96}},
         
{0x36,1,{0xAA}},
         
{0x37,1,{0xDB}},
         
{0x38,1,{0xCC}},
         
{0x39,1,{0xBD}},
         
{0x3A,1,{0x78}},
         
{0x3B,1,{0x69}},
         
{0x3C,1,{0x22}},
         
{0x3D,1,{0x22}},
         
{0x3E,1,{0x22}},
         
{0x3F,1,{0x22}},
         
{0x40,1,{0x22}},
         
{0x52,1,{0x10}},
         
{0x53,1,{0x10}},
         
{0xFF,5,{0xFF,0x98,0x06,0x04,0x07}},
         
{0x02,1,{0x77}},
         
{0xE1,1,{0x79}},
         
{0x18,1,{0x1D}},
         
{0x26,1,{0xB2}},
         
{0xFF,5,{0xFF,0x98,0x06,0x04,0x00}},
         
{0x36,1,{0x00}},
         
{0x11,1,{0x00}},

{REGFLAG_DELAY, 120, {}},
{0x29, 1,{0x00}},  
{REGFLAG_DELAY, 20, {}},  
{REGFLAG_END_OF_TABLE, 0x00, {}},
};


static struct LCM_setting_table lcm_sleep_in_setting[] =
{
    // Display off sequence
    {0x28, 0, {0x00}},
    {REGFLAG_DELAY, 10, {}},
    // Sleep Mode On
    {0x10, 0, {0x00}},
    {REGFLAG_DELAY, 120, {}},
    {REGFLAG_END_OF_TABLE, 0x00, {}}
};

#if 0
static struct LCM_setting_table lcm_sleep_out_setting[] =
{
    // Sleep Out
    {0x11, 0, {0x00}},
    {REGFLAG_DELAY, 120, {}},

    // Display ON
    {0x29, 0, {0x00}},
    {REGFLAG_DELAY, 10, {}},

    {REGFLAG_END_OF_TABLE, 0x00, {}}
};
#endif


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;

    for(i = 0; i < count; i++)
    {

        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd)
        {

            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;

            case REGFLAG_END_OF_TABLE :
                break;

            default:
				
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
//                dsi_set_cmdq_dcs(cmd, table[i].count, table[i].para_list, force_update);
        }
    }

}

static void init_lcm_registers(void)
{
	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}



// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{

		memset(params, 0, sizeof(LCM_PARAMS));
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

		// enable tearing-free
//		params->dbi.te_mode 				= LCM_DBI_TE_MODE_VSYNC_ONLY;
//		params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;

        #if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
        #else
		params->dsi.mode   = SYNC_PULSE_VDO_MODE;
//		params->dsi.mode   = BURST_VDO_MODE;
		//params->dsi.mode   = SYNC_EVENT_VDO_MODE; 
		
        #endif
	
		// DSI
		/* Command mode setting */
		//1 Three lane or Four lane
//		params->dsi.LANE_NUM				= LCM_THREE_LANE;
	params->dsi.LANE_NUM				= LCM_TWO_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
		params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
		params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		// Highly depends on LCD driver capability.
		// Not support in MT6573
		params->dsi.packet_size=256;

		// Video mode setting		//for low temp. can't initial
		params->dsi.intermediat_buffer_num = 2;//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;

	params->dsi.vertical_sync_active = 2; 
	params->dsi.vertical_backporch = 20; 
	params->dsi.vertical_frontporch = 20; 
	params->dsi.vertical_active_line = FRAME_HEIGHT; 

	params->dsi.horizontal_sync_active				= 10;
	params->dsi.horizontal_backporch				= 60;
	params->dsi.horizontal_frontporch				= 200;
	params->dsi.horizontal_active_pixel 			= FRAME_WIDTH;



	// DSI MIPI Spec parameters setting
	/*params->dsi.HS_TRAIL = 6;
	params->dsi.HS_ZERO = 9;
	params->dsi.HS_PRPR = 5;
	params->dsi.LPX = 4;
	params->dsi.TA_SACK = 1;
	params->dsi.TA_GET = 20;
	params->dsi.TA_SURE = 6;
	params->dsi.TA_GO = 16;
	params->dsi.CLK_TRAIL = 5;
	params->dsi.CLK_ZERO = 18;
	params->dsi.LPX_WAIT = 1;
	params->dsi.CONT_DET = 0;
	params->dsi.CLK_HS_PRPR = 4;*/
	// Bit rate calculation
	params->dsi.esd_check_enable = 1;
	params->dsi.customization_esd_check_enable = 1;
	params->dsi.lcm_esd_check_table[0].cmd         = 0x0a;
	params->dsi.lcm_esd_check_table[0].count       = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0]   = 0x9c;
	
	params->dsi.PLL_CLOCK = 241;

}

static void lcm_init(void)
{


	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(120); 

	init_lcm_registers();

}


static void lcm_suspend(void)
{
    #ifdef BUILD_LK
               // printf("%s, LK nt35592 debug: nt35590 id = 0x%08x\n", __func__, id);
    #else
                printk("kernel nt35521 debug: --------suspend--------\n");
    #endif
    push_table(lcm_sleep_in_setting, sizeof(lcm_sleep_in_setting) / sizeof(struct LCM_setting_table), 1);
    SET_RESET_PIN(1);
    MDELAY(20);
    SET_RESET_PIN(0);
	MDELAY(50);
	SET_RESET_PIN(1);
	MDELAY(20);
}


static void lcm_resume(void)
{

    #ifdef BUILD_LK
               // printf("%s, LK nt35592 debug: nt35590 id = 0x%08x\n", __func__, id);
    #else
                printk("---------kernel nt35521 resume\n");
    #endif
    
	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);

	SET_RESET_PIN(1);
	MDELAY(120); 	
 
	init_lcm_registers();
}
         
#if (LCM_DSI_CMD_MODE)
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);

//	data_array[0]= 0x00290508; //HW bug, so need send one HS packet
//	dsi_set_cmdq(&data_array, 1, 1);
	
	data_array[0]= 0x002c3909;
	dsi_set_cmdq(&data_array, 1, 0);

}
#endif

static unsigned int lcm_compare_id(void)
{
         unsigned int id=0;
        unsigned char buffer[2];
        unsigned int array[16];


        SET_RESET_PIN(1);
		MDELAY(10);
        SET_RESET_PIN(0);
        MDELAY(10);

        SET_RESET_PIN(1);
        MDELAY(120);

        array[0] = 0x00023700;// read id return two byte,version and id
        dsi_set_cmdq(array, 1, 1);

        read_reg_v2(0xDB, buffer, 2);
        id = buffer[0]; //we only need ID
    #ifdef BUILD_LK
                printf("%s, LK nt35590 debug: nt35590 id = 0x%08x\n", __func__, id);
    #else
                printk("%s, kernel nt35521 horse debug: nt35590 id = 0x%08x\n", __func__, id);
    #endif
	
//	if(id == 0x80)
        return 1;
//    else
//        return 0;
}

#if 0
//static int esd_cnt=0;
static unsigned int lcm_esd_check(void)
{
#ifndef BUILD_LK
	//#if 1
		char  buffer[3];
		int   array[4];
	
		array[0] = 0x00013700;
		dsi_set_cmdq(array, 1, 1);
	
		read_reg_v2(0x0a, buffer, 1);
		printk("jacob test lcm_esd_check buffer[0]=0x%x\n",buffer[0]);
		if(buffer[0]==0x9c)
		{
			return FALSE;
		}
		else
		{	
			return TRUE;
		}
#else
		return FALSE;
#endif
	}


static unsigned int lcm_esd_recover(void)
{
#ifndef BUILD_LK	
	printk("jacob test lcm_esd_recover\n");
	lcm_init();
#endif
	return TRUE;
}
#endif

LCM_DRIVER ili9806e_dsi_vdo_fwvga_drv_txd = {
	.name = "ili9806e_dsi_vdo_fwvga_txd",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id     = lcm_compare_id,
#if (LCM_DSI_CMD_MODE)
    .update         = lcm_update,
#endif
    };
