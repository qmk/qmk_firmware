#define _PLUG_CONCAT(X,Y) X ## Y
#define PLUG_CONCAT(X,Y) _PLUG_CONCAT(X,Y)

#ifdef  PLUG1
    #define PLUG1S INCLUDEFILE(PLUG1)
    #include PLUG1S
    #define PLUG1_process_record_user if( ! PLUG_CONCAT(PLUG1,_process_record_user)(keycode,record) ) return false;
    #define PLUG1_matrix_init_user PLUG_CONCAT(PLUG1,_matrix_init_user)()
    #define PLUG1_matrix_scan_user PLUG_CONCAT(PLUG1,_matrix_scan_user)()
#else
    #define PLUG1_process_record_user
    #define PLUG1_matrix_init_user
    #define PLUG1_matrix_scan_user
#endif

#ifdef  PLUG2
    #define PLUG2S INCLUDEFILE(PLUG2)
    #include PLUG2S
    #define PLUG2_process_record_user if( ! PLUG_CONCAT(PLUG2,_process_record_user)(keycode,record) ) return false;
    #define PLUG2_matrix_init_user PLUG_CONCAT(PLUG2,_matrix_init_user)()
    #define PLUG2_matrix_scan_user PLUG_CONCAT(PLUG2,_matrix_scan_user)()
#else
    #define PLUG2_process_record_user
    #define PLUG2_matrix_init_user
    #define PLUG2_matrix_scan_user
#endif

#ifdef  PLUG3
    #define PLUG3S INCLUDEFILE(PLUG3)
    #include PLUG3S
    #define PLUG3_process_record_user if( ! PLUG_CONCAT(PLUG3,_process_record_user)(keycode,record) ) return false;
    #define PLUG3_matrix_init_user PLUG_CONCAT(PLUG3,_matrix_init_user)()
    #define PLUG3_matrix_scan_user PLUG_CONCAT(PLUG3,_matrix_scan_user)()
#else
    #define PLUG3_process_record_user
    #define PLUG3_matrix_init_user
    #define PLUG3_matrix_scan_user
#endif

#ifdef  PLUG4
    #define PLUG4S INCLUDEFILE(PLUG4)
    #include PLUG4S
    #define PLUG4_process_record_user if( ! PLUG_CONCAT(PLUG4,_process_record_user)(keycode,record) ) return false;
    #define PLUG4_matrix_init_user PLUG_CONCAT(PLUG4,_matrix_init_user)()
    #define PLUG4_matrix_scan_user PLUG_CONCAT(PLUG4,_matrix_scan_user)()
#else
    #define PLUG4_process_record_user
    #define PLUG4_matrix_init_user
    #define PLUG4_matrix_scan_user
#endif

#ifdef  PLUG5
    #define PLUG5S INCLUDEFILE(PLUG5)
    #include PLUG5S
    #define PLUG5_process_record_user if( ! PLUG_CONCAT(PLUG5,_process_record_user)(keycode,record) ) return false;
    #define PLUG5_matrix_init_user PLUG_CONCAT(PLUG5,_matrix_init_user)()
    #define PLUG5_matrix_scan_user PLUG_CONCAT(PLUG5,_matrix_scan_user)()
#else
    #define PLUG5_process_record_user
    #define PLUG5_matrix_init_user
    #define PLUG5_matrix_scan_user
#endif
