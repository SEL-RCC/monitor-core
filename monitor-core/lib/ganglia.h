#ifndef GANGLIA_H
#define GANGLIA_H 1

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64
#endif

#define GANGLIA_DEFAULT_MCAST_CHANNEL "239.2.11.71"
#define GANGLIA_DEFAULT_MCAST_PORT    8649
#define GANGLIA_DEFAULT_XML_PORT      8649

#ifndef SYNAPSE_FAILURE
#define SYNAPSE_FAILURE -1
#endif
#ifndef SYNAPSE_SUCCESS
#define SYNAPSE_SUCCESS 0
#endif

/* 
 * Max multicast message: 1500 bytes (Ethernet max frame size)
 * minus 20 bytes for IPv4 header, minus 8 bytes for UDP header.
 */
#ifndef MAX_MCAST_MSG
#define MAX_MCAST_MSG 1472
#endif

/* For C++ */
#ifdef __cplusplus
#define BEGIN_C_DECLS extern "C" {
#define END_C_DECLS }
#else
#define BEGIN_C_DECLS
#define END_C_DECLS
#endif


typedef struct apr_pool_t *         Ganglia_pool;
typedef struct cfg_t *              Ganglia_gmond_config;
typedef struct apr_array_header_t * Ganglia_udp_send_channels;


extern int gexec_errno;

#define GEXEC_TIMEOUT 60

typedef struct
   {
      char ip[16];
      char name[MAXHOSTNAMELEN];
      char domain[MAXHOSTNAMELEN];
      double load_one;
      double load_five;
      double load_fifteen;
      double cpu_user;
      double cpu_nice;
      double cpu_system;
      double cpu_idle;
      unsigned int proc_run;
      unsigned int proc_total;
      unsigned int cpu_num;
      unsigned long last_reported;
      int gexec_on;
      int name_resolved;
   }
gexec_host_t;

typedef struct
   {
      char name[256];
      unsigned long localtime;
      unsigned int num_hosts;
      void *hosts;
      unsigned int num_gexec_hosts;
      void *gexec_hosts;
      unsigned int num_dead_hosts;
      void *dead_hosts;

      /* Used internally */
      int malloc_error;
      gexec_host_t *host;
      int host_up;
      int start;
	}
gexec_cluster_t;

BEGIN_C_DECLS
int gexec_cluster_free ( gexec_cluster_t *cluster );
int gexec_cluster (gexec_cluster_t *cluster, char *ip, unsigned short port);
END_C_DECLS

#endif
