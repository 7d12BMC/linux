
#include <linux/delay.h>

#include "ast_drv.h"
#include "ast_hdmitx.h"

#define I2C_BASE	0x1e780000

static void SetI2CReg(struct drm_device *dev, u8 jChannel, u8 DeviceAddr, u8 jIndex, u8 jData )
{
	struct ast_private *ast = dev->dev_private;
    u32 ulData, ulI2CBase, ulI2CAddr;
    u8 *ulI2CPortBase;
    u8 *pjMMIOBase;
    u32 retry;

    {
        pjMMIOBase = ast->ioregs;
        ulI2CBase = I2C_BASE;
        ulI2CPortBase = pjMMIOBase + 0x1a000 + 0x40 * jChannel;
        ulI2CAddr = DeviceAddr;
    }

    *(u32 *) (pjMMIOBase + 0xF004) = ulI2CBase;
    *(u32 *) (pjMMIOBase + 0xF000) = 0x1;

    *(u32 *) (ulI2CPortBase + 0x00) = 0x0;
    *(u32 *) (ulI2CPortBase + 0x04) = 0x77743356;
    *(u32 *) (ulI2CPortBase + 0x08) = 0x0;
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x00) = 0x1;
    *(u32 *) (ulI2CPortBase + 0x0C) = 0xAF;
    *(u32 *) (ulI2CPortBase + 0x20) = ulI2CAddr;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x03;
    retry = 0;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
        udelay(10);
        if (retry++ > 1000)
            goto Exit_SetI2CReg;
    } while (!(ulData & 0x01));
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x20) = (u32) jIndex;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x02;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
    } while (!(ulData & 0x01));
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x20) = (u32) jData;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x02;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
    } while (!(ulData & 0x01));
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x0C) |= 0x10;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x20;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
    } while (!(ulData & 0x10));
    *(u32 *) (ulI2CPortBase + 0x0C) &= 0xffffffef;
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    udelay(10);

Exit_SetI2CReg:
    ;
}

static u8 GetI2CReg(struct drm_device *dev, u8 jChannel, u8 DeviceAddr, u8 jIndex)
{
	struct ast_private *ast = dev->dev_private;
    u8 jData;
    u32 ulData, ulI2CBase, ulI2CAddr;
    u8 *ulI2CPortBase;
    u8 *pjMMIOBase;
    u32 retry;

    {
        pjMMIOBase = ast->ioregs;
        ulI2CBase = I2C_BASE;
        ulI2CPortBase = pjMMIOBase + 0x1a000 + 0x40 * jChannel;
        ulI2CAddr = DeviceAddr;
    }

    *(u32 *) (pjMMIOBase + 0xF004) = ulI2CBase;
    *(u32 *) (pjMMIOBase + 0xF000) = 0x1;

    *(u32 *) (ulI2CPortBase + 0x00) = 0x0;
    *(u32 *) (ulI2CPortBase + 0x04) = 0x77743356;
    *(u32 *) (ulI2CPortBase + 0x08) = 0x0;
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x00) = 0x1;
    *(u32 *) (ulI2CPortBase + 0x0C) = 0xAF;
    *(u32 *) (ulI2CPortBase + 0x20) = ulI2CAddr;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x03;
    retry = 0;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
        udelay(10);
        if (retry++ > 1000)
            return 0;
    } while (!(ulData & 0x01));
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x20) = (u32) jIndex;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x02;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
    } while (!(ulData & 0x01));
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x20) = ulI2CAddr + 1;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x1B;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
    } while (!(ulData & 0x04));
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    *(u32 *) (ulI2CPortBase + 0x0C) |= 0x10;
    *(u32 *) (ulI2CPortBase + 0x14) = 0x20;
    do {
        ulData = *(u32 *) (ulI2CPortBase + 0x10);
    } while (!(ulData & 0x10));
    *(u32 *) (ulI2CPortBase + 0x0C) &= 0xffffffef;
    *(u32 *) (ulI2CPortBase + 0x10) = 0xffffffff;
    jData = (u8) ((*(u32 *) (ulI2CPortBase + 0x20) & 0xFF00) >> 8);

    return (jData);
}
static bool I2C_Read_ByteN(struct drm_device *dev, u8 Addr, u8 RegAddr, u8 *pData, int N)
{
    u8 i, *pI2CData, jData;

    pI2CData = pData;
    for (i = 0; i < N; i++)
    {
        jData = GetI2CReg(dev, (u8) HDMI_I2C_CHANNEL, Addr, (RegAddr + i));
        *(u8 *) (pI2CData++) = jData;
    }

    return TRUE ;
}

