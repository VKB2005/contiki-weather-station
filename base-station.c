#include "contiki.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "sys/log.h"

#define LOG_MODULE "BaseStation"
#define LOG_LEVEL LOG_LEVEL_INFO

#define UDP_PORT 1234

PROCESS(base_station_process, "Base Station");
AUTOSTART_PROCESSES(&base_station_process);

static struct simple_udp_connection udp_conn;

static void
receiver(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
  LOG_INFO("Received from [");
  LOG_INFO_6ADDR(sender_addr);
  LOG_INFO_("]: %.*s\n", datalen, (char *)data);
}

PROCESS_THREAD(base_station_process, ev, data)
{
  PROCESS_BEGIN();

  // Register the UDP receiver
  simple_udp_register(&udp_conn, UDP_PORT, NULL, UDP_PORT, receiver);

  LOG_INFO("Base station started and listening on port %d\n", UDP_PORT);

  PROCESS_END();
}

