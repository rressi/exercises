function(add_protos)

    if(NOT TARGET protoc)
        message(ERROR "Cannot find required target: protoc")
    endif()
    if(NOT TARGET libprotobuf)
        message(ERROR "Cannot find required target: libprotobuf")
    endif()

    set(_options)
    set(_singleargs PROTOC_OUT_DIR TARGET)
    set(_multiargs PROTOS)
    cmake_parse_arguments(add_protos "${_options}" "${_singleargs}" "${_multiargs}" "${ARGN}")

    if(NOT add_protos_TARGET)
        message(ERROR "add_protos requires TARGET")
        return()
    endif()
    if(NOT add_protos_PROTOS)
        message(ERROR "add_protos requires PROTOS")
        return()
    endif()
    if(NOT add_protos_PROTOC_OUT_DIR)
        set(add_protos_PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    get_target_property(_source_list ${add_protos_TARGET} SOURCES)
    foreach(_file ${_source_list})
      if(_file MATCHES "proto$")
        list(APPEND add_protos_PROTOS ${_file})
      endif()
    endforeach()

    set(_generated_srcs_all)
    foreach(_proto ${add_protos_PROTOS})
        get_filename_component(_abs_file ${_proto} ABSOLUTE)
        get_filename_component(_abs_dir ${_abs_file} DIRECTORY)
        get_filename_component(_basename ${_proto} NAME_WE)
        file(RELATIVE_PATH _rel_dir ${CMAKE_CURRENT_SOURCE_DIR} ${_abs_dir})

        set(_possible_rel_dir ${_rel_dir}/)

        set(_generated_srcs)
        foreach(_ext .pb.h .pb.cc)
            list(APPEND _generated_srcs "${add_protos_PROTOC_OUT_DIR}/${_possible_rel_dir}${_basename}${_ext}")
        endforeach()
        list(APPEND _generated_srcs_all ${_generated_srcs})

        add_custom_command(
            OUTPUT ${_generated_srcs}
            COMMAND  protoc
            ARGS -I ${_abs_dir} --cpp_out ${add_protos_PROTOC_OUT_DIR} ${_abs_file}
            DEPENDS ${_abs_file} protoc
            COMMENT "Running C++ protocol buffer compiler on ${_proto}"
            VERBATIM)

    endforeach()
    set_source_files_properties(${_generated_srcs_all} PROPERTIES GENERATED TRUE)
        
    target_sources(${add_protos_TARGET} PRIVATE ${_generated_srcs_all})
    target_link_libraries(${add_protos_TARGET} PRIVATE libprotobuf)
    
endfunction(add_protos)
