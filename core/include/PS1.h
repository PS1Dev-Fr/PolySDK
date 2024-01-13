


#define SCRATHPAD     0x1F800000
#define SCRATHPAD_END 0x1F8003FF

#define JOY_DATA 0x1F801040
#define JOY_STAT 0x1F801044
#define JOY_MODE 0x1F801048
#define JOY_CTRL 0x1F80104A
#define JOY_BAUD 0x1F80104E

#define SIO_DATA 0x1F801050
#define SIO_STAT 0x1F801054
#define SIO_MODE 0x1F801058
#define SIO_CTRL 0x1F80105A
#define SIO_MISC 0x1F80105C
#define SIO_BAUD 0x1F80105E

#define GP0_CMD_COLOR(cmd,r,g,b) \
		(r	<<  0  ) |	\
		(g	<<  8  ) |	\
		(b	<<  16 ) |	\
		(cmd  <<  24 )

#define GP0_VERTEX(x,y) \
		(x	<<  0  ) |	\
		(y	<<  16 )

#define GP0_TEXCOORD(x,y,arg) \
		(x	<<  0  ) |	\
		(y	<<  8  ) |	\
		(arg  <<  16 )

#define GP0_TEXPAGE(tpx,tpy,sm,tpc,dbit,dda,td,trx,try) \
		(tpx  <<  0  ) |	\
		(tpy  <<  4  ) |	\
		(sm   <<  5  ) |	\
		(tpc  <<  7  ) |	\
		(dbit <<  9  ) |	\
		(dda  <<  10 ) |	\
		(td   <<  11 ) |	\
		(trx  <<  12 ) |	\
		(try  <<  13 ) |	\
		(0xE1 <<  24 )


#define DMA_CHCR_SET(td,mas,ce,ts,dmaws,cpuws,dmast,smst,unk1,unk2) \
		(td	<<  0  ) |	\
		(mas   <<  1  ) |	\
		(ce	<<  8  ) |	\
		(ts	<<  9  ) |	\
		(dmaws <<  16 ) |	\
		(cpuws <<  20 ) |	\
		(dmast <<  24 ) |	\
		(smst  <<  28 ) |	\
		(unk1  <<  29 ) |	\
		(unk2  <<  30 )

#define SCRATCHPAD	0x1F800000

//Interrupt Control
#define I_STAT		0x1F801070
#define I_MASK		0x1F801074

//DMA Registers
#define D0_MADR		0x1F801080
#define D0_BCR		0x1F801084
#define D0_CHCR		0x1F801088

#define D1_MADR		0x1F801090
#define D1_BCR		0x1F801094
#define D1_CHCR		0x1F801098

#define D2_MADR		0x1F8010A0
#define D2_BCR		0x1F8010A4
#define D2_CHCR		0x1F8010A8

#define D3_MADR		0x1F8010B0
#define D3_BCR		0x1F8010B4
#define D3_CHCR		0x1F8010B8

#define D4_MADR		0x1F8010C0
#define D4_BCR		0x1F8010C4
#define D4_CHCR		0x1F8010C8

#define D5_MADR		0x1F8010D0
#define D5_BCR		0x1F8010D4
#define D5_CHCR		0x1F8010D8

#define D6_MADR		0x1F8010E0
#define D6_BCR		0x1F8010E4
#define D6_CHCR		0x1F8010E8

#define DPCR		0x1F8010F0
#define DICR		0x1F8010F4

#define TIMERV0		0x1F801100
#define TIMERM0		0x1F801104

#define TIMERV1		0x1F801110
#define TIMERM1		0x1F801114

#define TIMERV2		0x1F801120
#define TIMERM2		0x1F801124

//GPU Registers
#define GP0			0x1F801810
#define GP1			0x1F801814

// GPU COMMANDS
//M = Monochrome , T=Textured , S = Shaded
//O = Opaque ,N = semi-transparent
//R = Raw-texture , B = texture-Blending

#define GP0_TRIANGLE_MO			0x20
#define GP0_TRIANGLE_MN			0x22
#define GP0_TRIANGLE_TOB		0x24
#define GP0_TRIANGLE_TOR		0x25
#define GP0_TRIANGLE_TNB		0x26
#define GP0_TRIANGLE_TNR		0x27

