/*
 * sharedmem.c
 *
 */

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// Driver header file
#include <pruss/prussdrv.h>
#include <pruss/pruss_intc_mapping.h>	 


#define PRU_NUM 	 1
#define PRU_PROG        "./sharedmem.bin"
#define PRU_ADDR 0x4A300000
#define SHAREDRAM_OFFSET 0x00010000


int main (void)
{
    int fd = open("/dev/mem",O_RDWR | O_SYNC);
    ulong* prusharedmemory = 
        (ulong*) mmap(NULL, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 
                PRU_ADDR+SHAREDRAM_OFFSET);
    prusharedmemory[0] = 1; 
    printf ("Sleeping for 1 second after setting memory...\n");
    sleep(1);

    unsigned int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
    
    printf("\nINFO: Starting %s example.\r\n", "sharedmem");
    /* Initialize the PRU */
    prussdrv_init ();		
    
    /* Open PRU Interrupt */
    ret = prussdrv_open(PRU_EVTOUT_1);
    if (ret)
    {
        printf("prussdrv_open open failed\n");
        return (ret);
    }
    
    /* Get the interrupt initialized */
    prussdrv_pruintc_init(&pruss_intc_initdata);
    


    /* Execute example on PRU */
    printf("\tINFO: Executing example.\r\n");
    prussdrv_exec_program (PRU_NUM, PRU_PROG); 


    printf("Enter in a zero to trigger PRU to quit.\n");
    while (1)
    {
        int a;
        scanf("%d", &a); 
        
        if (a == 0)
        {
            prusharedmemory[0] = a;
            break;
        }
    }
        
    printf("Waiting for PRU to write back to memory...\n");
    while (1)
    {
        if (prusharedmemory[0] == 1) break;
    }
    
    printf("PRU successfully wrote back to memory.\n");
        

    /* Wait until PRU0 has finished execution */
    printf("\tINFO: Waiting for HALT command.\r\n");
    prussdrv_pru_wait_event (PRU_EVTOUT_1);
    printf("\tINFO: PRU completed transfer.\r\n");
    prussdrv_pru_clear_event (PRU_EVTOUT_1, PRU1_ARM_INTERRUPT);

    
    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable(PRU_NUM); 
    prussdrv_exit ();


    return(0);
}