static bool I2C_Write_ByteN(struct drm_device *dev, u8 Addr,u8 RegAddr,u8 *pData,int N)
{
    u8   i;

    for (i = 0; i < N; i++)
    {
        SetI2CReg(dev, (u8) HDMI_I2C_CHANNEL, Addr, (RegAddr + i), *(u8 *)(pData + i));
    }

    return TRUE ;
}

static u8 I2C_Read_Byte(struct drm_device *dev, u8 Addr,u8 RegAddr)
{
    u8 data ;

    I2C_Read_ByteN(dev, Addr,RegAddr,&data, 1)  ;

    return data ;
}

static bool I2C_Write_Byte(struct drm_device *dev, u8 Addr,u8 RegAddr,u8 Data)
{
    return I2C_Write_ByteN(dev, Addr,RegAddr,&Data, 1) ;
}

static u8 HDMITX_ReadI2C_Byte(struct drm_device *dev, u8 RegAddr)
{
	return I2C_Read_Byte(dev, HDMI_TX_I2C_SLAVE_ADDR,RegAddr) ;
}

static bool HDMITX_WriteI2C_Byte(struct drm_device *dev, u8 RegAddr,u8 Data)
{
	return I2C_Write_Byte(dev, HDMI_TX_I2C_SLAVE_ADDR,RegAddr,Data) ;
}

static bool HDMITX_ReadI2C_ByteN(struct drm_device *dev, u8 RegAddr,u8 *pData,int N)
{
	return I2C_Read_ByteN(dev, HDMI_TX_I2C_SLAVE_ADDR,RegAddr,pData,N) ;
}

static bool HDMITX_SetI2C_Byte(struct drm_device *dev, u8 Reg,u8 Mask,u8 Value)
{
    u8 Temp;
    if( Mask != 0xFF )
    {
        Temp=HDMITX_ReadI2C_Byte(dev, Reg);
        Temp&=(~Mask);
        Temp|=Value&Mask;
    }
    else
    {
        Temp=Value;
    }
    return HDMITX_WriteI2C_Byte(dev, Reg,Temp);
}

static void hdmitx_LoadRegSetting(struct drm_device *dev, RegSetEntry table[])
{
    u32 i ;

    for( i = 0 ;  ; i++ )
    {
        if( table[i].offset == 0 && table[i].invAndMask == 0 && table[i].OrMask == 0 )
        {
            return ;
        }
        else if( table[i].invAndMask == 0 && table[i].OrMask == 0 )
        {
            udelay(table[i].offset);
        }
        else if( table[i].invAndMask == 0xFF )
        {
            HDMITX_WriteI2C_Byte(dev, table[i].offset,table[i].OrMask);
        }
        else
        {
            HDMITX_SetI2C_Byte(dev, table[i].offset,table[i].invAndMask,table[i].OrMask);
        }
    }
}

/*
 * Export Procedures
 */
bool ast_hdmi_check(struct drm_device *dev)
{
	// Check ite 66121 chip
    u16 VendorID, DeviceID;
    u8 pData[4];

    Switch_HDMITX_Bank(dev, 0) ;
    HDMITX_ReadI2C_ByteN(dev, 0x00, pData, 4);
    VendorID = *(u16 *)(pData) & 0xFFFF;
    DeviceID = *(u16 *)(pData + 2) & 0x0FFF;
    if ((VendorID != 0x4954) || (DeviceID != 0x0612))
    {
        return FALSE;
    }

    return (TRUE);

}

#ifndef INV_INPUT_PCLK
#define PCLKINV 0
#else
#define PCLKINV B_TX_VDO_LATCH_EDGE
#endif

#ifndef INV_INPUT_ACLK
    #define InvAudCLK 0
