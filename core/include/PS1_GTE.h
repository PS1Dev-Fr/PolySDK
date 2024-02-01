
#define SET_GTE  ".set RTPS  ,0x0180001\n	" \
				 ".set RTPT  ,0x0280030\n	" \
				 ".set NCLIP ,0x1400006\n	" \
				 ".set AVSZ3 ,0x158002D\n	" \
				 ".set AVSZ4 ,0x168002E\n	" \
				 ".set MVMVA ,0x0400012\n	" \
				 ".set SQR   ,0x0A00428\n	" \
				 ".set OP	 ,0x0170000\n	" \
				 ".set CMD_SF ,1<<19\n	" \
				 ".set CMD_MMR ,0<<17\n	" \
				 ".set CMD_MML ,1<<17\n	" \
				 ".set CMD_MMC ,2<<17\n	" \
				 ".set CMD_MV0 ,0<<15\n	" \
				 ".set CMD_MV1 ,1<<15\n	" \
				 ".set CMD_MV2 ,2<<15\n	" \
				 ".set CMD_MVIR ,3<<15\n	" \
				 ".set CMD_TVTR ,0<<13\n	" \
				 ".set CMD_TVBK ,1<<13\n	" \
				 ".set CMD_TVFC ,2<<13\n	" \
				 ".set CMD_LM ,1<<10\n	" \
				 ".set VXY0 ,$0 \n	" \
				 ".set VZ0  ,$1 \n	" \
				 ".set VXY1 ,$2 \n	" \
				 ".set VZ1  ,$3 \n	" \
				 ".set VXY2 ,$4 \n	" \
				 ".set VZ2  ,$5 \n	" \
				 ".set RGB  ,$6 \n	" \
				 ".set OTZ  ,$7 \n	" \
				 ".set IR0  ,$8 \n	" \
				 ".set IR1  ,$9 \n	" \
				 ".set IR2  ,$10 \n	" \
				 ".set IR3  ,$11 \n	" \
				 ".set SXY0 ,$12 \n	" \
				 ".set SXY1 ,$13 \n	" \
				 ".set SXY2 ,$14 \n	" \
				 ".set SXYP ,$15 \n	" \
				 ".set SZ0  ,$16 \n	" \
				 ".set SZ1  ,$17 \n	" \
				 ".set SZ2  ,$18 \n	" \
				 ".set SZ3  ,$19 \n	" \
				 ".set RGB0 ,$20 \n	" \
				 ".set RGB1 ,$21 \n	" \
				 ".set RGB2 ,$22 \n	" \
				 ".set RES1 ,$23 \n	" \
				 ".set MAC0 ,$24 \n	" \
				 ".set MAC1 ,$25 \n	" \
				 ".set MAC2 ,$26 \n	" \
				 ".set MAC3 ,$27 \n	" \
				 ".set IRGB ,$28 \n	" \
				 ".set ORGB ,$29 \n	" \
				 ".set LZCS ,$30 \n	" \
				 ".set LZVR ,$31 \n	" \
				 ".set C0_STATUS   ,$12 \n	" \
				 ".set CTC2   ,0x48A00000 \n	" \
				 ".set R11R12 ,(0<<11) \n	" \
				 ".set R13R21 ,(1<<11) \n	" \
				 ".set R22R23 ,(2<<11) \n	" \
				 ".set R31R32 ,(3<<11) \n	" \
				 ".set R33	,(4<<11) \n	" \
				 ".set TRX	,(5<<11) \n	" \
				 ".set TRY	,(6<<11) \n	" \
				 ".set TRZ	,(7<<11) \n	" \
				 ".set L11L12 ,(8<<11) \n	" \
				 ".set L13L21 ,(9<<11) \n	" \
				 ".set L22L23 ,(10<<11) \n	" \
				 ".set L31L32 ,(11<<11) \n	" \
				 ".set L33	,(12<<11) \n	" \
				 ".set RBK	,(13<<11) \n	" \
				 ".set GBK	,(14<<11) \n	" \
				 ".set BBK	,(15<<11) \n	" \
				 ".set LR1LR2 ,(16<<11) \n	" \
				 ".set LR3LG1 ,(17<<11) \n	" \
				 ".set LG2LG3 ,(18<<11) \n	" \
				 ".set LB1LB2 ,(19<<11) \n	" \
				 ".set LB3	,(20<<11) \n	" \
				 ".set RFC	,(21<<11) \n	" \
				 ".set GFC	,(22<<11) \n	" \
				 ".set BFC	,(23<<11) \n	" \
				 ".set OFX	,(24<<11) \n	" \
				 ".set OFY	,(25<<11) \n	" \
				 ".set H	  ,(26<<11) \n	" \
				 ".set DQA	,(27<<11) \n	" \
				 ".set DQB	,(28<<11) \n	" \
				 ".set ZSF3   ,(29<<11) \n	" \
				 ".set ZSF4   ,(30<<11) \n	" \
				 ".set FLAG   ,(31<<11) \n	"
