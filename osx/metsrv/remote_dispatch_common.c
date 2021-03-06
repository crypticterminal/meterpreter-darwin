#include "metsrv.h"


/**************************
 * Core dispatch routines *
 **************************/

LIST * extension_list = NULL;

// Dispatch table
Command customCommands[] = 
{
	COMMAND_REQ( "core_loadlib", request_core_loadlib ),
	COMMAND_TERMINATOR
};

/*
 * Registers custom command handlers
 */
VOID register_dispatch_routines()
{
	extension_list = list_create();

	command_register_all( customCommands );
}

/*
 * Deregisters previously registered custom commands and loaded extensions.
 */
VOID deregister_dispatch_routines( Remote * remote )
{
	while( TRUE )
	{
		EXTENSION * extension = list_pop( extension_list );
		if( !extension )
			break;

		extension->deinit( remote );

		free( extension );
	}

	command_deregister_all( customCommands );

	list_destroy( extension_list );
}
