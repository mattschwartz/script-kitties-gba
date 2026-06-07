## Charblocks
All tiles are stored in charblocks. Each charblock is 16 kb long (512 s-tiles or 256 d-tiles). 96kb VRAM = 6 charblocks.

charblocks 0-3 are for backgrounds. 4-5 are for sprites

for backgrounds, tile-counting starts at a given CBB, indicated by: REG_BGxCNT{2-3}, eg REG_BG2CNT
for sprites, tile-indexing always starts at the lower sprite block (block 4, 0601:0000h) and numbering always follows s-tiles (20h offsets), even for d-tiles. backgrounds stick to their indicated tile-size: 20h offsets in 4bpp mode, 40h offsets for 8bpp mode.

> Sprites always have 32 bytes between tile indices, bg tile-indexing uses 32 or 64 byte offsets, depending on their set bitdepth.

## Screenblocks

Maps go into screenblocks, which take up the same memory space as charblocks. but screenblocks are 2048 bytes long, so 32 in total across the background charblocks (0600:0000 to 0600:FFFF)

Remember: tile*set* goes into charblocks. tile*maps* go into screenblocks.

## Sprites

tiles available for sprites are stored in object VRAM (OVRAM), 32 KB long, mapped in the last two charblocks of `tile_mem`:
- lower block 4 (0601:0000h) 
- higher block 5 (0601:4000h)

counting starts at the lower and is done in 32 byte offsets. eg sprite-tile #1 is at 0601:0020h no matter what the bit depth (s/d) is.

ex: find sprite-tile 123 in OVRAM: `tile_mem[4][123]` (4: lower block, 123: sprite-tile index)

| memory 0601:| 0000| 0020| 0040| 0060| 0080| 0100| ... |
|---|---|---|---|---|---|---|---|
| 4bpp tile| 0| 1| 2| 3| 4| 5|  
| 8bpp tile| 0|| 2|| 4|

Gotta load the sprite tiles in object VRAM and also update the OAM and also the sprite palette (0500:0200), specifically not the bg palette

changing the starting tile tid that a sprite uses, while the sprite is active and rendering, is standard practice for animations. 

## Palettes and tile colors

Sprites and backgrounds have separate palettes. The background palette goes first at 0500:0000h, immediately followed by the sprite palette (0500:0200h). Both palettes contain 256 entries of 15bit colors.

## Gotchas

> Another thing you need to know about available charblocks is that in one of the bitmap modes, the bitmaps extend into the lower sprite block. For that reason, you can only use the higher sprite block (containing tiles 512 to 1023) in this case. (modes 3-5). indexing still starts at the lower block!! (512-1023)

## Object Attribute Memory (OAM)

> the way you tell the GBA how to draw your sprites

i guess? use a double-buffer and copy to OAM during VBlank (you can't update OAM during VDraw)

# Tilemaps and such 

Video modes 0, 1, 2 are tiled modes. Can have up to 4 backgrounds that display tilemaps. size of maps can be between 128x128 and 1024x1024, configurable in control registers. 

Each tile is always 8x8
