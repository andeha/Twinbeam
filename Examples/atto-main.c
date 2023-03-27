/*  atto-main.c | startup for minimal Kirkbridge-family kernel. */

import Twinbeam;

coro_t * interrupt;
coro_t * master;

int corout₋interrupt(coro_t * coro)
{
   /* initialization */
   coro_feedback(coro,1);
   while (1) {
     🔧𝑀𝑍(LATHINV) = 0b111; // Invert all three LEDs.
     coro_resume(master);
   }
   return 0;
}

int corout₋master(coro_t * coro)
{
   /* initialization */
   while (1) { wait; }
   return 0;
}

void Isr()
{
   switch (🔎IRQ()) {
   case Timer4: 🔧𝑀𝑍𝐷𝐴(IFS0CLR) = PIC32MZDA_IFS0_T4IF; coro_resume(interrupt); break;
   case Adc: 🔧𝑀𝑍𝐷𝐴(IFS1CLR) = PIC32MZDA_IFS1_ADCIF; coro_resume(interrupt); break; asm("iret");
   } /* see interrupt proximity timer in pic32mzda. */
}

void mips_general_exception() { print("general exception\n"); }

int main()
{
   PortRectifyAsOutputs(MZDA,H,RE0)
   🔧𝑀𝑍𝐷𝐴(TMR4) = 0; /* set current value. */
   🔧𝑀𝑍𝐷𝐴(PR4) = 125; /* set period. */
   interrupt = coro_await(corout₋interrupt);
   master = coro_await(corout₋master);
   coro_resume(master);
   return 0;
}

/* compile with 'ninja atto.bin'. */

