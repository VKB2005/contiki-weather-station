#include <stdlib.h>
#include "contiki.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "sys/log.h"

#define LOG_MODULE "SensorNode"
#define LOG_LEVEL LOG_LEVEL_INFO

#define UDP_PORT 1234

PROCESS(sensor_node_process, "Sensor Node");
AUTOSTART_PROCESSES(&sensor_node_process);

static struct simple_udp_connection udp_conn;

PROCESS_THREAD(sensor_node_process, ev, data)
{
  static struct etimer timer;
  static int temperature = 25;
  static int humidity = 60;
  static uip_ipaddr_t dest_ipaddr;

  PROCESS_BEGIN();

  // Register the UDP connection
  simple_udp_register(&udp_conn, UDP_PORT, NULL, UDP_PORT, NULL);

  LOG_INFO("Sensor node started\n");

  // Set the destination IP address (Base station's IP)
  uip_ip6addr(&dest_ipaddr, 0xfe80, 0, 0, 0, 0x0212, 0x7401, 1, 0x0101); // example LL address

  etimer_set(&timer, CLOCK_SECOND * 5);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    char msg[64];
    snprintf(msg, sizeof(msg), "Temp: %d, Hum: %d", temperature, humidity);
    LOG_INFO("Sending message: %s\n", msg);

    simple_udp_sendto(&udp_conn, msg, strlen(msg), &dest_ipaddr);

    // Simulate sensor value change
    
temperature = 20 + rand() % 10; // random temp between 20–29°C
humidity = 50 + rand() % 20;    // random humidity between 50–69%
    etimer_reset(&timer);
  }

  PROCESS_END();
}