#define GP0_TRIANGLE_STRIP_MO	0x28
#define GP0_TRIANGLE_STRIP_MN	0x2A
#define GP0_TRIANGLE_STRIP_TOB	0x2C
#define GP0_TRIANGLE_STRIP_TOR	0x2D
#define GP0_TRIANGLE_STRIP_TNB	0x2E
#define GP0_TRIANGLE_STRIP_TNR	0x2F

#define GP0_TRIANGLE_SO			0x30
#define GP0_TRIANGLE_SN			0x32
#define GP0_TRIANGLE_STOB		0x34
#define GP0_TRIANGLE_STNB		0x36

#define GP0_TRIANGLE_STRIP_SO	0x38
#define GP0_TRIANGLE_STRIP_MSN	0x3A
#define GP0_TRIANGLE_STRIP_STOB	0x3C
#define GP0_TRIANGLE_STRIP_STNB	0x3E

#define GP0_RECTANGLE_MO		0x60
#define GP0_RECTANGLE_MN		0x62
#define GP0_RECTANGLE_TOB		0x64
#define GP0_RECTANGLE_TOR		0x65
#define GP0_RECTANGLE_TNB		0x66
#define GP0_RECTANGLE_TNR		0x67

#define GP0_RECTANGLE_MO1		0x68
#define GP0_RECTANGLE_MN1		0x6A
#define GP0_RECTANGLE_TOB1		0x6C
#define GP0_RECTANGLE_TOR1		0x6D
#define GP0_RECTANGLE_TNB1		0x6E
#define GP0_RECTANGLE_TNR1		0x6F

#define GP0_RECTANGLE_MO8		0x70
#define GP0_RECTANGLE_MN8		0x72
#define GP0_RECTANGLE_TOB8		0x74
#define GP0_RECTANGLE_TOR8		0x75
#define GP0_RECTANGLE_TNB8		0x76
#define GP0_RECTANGLE_TNR8		0x77

#define GP0_RECTANGLE_MO16		0x78
#define GP0_RECTANGLE_MN16		0x7A
#define GP0_RECTANGLE_TOB16		0x7C
#define GP0_RECTANGLE_TOR16		0x7D
#define GP0_RECTANGLE_TNB16		0x7E
#define GP0_RECTANGLE_TNR16		0x7F

#define PS1_PSM4	0x00
#define PS1_PSM8	0x01
#define PS1_PSM16	0x02


#define D_CHCR_TO_RAM        0
#define D_CHCR_FROM_RAM      (1 << 0)
#define D_CHCR_FORWARD       0
#define D_CHCR_BACKWARD      (1 << 1)
#define D_CHCR_NO_CHOP       0
#define D_CHCR_CHOP          (1 << 8)
#define D_CHCR_SYNC_IMM      0
#define D_CHCR_SYNC_DEV      (1 << 9) /* transfer blocks, device-controlled */
#define D_CHCR_SYNC_LL       (2 << 9) /* transfer linked list, device-controlled */
#define D_CHCR_CHOP_DMA_SIZE(x) (((x) & 7) << 16) /* size of dma window in words */
#define D_CHCR_CHOP_CPU_SIZE(x) (((x) & 7) << 20) /* size of cpu window in clock cycles (33MHz?) */
#define D_CHCR_START         (1 << 24) /* "master" trigger for transfers */
#define D_CHCR_BUSY          (1 << 24) /* gets reset once transfer is complete */
#define D_CHCR_IMM_TRIG      (1 << 28) /* trigger for immediate transfers, combine with START */
#define D_CHCR_IMM_PAUSE     (1 << 29) /* pause for imm transfers? not verified, only makes sense with CHOP */

#define DICR_CH_ENABLE_OFFSET   16
#define DICR_MASTER_ENABLE	  (1 << 23)
#define DICR_CH_FLAG_OFFSET	 24

#define GPUREAD GP0
#define GPUSTAT GP1

#define GPUSTAT_CMD_READY	  (1 << 26)
#define GPUSTAT_DMA_READY	  (1 << 28)

#define GP0_COPY_CPU_TO_VRAM 0xA0

#define GP1_RESET_CMD_BUFFER   0x01
#define GP1_DISPLAY_AREA_START 0x05
#define GP1_HRANGE             0x06
#define GP1_VRANGE             0x07
#define GP1_DISPLAY_MODE       0x08