#else
    #define InvAudCLK B_TX_AUDFMT_FALL_EDGE_SAMPLE_WS
#endif

#define INIT_CLK_HIGH
/* #define INIT_CLK_LOW */

RegSetEntry HDMITX_Init_Table[] = {

    {0x0F, 0x40, 0x00},

    {0x62, 0x08, 0x00},
    {0x64, 0x04, 0x00},
    {0x01,0x00,0x00},/*idle(100)*/

    {0x04, 0x20, 0x20},
    {0x04, 0x1D, 0x1D},
    {0x01,0x00,0x00},/*idle(100)*/
    {0x0F, 0x01, 0x00}, /* bank 0 */
    #ifdef INIT_CLK_LOW
        {0x62, 0x90, 0x10},
        {0x64, 0x89, 0x09},
        {0x68, 0x10, 0x10},
    #endif

    {0xD1, 0x0E, 0x0C},
    {0x65, 0x03, 0x00},
    #ifdef NON_SEQUENTIAL_YCBCR422 /* for ITE HDMIRX */
        {0x71, 0xFC, 0x1C},
    #else
        {0x71, 0xFC, 0x18},
    #endif

    {0x8D, 0xFF, CEC_I2C_SLAVE_ADDR},
    {0x0F, 0x08, 0x08},

    {0xF8,0xFF,0xC3},
    {0xF8,0xFF,0xA5},
    {0x20, 0x80, 0x80},
    {0x37, 0x01, 0x00},
    {0x20, 0x80, 0x00},
    {0xF8,0xFF,0xFF},

    {0x59, 0xD8, 0x40|PCLKINV},
    {0xE1, 0x20, InvAudCLK},
    {0x05, 0xC0, 0x40},
    {REG_TX_INT_MASK1, 0xFF, (u8)(~(B_TX_RXSEN_MASK|B_TX_HPD_MASK))},
    {REG_TX_INT_MASK2, 0xFF, (u8)(~(B_TX_KSVLISTCHK_MASK|B_TX_AUTH_DONE_MASK|B_TX_AUTH_FAIL_MASK))},
    {REG_TX_INT_MASK3, 0xFF, (u8)(~(B_TX_VIDSTABLE_MASK))},
    {0x0C, 0xFF, 0xFF},
    {0x0D, 0xFF, 0xFF},
    {0x0E, 0x03, 0x03},

    {0x0C, 0xFF, 0x00},
    {0x0D, 0xFF, 0x00},
    {0x0E, 0x02, 0x00},
    {0x09, 0x03, 0x00}, /* Enable HPD and RxSen Interrupt */
    {0,0,0}
};

RegSetEntry HDMITX_DefaultVideo_Table[] = {

    /* //////////////////////////////////////////////////
      // Config default output format.
      /////////////////////////////////////////////////// */
    {0x72, 0xff, 0x00},
    {0x70, 0xff, 0x00},
#ifndef DEFAULT_INPUT_YCBCR
/* GenCSC\RGB2YUV_ITU709_16_235.c */
    {0x72, 0xFF, 0x02},
    {0x73, 0xFF, 0x00},
    {0x74, 0xFF, 0x80},
    {0x75, 0xFF, 0x00},
    {0x76, 0xFF, 0xB8},
    {0x77, 0xFF, 0x05},
    {0x78, 0xFF, 0xB4},
    {0x79, 0xFF, 0x01},
    {0x7A, 0xFF, 0x93},
    {0x7B, 0xFF, 0x00},
    {0x7C, 0xFF, 0x49},
    {0x7D, 0xFF, 0x3C},
    {0x7E, 0xFF, 0x18},
    {0x7F, 0xFF, 0x04},
    {0x80, 0xFF, 0x9F},
    {0x81, 0xFF, 0x3F},
    {0x82, 0xFF, 0xD9},
    {0x83, 0xFF, 0x3C},
    {0x84, 0xFF, 0x10},
    {0x85, 0xFF, 0x3F},
    {0x86, 0xFF, 0x18},
    {0x87, 0xFF, 0x04},
#else
/* GenCSC\YUV2RGB_ITU709_16_235.c */
    {0x0F, 0x01, 0x00},
    {0x72, 0xFF, 0x03},
    {0x73, 0xFF, 0x00},
    {0x74, 0xFF, 0x80},
    {0x75, 0xFF, 0x00},
    {0x76, 0xFF, 0x00},
    {0x77, 0xFF, 0x08},
    {0x78, 0xFF, 0x53},
    {0x79, 0xFF, 0x3C},
    {0x7A, 0xFF, 0x89},
    {0x7B, 0xFF, 0x3E},
    {0x7C, 0xFF, 0x00},
    {0x7D, 0xFF, 0x08},
    {0x7E, 0xFF, 0x51},
    {0x7F, 0xFF, 0x0C},
    {0x80, 0xFF, 0x00},
    {0x81, 0xFF, 0x00},
    {0x82, 0xFF, 0x00},
    {0x83, 0xFF, 0x08},
    {0x84, 0xFF, 0x00},
    {0x85, 0xFF, 0x00},
    {0x86, 0xFF, 0x87},
    {0x87, 0xFF, 0x0E},
#endif

    {0x04, 0x08, 0x00},
    {0,0,0}
};

