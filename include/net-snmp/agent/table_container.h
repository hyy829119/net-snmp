/*
 * table_container.h
 * $Id$
 */
#ifndef _TABLE_CONTAINER_HANDLER_H_
#define _TABLE_CONTAINER_HANDLER_H_

#ifdef __cplusplus
extern          "C" {
#endif

    /*
     * The table container helper is designed to simplify the task of
     * writing a table handler for the net-snmp agent when the data being
     * accessed is accessible via a netsnmp_container.
     * 
     * Functionally, it is a specialized version of the more
     * generic table helper but easies the burden of GETNEXT processing by
     * retrieving the appropriate row for each index through
     * function calls which should be supplied by the module that wishes
     * help.  The module the table_container helps should, afterwards,
     * never be called for the case of "MODE_GETNEXT" and only for the GET
     * and SET related modes instead.
     */
    
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table.h>
    
#define TABLE_CONTAINER_NAME "table_container"
    
#define TABLE_CONTAINER_KEY_NETSNMP_INDEX         1 /* default */
#define TABLE_CONTAINER_KEY_VARBIND_INDEX         2
#define TABLE_CONTAINER_KEY_VARBIND_RAW           3

    /*
     * register a container table
     */
    int            
    netsnmp_container_table_register(netsnmp_handler_registration *reginfo,
                                     netsnmp_table_registration_info
                                     *tabreq,
                                     netsnmp_container *container,
                                     char key_type);
    /*
     * get an injectable containe table handler
     */
    netsnmp_mib_handler *
    netsnmp_container_table_handler_get(netsnmp_table_registration_info *tabreq,
                                        netsnmp_container *container,
                                        char key_type);
    
    /** find the context data used by the table_container helper */
    NETSNMP_STATIC_INLINE void *
    netsnmp_container_table_extract_context(netsnmp_request_info *request) {
        return netsnmp_request_get_list_data(request, TABLE_CONTAINER_NAME);
    }

    void *
    netsnmp_container_table_find_next_row(netsnmp_request_info *request,
                                          netsnmp_table_request_info *tblreq,
                                          netsnmp_container *container,
                                          char key_type );
#ifdef __cplusplus
};
#endif

#endif                          /* _TABLE_CONTAINER_HANDLER_H_ */
