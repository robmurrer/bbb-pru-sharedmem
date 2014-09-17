/* sharedmem.p 
    
    A simple example using the shared memory between the PRU and main CPU on Beaglebone Black
    Polls sharedmem[0] for the value of 0 and then writes 1 to that location and then exits.
    Rob Murrer - 2014-09-17
*/

.origin 0
.entrypoint START

#include "sharedmem.hp"

START:

    /* Enable OCP master port*/
    lbco    r0, CONST_PRUCFG, 4, 4
    clr     r0, r0, 4         /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port*/
    sbco    r0, CONST_PRUCFG, 4, 4



/* wait until sharedmem[0] == 0*/
WAIT0:
    mov     r3, 0x12000
    lbbo    r4, r3, 0, 4
    qbne    WAIT0, r4, 0

/* set sharedmem[0] = 1 */
    mov     r4, 1
    sbbo    r4, r3, 0, 4

EXIT:
    /* signal c program done */
    mov     r31.b0, PRU1_ARM_INTERRUPT+16

    halt 
