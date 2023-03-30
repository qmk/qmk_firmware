/**
 * \defgroup pico_lwip pico_lwip
 * \brief Integration/wrapper libraries for <a href="https://savannah.nongnu.org/projects/lwip/lwIP">lwIP</a>
 * the documentation for which is <a href="https://www.nongnu.org/lwip/2_1_x/index.html">here</a>.
 *
 * The main \c \b pico_lwip library itself aggregates the lwIP RAW API: \c \b pico_lwip_core, \c \b pico_lwip_core4, \c \b pico_lwip_core6, \c \b pico_lwip_api, \c \b pico_lwip_netif, \c \b pico_lwip_sixlowpan and \c \b pico_lwip_ppp.
 *
 * If you wish to run in NO_SYS=1 mode, then you can link \c \b pico_lwip along with \ref pico_lwip_nosys.
 *
 * If you wish to run in NO_SYS=0 mode, then you can link \c \b pico_lwip with (for instance) \ref pico_lwip_freertos,
 * and also link in pico_lwip_api for the additional blocking/thread-safe APIs.
 *
 * Additionally you must link in \ref pico_lwip_arch unless you provide your own compiler bindings for lwIP.
 *
 * Additional individual pieces of lwIP functionality are available à la cart, by linking any of the libraries below.
 *
 * The following libraries are provided that contain exactly the equivalent lwIP functionality groups:
 *
 * * \c \b pico_lwip_core -
 * * \c \b pico_lwip_core4 -
 * * \c \b pico_lwip_core6 -
 * * \c \b pico_lwip_netif -
 * * \c \b pico_lwip_sixlowpan -
 * * \c \b pico_lwip_ppp -
 * * \c \b pico_lwip_api -
 *
 * The following libraries are provided that contain exactly the equivalent lwIP application support:
 *
 * * \c \b pico_lwip_snmp -
 * * \c \b pico_lwip_http -
 * * \c \b pico_lwip_makefsdata -
 * * \c \b pico_lwip_iperf -
 * * \c \b pico_lwip_smtp -
 * * \c \b pico_lwip_sntp -
 * * \c \b pico_lwip_mdns -
 * * \c \b pico_lwip_netbios -
 * * \c \b pico_lwip_tftp -
 * * \c \b pico_lwip_mbedtls -
 * * \c \b pico_lwip_mqtt -
 *
 */

/** \defgroup pico_lwip_arch pico_lwip_arch
 * \ingroup pico_lwip
 * \brief lwIP compiler adapters. This is not included by default in \c \b pico_lwip in case you wish to implement your own.
 */
