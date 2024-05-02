/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"

#include "random.h"

#include "weather_forecast.h" // emlearn generated model

#include "eml_net.h"


#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  float features[] = { 30, 90, 1060 };

  printf("%p\n", eml_net_activation_function_strs); // This is needed to avoid compiler error (warnings == errors)

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 10);

  random_init(0);

  while(1) {
     /*PROCESS_WAIT_EVENT();
     if(ev == serial_line_event_message) {
       printf("received line: %s\n", (char *)data);

       unsigned int tmp=0, hum=0, pre=0;
	
       sprintf(data, "%u %u %u", tmp, hum, pre);

       features[0]= (float) tmp;
       features[1] = (float) hum;
       features[2] = (float) pre;

       float outputs[5] = {1, 0, 0, 0, 0};

       eml_net_predict_proba(&weather_forecast, features, 3, outputs, 5);

       printf("%i, %i, %i, %i, %i\n",  (int) ((float) outputs[0]*100), (int) ((float) outputs[1]*100), (int) ((float)outputs[2]*100), (int)((float)outputs[3]*100), (int)((float)outputs[4]*100));

     }*/

    features[0]= (float) (random_rand() % 40);
    features[1] = (float) (random_rand() % 100);
    features[2] = (float) (random_rand() % 1300);


    printf("New sample\n");
     
    float outputs[5] = {0, 0, 0, 0, 0};

    eml_net_predict_proba(&weather_forecast, features, 3, outputs, 5);


    printf("%i, %i, %i, %i, %i\n",  (int) ((float) outputs[0]*100), (int) ((float) outputs[1]*100), (int) ((float)outputs[2]*100), (int)((float)outputs[3]*100), (int)((float)outputs[4]*100));


    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);


	  
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
