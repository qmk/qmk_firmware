if(${FNV_ENABLE})
    target_compile_definitions(qmk PUBLIC FNV_ENABLE)
    target_include_directories(qmk PUBLIC lib/fnv)
    target_sources(qmk PUBLIC
        lib/fnv/qmk_fnv_type_validation.c
        lib/fnv/hash_32a.c
        lib/fnv/hash_64a.c
    )
endif()