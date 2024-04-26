#include <stdio.h> 
#include "os/dev/serial-line.h"
#include "contiki-conf.h"
#include "string.h"
#include "leds.h"
#include "sys/etimer.h"

PROCESS(proc1, "Test serial line");
AUTOSTART_PROCESSES(&proc1);


PROCESS_THREAD(proc1, ev, data)
{
    static struct etimer et;
    PROCESS_BEGIN();
    
    leds_on(LEDS_NUM_TO_MASK(LEDS_YELLOW));
    etimer_set(&et, CLOCK_SECOND);

    while(1){

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        etimer_reset(&et);

         leds_toggle(LEDS_NUM_TO_MASK(LEDS_YELLOW));
         leds_toggle(LEDS_NUM_TO_MASK(LEDS_RED));

        printf("coloro di giallo!\n");
    }

    //yellow led starts, at timeout they invert
    PROCESS_END();
} 