enum
{
	/** NTSC video mode, 60Hz */
	VMODE_NTSC, 
	/** PAL video mode, 50Hz */
	VMODE_PAL
};

/* If this flag is set, pixels drawn have MSB set */
#define MASK_SET		1	
/* If this flag is set, pixels aren't drawn over pixels with MSB set */
#define MASK_IGNORE		2

static inline void PS1_GP1(unsigned int command, unsigned int param)
{
	RW_REGISTER_U32(GP1) = (command << 0x18) | param;
}

static inline void PS1_GP0(unsigned int command, unsigned int param)
{
	RW_REGISTER_U32(GP0) = (command << 0x18) | param;
}

void PS1_Init(uint32_t width,uint32_t height);
/*
void gpu_ctrl(unsigned int command, unsigned int param)
{
	RW_REGISTER_U32(GP1) = 0x01000000;
	RW_REGISTER_U32(GP1) = (command << 0x18) | param;
}

void gpu_data_ctrl(unsigned int command, unsigned int param)
{
	RW_REGISTER_U32(GP1) = 0x01000000;
	RW_REGISTER_U32(GP0) = (command << 0x18) | param;
}


#define IO_
#define IO_




DMA Registers


Timers (aka Root counters)

  1F801100h 2    Timer 0 Current Counter Value (R/W)  ;\
  1F801104h 2    Timer 0 Counter Mode          (R/W)  ; Dotclock
  1F801108h 2    Timer 0 Counter Target Value  (R/W)  ;/
  1F801110h 2    Timer 1 Current Counter Value (R/W)  ;\
  1F801114h 2    Timer 1 Counter Mode          (R/W)  ; Horizontal Retrace
  1F801118h 2    Timer 1 Counter Target Value  (R/W)  ;/
  1F801120h 2    Timer 2 Current Counter Value (R/W)  ;\
  1F801124h 2    Timer 2 Counter Mode          (R/W)  ; 1/8 system clock
  1F801128h 2    Timer 2 Counter Target Value  (R/W)  ;/

CDROM Registers (Address.Read/Write.Index)

  1F801800h.x.x   1   CD Index/Status Register (Bit0-1 R/W, Bit2-7 Read Only)
  1F801801h.R.x   1   CD Response Fifo (R) (usually with Index1)
  1F801802h.R.x   1/2 CD Data Fifo - 8bit/16bit (R) (usually with Index0..1)
  1F801803h.R.0   1   CD Interrupt Enable Register (R)
  1F801803h.R.1   1   CD Interrupt Flag Register (R/W)
  1F801803h.R.2   1   CD Interrupt Enable Register (R) (Mirror)
  1F801803h.R.3   1   CD Interrupt Flag Register (R/W) (Mirror)
  1F801801h.W.0   1   CD Command Register (W)
  1F801802h.W.0   1   CD Parameter Fifo (W)
  1F801803h.W.0   1   CD Request Register (W)
  1F801801h.W.1   1   Unknown/unused
  1F801802h.W.1   1   CD Interrupt Enable Register (W)
  1F801803h.W.1   1   CD Interrupt Flag Register (R/W)
  1F801801h.W.2   1   Unknown/unused
  1F801802h.W.2   1   CD Audio Volume for Left-CD-Out to Left-SPU-Input (W)
  1F801803h.W.2   1   CD Audio Volume for Left-CD-Out to Right-SPU-Input (W)
  1F801801h.W.3   1   CD Audio Volume for Right-CD-Out to Right-SPU-Input (W)
  1F801802h.W.3   1   CD Audio Volume for Right-CD-Out to Left-SPU-Input (W)
  1F801803h.W.3   1   CD Audio Volume Apply Changes (by writing bit5=1)

GPU Registers

  1F801810h.Write 4   GP0 Send GP0 Commands/Packets (Rendering and VRAM Access)
  1F801814h.Write 4   GP1 Send GP1 Commands (Display Control)
  1F801810h.Read  4   GPUREAD Read responses to GP0(C0h) and GP1(10h) commands
  1F801814h.Read  4   GPUSTAT Read GPU Status Register

MDEC Registers

  1F801820h.Write 4   MDEC Command/Parameter Register (W)
  1F801820h.Read  4   MDEC Data/Response Register (R)
  1F801824h.Write 4   MDEC Control/Reset Register (W)
  1F801824h.Read  4   MDEC Status Register (R)

SPU Voice 0..23 Registers

  1F801C00h+N*10h 4   Voice 0..23 Volume Left/Right
  1F801C04h+N*10h 2   Voice 0..23 ADPCM Sample Rate
  1F801C06h+N*10h 2   Voice 0..23 ADPCM Start Address
  1F801C08h+N*10h 4   Voice 0..23 ADSR Attack/Decay/Sustain/Release
  1F801C0Ch+N*10h 2   Voice 0..23 ADSR Current Volume
  1F801C0Eh+N*10h 2   Voice 0..23 ADPCM Repeat Address

SPU Control Registers

  1F801D80h 4  Main Volume Left/Right
  1F801D84h 4  Reverb Output Volume Left/Right
  1F801D88h 4  Voice 0..23 Key ON (Start Attack/Decay/Sustain) (W)
  1F801D8Ch 4  Voice 0..23 Key OFF (Start Release) (W)
  1F801D90h 4  Voice 0..23 Channel FM (pitch lfo) mode (R/W)
  1F801D94h 4  Voice 0..23 Channel Noise mode (R/W)
  1F801D98h 4  Voice 0..23 Channel Reverb mode (R/W)
  1F801D9Ch 4  Voice 0..23 Channel ON/OFF (status) (R)
  1F801DA0h 2  Unknown? (R) or (W)
  1F801DA2h 2  Sound RAM Reverb Work Area Start Address
  1F801DA4h 2  Sound RAM IRQ Address
  1F801DA6h 2  Sound RAM Data Transfer Address
  1F801DA8h 2  Sound RAM Data Transfer Fifo
  1F801DAAh 2  SPU Control Register (SPUCNT)
  1F801DACh 2  Sound RAM Data Transfer Control
  1F801DAEh 2  SPU Status Register (SPUSTAT) (R)
  1F801DB0h 4  CD Volume Left/Right
  1F801DB4h 4  Extern Volume Left/Right
  1F801DB8h 4  Current Main Volume Left/Right
  1F801DBCh 4  Unknown? (R/W)

SPU Reverb Configuration Area

  1F801DC0h 2  dAPF1  Reverb APF Offset 1
  1F801DC2h 2  dAPF2  Reverb APF Offset 2
  1F801DC4h 2  vIIR   Reverb Reflection Volume 1
  1F801DC6h 2  vCOMB1 Reverb Comb Volume 1
  1F801DC8h 2  vCOMB2 Reverb Comb Volume 2
  1F801DCAh 2  vCOMB3 Reverb Comb Volume 3
  1F801DCCh 2  vCOMB4 Reverb Comb Volume 4
  1F801DCEh 2  vWALL  Reverb Reflection Volume 2
  1F801DD0h 2  vAPF1  Reverb APF Volume 1
  1F801DD2h 2  vAPF2  Reverb APF Volume 2
  1F801DD4h 4  mSAME  Reverb Same Side Reflection Address 1 Left/Right
  1F801DD8h 4  mCOMB1 Reverb Comb Address 1 Left/Right
  1F801DDCh 4  mCOMB2 Reverb Comb Address 2 Left/Right
  1F801DE0h 4  dSAME  Reverb Same Side Reflection Address 2 Left/Right
  1F801DE4h 4  mDIFF  Reverb Different Side Reflection Address 1 Left/Right
  1F801DE8h 4  mCOMB3 Reverb Comb Address 3 Left/Right
  1F801DECh 4  mCOMB4 Reverb Comb Address 4 Left/Right
  1F801DF0h 4  dDIFF  Reverb Different Side Reflection Address 2 Left/Right
  1F801DF4h 4  mAPF1  Reverb APF Address 1 Left/Right
  1F801DF8h 4  mAPF2  Reverb APF Address 2 Left/Right
  1F801DFCh 4  vIN    Reverb Input Volume Left/Right

SPU Internal Registers

  1F801E00h+N*04h  4 Voice 0..23 Current Volume Left/Right
  1F801E60h      20h Unknown? (R/W)
  1F801E80h     180h Unknown? (Read: FFh-filled) (Unused or Write only?)



*/