#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <idtLoader.h>

void _irq00Handler(void);
void _irq01Handler(void);
void _irq80Handler(void);

void _exception00Handler(void);
void _exception06Handler(void);

void _cli(void);
void _sti(void);
void _hlt(void);

void picMasterMask(uint8_t mask);
void picSlaveMask(uint8_t mask);

void saveInitialConditions(void* address);

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPTS_H_ */