RegSetEntry HDMITX_SetHDMI_Table[] = {

    /* //////////////////////////////////////////////////
       // Config default HDMI Mode
       /////////////////////////////////////////////////// */
    {0xC0, 0x01, 0x01},
    {0xC1, 0x03, 0x03},
    {0xC6, 0x03, 0x03},
    {0,0,0}
};

RegSetEntry HDMITX_SetDVI_Table[] = {

    /* //////////////////////////////////////////////////
       // Config default HDMI Mode
       /////////////////////////////////////////////////// */
    {0x0F, 0x01, 0x01},
    {0x58, 0xFF, 0x00},
    {0x0F, 0x01, 0x00},
    {0xC0, 0x01, 0x00},
    {0xC1, 0x03, 0x02},
    {0xC6, 0x03, 0x00},
    {0,0,0}
};

RegSetEntry HDMITX_DefaultAVIInfo_Table[] = {

    /* //////////////////////////////////////////////////
       // Config default avi infoframe
       /////////////////////////////////////////////////// */
    {0x0F, 0x01, 0x01},
    {0x58, 0xFF, 0x10},
    {0x59, 0xFF, 0x08},
    {0x5A, 0xFF, 0x00},
    {0x5B, 0xFF, 0x00},
    {0x5C, 0xFF, 0x00},
    {0x5D, 0xFF, 0x57},
    {0x5E, 0xFF, 0x00},
    {0x5F, 0xFF, 0x00},
    {0x60, 0xFF, 0x00},
    {0x61, 0xFF, 0x00},
    {0x62, 0xFF, 0x00},
    {0x63, 0xFF, 0x00},
    {0x64, 0xFF, 0x00},
    {0x65, 0xFF, 0x00},
    {0x0F, 0x01, 0x00},
    {0xCD, 0x03, 0x03},
    {0,0,0}
};
RegSetEntry HDMITX_DeaultAudioInfo_Table[] = {

    /* ///////////////////////////////////////////////////
       // Config default audio infoframe
       /////////////////////////////////////////////////// */
    {0x0F, 0x01, 0x01},
    {0x68, 0xFF, 0x00},
    {0x69, 0xFF, 0x00},
    {0x6A, 0xFF, 0x00},
    {0x6B, 0xFF, 0x00},
    {0x6C, 0xFF, 0x00},
    {0x6D, 0xFF, 0x71},
    {0x0F, 0x01, 0x00},
    {0xCE, 0x03, 0x03},

    {0,0,0}
};

RegSetEntry HDMITX_Aud_CHStatus_LPCM_20bit_48Khz[] =
{
    {0x0F, 0x01, 0x01},
    {0x33, 0xFF, 0x00},
    {0x34, 0xFF, 0x18},
    {0x35, 0xFF, 0x00},
    {0x91, 0xFF, 0x00},
    {0x92, 0xFF, 0x00},
    {0x93, 0xFF, 0x01},
    {0x94, 0xFF, 0x00},
    {0x98, 0xFF, 0x02},
    {0x99, 0xFF, 0xDA},
    {0x0F, 0x01, 0x00},
    {0,0,0}/*end of table*/
} ;

