#include <tonc.h>

int main()
{
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	REG_DISPCNT = DCNT_MODE1 | DCNT_BG2;

	// Init BG 0 for text on screen entries.
	//tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
	// --- (1) Base TTE init for tilemaps ---
	//tte_init_se(
	//	0,                      // Background number (BG 0)
	//	BG_CBB(0) | BG_SBB(31),   // BG control (for REG_BGxCNT)
	//	0,                      // Tile offset (special cattr)
	//	CLR_YELLOW,             // Ink color
	//	14,                     // BitUnpack offset (on-pixel = 15)
	//	NULL,                   // Default font (sys8)
	//	NULL);                  // Default renderer (se_drawg_s)

	tte_init_ase(
		2,                      // BG number
		BG_CBB(0) | BG_SBB(28) | BG_AFF_32x32,  // BG control
		0,                      // Tile offset (special cattr)
		CLR_YELLOW,             // Ink color
		0xFE,                   // BUP offset (on-pixel = 255)
		NULL,                   // Default font (sys8)
		NULL);                  // Default renderer (ase_drawg_s)

	// --- (2) Init some colors ---
	//pal_bg_bank[1][15] = CLR_RED;
	//pal_bg_bank[2][15] = CLR_GREEN;
	//pal_bg_bank[3][15] = CLR_BLUE;
	//pal_bg_bank[4][15] = CLR_WHITE;
	//pal_bg_bank[5][15] = CLR_MAG;

	//pal_bg_bank[4][14] = CLR_GRAY;

	//tte_write("#{P:62,64}");
	//tte_write("#{cx:0x2000}ScriptKitties\n");

	//tte_write("#{P:70,80}");
	//tte_write("#{cx:0}ADVANCE");

	tte_write("#{P:62,64}");
	tte_write("This is some text?");


	// Rotate it
	AFF_SRC_EX asx = { 124 << 8, 84 << 8, 120, 80, 0x100, 0x100, 0 };
	bg_rotscale_ex(&REG_BG_AFFINE[2], &asx);

	while (1) {
		VBlankIntrWait();
		key_poll();

		asx.alpha += 0x111;
		bg_rotscale_ex(&REG_BG_AFFINE[2], &asx);
	}

	return 0;
}
