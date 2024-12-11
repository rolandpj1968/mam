/* alu ops */

typedef enum Aop Aop;
enum Aop {
	Anop = 0,

/* Arithmetic Binary*/

	Aiadd32,
	Aisub32,
	Airsub32,
	Aidiv32,
	Airem32,
	Aiudiv32,
	Aiurem32,
	Aimul32,

	Aiadd64,
	Aisub64,
	Airsub64,
	Aidiv64,
	Airem64,
	Aiudiv64,
	Aiurem64,
	Aimul64,
	
	Afadd32,
	Afsub32,
	Afrsub32,
	Afdiv32,
	Afrem32,
	Afudiv32,
	Afurem32,
	Afmul32,

	Afadd64,
	Afsub64,
	Afrsub64,
	Afdiv64,
	Afrem64,
	Afudiv64,
	Afurem64,
	Afmul64,
	
/* Arithmetic Unary */

	Aineg32,
	Aineg64,
	Afneg32,
	Afneg64,
	
/* Shift Binary */

	Aisar32,
	Aishr32,
	Aishl32,
	Airotr32,

	Aisar64,
	Aishr64,
	Aishl64,
	Airotr64,

/* Bits */

	Aiand32,
	Aior32,
	Aixor32,
	Ainot32,

	Aiand64,
	Aior64,
	Aixor64,
	Ainot64,

/* Comparisons */

	Aiceq32,
	Aicne32,
	Aiceq64,
	Aicne64,

	Aicsge32,
	Aicsgt32,
	Aicsle32,
	Aicslt32,
	Aicuge32,
	Aicugt32,
	Aicule32,
	Aicult32,

	Aicsge64,
	Aicsgt64,
	Aicsle64,
	Aicslt64,
	Aicuge64,
	Aicugt64,
	Aicule64,
	Aicult64,

	Afceq32,
	Afcge32,
	Afcgt32,
	Afcle32,
	Afclt32,
	Afcne32,
	Afco32,
	Afcuo32,

	Afceq64,
	Afcge64,
	Afcgt64,
	Afcle64,
	Afclt64,
	Afcne64,
	Afco64,
	Afcuo64,

/* Extensions and Truncations */

	Ai32exts8,
	Ai32extu8,
	Ai32exts16,
	Ai32extu16,
	Ai32exts32,
	Ai32extu32,

	Ai64exts8,
	Ai64extu8,
	Ai64exts16,
	Ai64extu16,
	Ai64exts32,
	Ai64extu32,

	Afext32,
	Aftrunc64,

	Af32tosi32,
	Af32toui32,
	Af32tosi64,
	Af32toui64,
	Af64tosi32,
	Af64toui32,
	Af64tosi64,
	Af64toui64,

	Ai32stof32,
	Ai32utof32,
	Ai64stof32,
	Ai64utof32,
	Ai32stof64,
	Ai32utof64,
	Ai64stof64,
	Ai64utof64,

/* Stack read */
	Astk0,
	Astk1,
	Astk2,
	Astk3,
	
/* Register read */
	Areg0,
	Areg1,
	Areg2,
	Areg3,
	
/* Register write popping */
	Aregp0,
	Aregp1,
	Aregp2,
	Aregp3,
	
/* Register write non-popping */
	Aregw0,
	Aregw1,
	Aregw2,
	Aregw3,

/* Remote unit TOS access */
	Atos0,
	Atos1,
	Atos2,
	Atos3,
	Atos4,
	Atos5,
	Atos6,
	Atos7,
	Atos8,
	Atos9,
	Atos10,
	Atos11,
	Atos12,
	Atos13,
	Atos14,
	Atos15,
	
	NAops,
};