RegSetEntry HDMITX_AUD_SPDIF_2ch_24bit[] =
{
    {0x0F, 0x11, 0x00},
    {0x04, 0x14, 0x04},
    {0xE0, 0xFF, 0xD1},
    {0xE1, 0xFF, 0x01},
    {0xE2, 0xFF, 0xE4},
    {0xE3, 0xFF, 0x10},
    {0xE4, 0xFF, 0x00},
    {0xE5, 0xFF, 0x00},
    {0x04, 0x14, 0x00},
    {0,0,0}/*end of table*/
} ;

RegSetEntry HDMITX_AUD_I2S_2ch_24bit[] =
{
    {0x0F, 0x11, 0x00},
    {0x04, 0x14, 0x04},
    {0xE0, 0xFF, 0xC1},
    {0xE1, 0xFF, 0x01},
    {0xE2, 0xFF, 0xE4},
    {0xE3, 0xFF, 0x00},
    {0xE4, 0xFF, 0x00},
    {0xE5, 0xFF, 0x00},
    {0x04, 0x14, 0x00},
    {0,0,0}/*end of table*/
} ;

RegSetEntry HDMITX_DefaultAudio_Table[] = {

    /* //////////////////////////////////////////////////
       // Config default audio output format.
       /////////////////////////////////////////////////// */
    {0x0F, 0x21, 0x00},
    {0x04, 0x14, 0x04},
    {0xE0, 0xFF, 0xC1},
    {0xE1, 0xFF, 0x01},
    {0xE2, 0xFF, 0xE4},
    {0xE3, 0xFF, 0x00},
    {0xE4, 0xFF, 0x00},
    {0xE5, 0xFF, 0x00},
    {0x0F, 0x01, 0x01},
    {0x33, 0xFF, 0x00},
    {0x34, 0xFF, 0x18},
    {0x35, 0xFF, 0x00},
    {0x91, 0xFF, 0x00},
    {0x92, 0xFF, 0x00},
    {0x93, 0xFF, 0x01},
    {0x94, 0xFF, 0x00},
    {0x98, 0xFF, 0x02},
    {0x99, 0xFF, 0xDB},
    {0x0F, 0x01, 0x00},
    {0x04, 0x14, 0x00},

    {0x00, 0x00, 0x00} /* End of Table. */
} ;

RegSetEntry HDMITX_PwrDown_Table[] = {
     /* Enable GRCLK */
     {0x0F, 0x40, 0x00},
     /* PLL Reset */
     {0x61, 0x10, 0x10},   /* DRV_RST */
     {0x62, 0x08, 0x00},   /* XP_RESETB */
     {0x64, 0x04, 0x00},   /* IP_RESETB */
     {0x01, 0x00, 0x00},   /* idle(100); */

     /* PLL PwrDn */
     {0x61, 0x20, 0x20},   /* PwrDn DRV */
     {0x62, 0x44, 0x44},   /* PwrDn XPLL */
     {0x64, 0x40, 0x40},   /* PwrDn IPLL */

     /* HDMITX PwrDn */
     {0x05, 0x01, 0x01},   /* PwrDn PCLK */
     {0x0F, 0x78, 0x78},   /* PwrDn GRCLK */
     {0x00, 0x00, 0x00}    /* End of Table. */
};

RegSetEntry HDMITX_PwrOn_Table[] = {
    {0x0F, 0x78, 0x38},   /* PwrOn GRCLK */
    {0x05, 0x01, 0x00},   /* PwrOn PCLK */

    /* PLL PwrOn */
    {0x61, 0x20, 0x00},   /* PwrOn DRV */
    {0x62, 0x44, 0x00},   /* PwrOn XPLL */
    {0x64, 0x40, 0x00},   /* PwrOn IPLL */

    /* PLL Reset OFF */
    {0x61, 0x10, 0x00},   /* DRV_RST */
    {0x62, 0x08, 0x08},   /* XP_RESETB */
    {0x64, 0x04, 0x04},   /* IP_RESETB */
    {0x0F, 0x78, 0x08},   /* PwrOn IACLK */
    {0x00, 0x00, 0x00}    /* End of Table. */
};

