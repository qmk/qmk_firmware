#ifndef TMK_CORE_PROTOCOL_NRF_SDK15_CLI_H_
#define TMK_CORE_PROTOCOL_NRF_SDK15_CLI_H_

void cli_init();
void cli_exec();

typedef struct {
    void (*func)(void*);
    void* data;
} cli_app_t;

void set_cli_app(cli_app_t * const p_cli_app);

#endif /* TMK_CORE_PROTOCOL_NRF_SDK15_CLI_H_ */
