#define ONE_MEG 0x10000

#ifdef DECLARE_RAM
extern uint8_t RAM[ONE_MEG];
#else
extern uint8_t* RAM;
#endif

extern void write86(uint32_t addr32, uint8_t value);
extern void writew86(uint32_t addr32, uint16_t value);
extern uint8_t read86(uint32_t addr32);
extern uint16_t readw86(uint32_t addr32);