void ast_hdmi_init(struct drm_device *dev)
{

    hdmitx_LoadRegSetting(dev, HDMITX_Init_Table);
    hdmitx_LoadRegSetting(dev, HDMITX_DefaultVideo_Table);
    hdmitx_LoadRegSetting(dev, HDMITX_SetDVI_Table);  //set to DVI mode
    //hdmitx_LoadRegSetting(dev, HDMITX_SetHDMI_Table);
    //hdmitx_LoadRegSetting(dev, HDMITX_DefaultAVIInfo_Table);
    //hdmitx_LoadRegSetting(dev, HDMITX_DeaultAudioInfo_Table);
    //hdmitx_LoadRegSetting(dev, HDMITX_Aud_CHStatus_LPCM_20bit_48Khz);
    //hdmitx_LoadRegSetting(dev, HDMITX_AUD_SPDIF_2ch_24bit);

}
RegSetEntry HDMITX_DisableVideoOutput_Table[] = {
    {0x0F, 0x01, 0x00},
    {REG_TX_SW_RST, 0x00, B_HDMITX_VID_RST},
    {REG_TX_AFE_DRV_CTRL, 0xFF, (B_TX_AFE_DRV_RST + B_TX_AFE_DRV_PWD)},
    {0x62, 0x90, 0x00},
    {0x64, 0x89, 0x00},
    {0x00, 0x00, 0x00}
};

void ast_hdmi_disable(struct drm_device *dev)
{
    hdmitx_LoadRegSetting(dev, HDMITX_DisableVideoOutput_Table);
} /* DisableHDMITX */

RegSetEntry ClearDDCFIFO_HDMITX_Table[] = {
    {0x0F, 0x01, 0x00},							/*switch bank 0 */
    {REG_TX_DDC_MASTER_CTRL, 0xff, (B_TX_MASTERDDC+B_TX_MASTERHOST)},	/*hdmitx_ClearDDCFIFO */
    {REG_TX_DDC_CMD, 0xff, CMD_FIFO_CLR},
    {0x01, 0x00, 0x00},							/*delay*/
    {0x00, 0x00, 0x00}
};

RegSetEntry ReadEDID_HDMITX_Table[] = {
    {0x0F, 0x01, 0x00},	/*switch bank 0*/
    {REG_TX_DDC_MASTER_CTRL, 0xff, (B_TX_MASTERDDC+B_TX_MASTERHOST)},	/*hdmitx_ClearDDCFIFO*/
    {REG_TX_DDC_HEADER, 0xff, 0xa0},
    {REG_TX_DDC_REQCOUNT, 0xff, 0x20},					/*max. fifo: 0x20*/
    {REG_TX_DDC_EDIDSEG, 0xff, 0x00},
    {REG_TX_DDC_CMD, 0xff, CMD_EDID_READ},
    {0x00, 0x00, 0x00}
};

bool ast_hdmi_read_edid(struct drm_device *dev, u8 *pEDIDData)
{
	u8 i, j;
	u8 *pEDIDPtr = pEDIDData;
	u8 volatile jReg;
	bool Status = FALSE;

	{
		for (i=0; i<4; i++)
		{
			hdmitx_LoadRegSetting(dev, ClearDDCFIFO_HDMITX_Table);
			do {
				jReg = HDMITX_ReadI2C_Byte(dev, REG_TX_DDC_STATUS);
				if (jReg & B_TX_DDC_ERROR)			/*error*/
					return FALSE;
			} while (!(jReg & B_TX_DDC_DONE));

			HDMITX_WriteI2C_Byte(dev, REG_TX_DDC_REQOFF, i*0x20);
			hdmitx_LoadRegSetting(dev, ReadEDID_HDMITX_Table);
			do {
				jReg = HDMITX_ReadI2C_Byte(dev, REG_TX_DDC_STATUS);
				if (jReg & B_TX_DDC_ERROR)			/*error*/
					return FALSE;
			} while (!(jReg & B_TX_DDC_DONE));

			for (j=0; j<DDC_FIFO_MAXREQ; j++)		/*FIFO:0x20*/
			{
				jReg = HDMITX_ReadI2C_Byte(dev, REG_TX_DDC_READFIFO);
				*(u8 *)(pEDIDPtr++) = jReg;
			}
		}

		Status = TRUE;
	}

	return Status;

} /* ReadEDID_HDMITX */

