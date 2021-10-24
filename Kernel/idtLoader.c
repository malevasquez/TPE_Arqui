#include <stdint.h>
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>

//defino struct con formato de un descriptor
//alineo los elementos de la estructura
#pragma pack(push)
#pragma pack(1)

typedef struct {
    unint16_t offset_l,selector;
    unint8_t cero, access;
    unint16_t offset_m;
    unint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)

//IDT estaba cargada en posicion 0x00
DESCR_INT *idt =  (DESCR_INT *) 0;

/*
recibe el numero de la interrupcion y el puntero
a la rutina de atencion de interrupcion
*/
void setup_IDT_entry(int index, unint64_t offset) {
    idt[index].offset_l = offset & 0xFFFF;
    idt[index].selector = 0x08;
    idt[index].cero = 0;
    idt[index].access = ACS_INT;
    idt[index].offset_m = (offset >> 16) & 0xFFFF;
    idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
    idt[index].other_cero = 0;
}

void load_idt() {
  _cli();

  //interrupciones habilitadas
  setup_IDT_entry (0x20, (uint64_t) &_irq00Handler);
  setup_IDT_entry(0x21, (uint64_t) & _irq01Handler);
  setup_IDT_entry(0x80, (uint64_t) & _irq80Handler);
  setup_IDT_entry(0x00, (uint64_t) & _exception00Handler);
  setup_IDT_entry(0x06, (uint64_t) & _exception06Handler);

  picMasterMask(0xFE);
  picSlaveMask(0xFF);

  _sti();
}