RegSetEntry HDMITX_SetOutput_Table [] = {
    {0x0F, 0x01, 0x00},	/*switch bank 0*/
    /*HDMITX_DisableAudioOutput*/
    {REG_TX_SW_RST, (B_HDMITX_AUD_RST + B_TX_AREF_RST), (B_HDMITX_AUD_RST + B_TX_AREF_RST)},
    {0x0f, 0x10, 0x10},
    /*HDMITX_EnableHDCP(FALSE)*/
    /*TODO*/
    /*HDMITX_EnableVideoOutput*/
    {REG_TX_SW_RST, 0xff, (B_HDMITX_VID_RST+B_HDMITX_AUD_RST+B_TX_AREF_RST+B_TX_HDCP_RST_HDMITX)},
    {0x0F, 0x01, 0x01},	/*switch bank 1*/
    {REG_TX_AVIINFO_DB1, 0xff, 0x00},
    /*hdmitx_SetInputMode(RGB444)*/
    {0x0F, 0x01, 0x00},	/*switch bank 0*/
    {REG_TX_INPUT_MODE, (M_TX_INCOLMOD+B_TX_2X656CLK+B_TX_SYNCEMB+B_TX_INDDR+B_TX_PCLKDIV2), (B_TX_IN_RGB + 0x01)},
    /*hdmitx_SetCSCScale(RGB->RGB)*/
    {0x0F, 0x10, 0x10},
    {REG_TX_CSC_CTRL, (M_TX_CSC_SEL+B_TX_DNFREE_GO+B_TX_EN_DITHER+B_TX_EN_UDFILTER), B_HDMITX_CSC_BYPASS},
    /*set dvi mode*/
    {REG_TX_HDMI_MODE, 0xff, B_TX_DVI_MODE},
    /*hdmitx_SetupAFE*/
    {REG_TX_AFE_DRV_CTRL, 0xff, B_TX_AFE_DRV_RST},
    /*{0x62, 0x90, 0x80},*/		/*PCLK_HIGH */
    /*{0x64, 0x89, 0x80},*/
    /*{0x68, 0x10, 0x80},*/
    {0x62, 0x90, 0x10},			/*PCLK_LOW*/
    {0x64, 0x89, 0x09},
    {0x68, 0x10, 0x10},
    {REG_TX_SW_RST, (B_TX_REF_RST_HDMITX+B_HDMITX_VID_RST), 0x00},
    {REG_TX_AFE_DRV_CTRL, 0xff, 0x00},
    {0x01, 0x00, 0x00},			/* delay1 */
    {REG_TX_SW_RST, 0xff, (B_HDMITX_AUD_RST+B_TX_AREF_RST+B_TX_HDCP_RST_HDMITX)},
    {0x0F, 0x01, 0x00},			/* switch bank 0 */
    {REG_TX_AFE_DRV_CTRL, 0xff, 0x00}, 		/*hdmitx_FireAFE*/
    {REG_TX_AVI_INFOFRM_CTRL, 0xff, 0x00},	/*hdmitx_DISABLE_AVI_INFOFRM_PKT*/
    {REG_TX_3D_INFO_CTRL, 0xff, 0x00},		/*hdmitx_DISABLE_VSDB_PKT*/
    {REG_TX_GCP, B_TX_SETAVMUTE, 0x00},		/*setHDMITX_AVMute*/
    {REG_TX_PKT_GENERAL_CTRL, 0xff, (B_TX_ENABLE_PKT+B_TX_REPEAT_PKT)},
    {0x00, 0x00, 0x00}
};

void ast_hdmi_set_output(struct drm_device *dev)
{
	/*ITE66121_SetOutput*/
    hdmitx_LoadRegSetting(dev, HDMITX_SetOutput_Table);
} 
