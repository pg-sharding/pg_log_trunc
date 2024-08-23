/* -------------------------------------------------------------------------
 *
 * pg_log_trunc.c
 *
 * Copyright (c) 2024, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *		contrib/pg_log_trunc/pg_log_trunc.c
 *
 * -------------------------------------------------------------------------
 */
#include "postgres.h"

#include <limits.h>

#include "libpq/auth.h"
#include "port.h"
#include "utils/guc.h"
#include "utils/timestamp.h"

PG_MODULE_MAGIC;

/* GUC Variables */
static int	pg_log_trunc_len = 0;

/* Original Hook */
static emit_log_hook_type original_emit_log_hook = NULL;


/* Log hook */
static void
pg_log_trunc_emit_log_hook(ErrorData *edata)
{
	/* disabled */
	if (pg_log_trunc_len == 0) {
		return;
	}

	if (edata->internalquery && strlen(edata->internalquery) > pg_log_trunc_len)
		edata->internalquery[pg_log_trunc_len] = '\0';
	
	if (edata->message && strlen(edata->message) > pg_log_trunc_len)
		edata->message[pg_log_trunc_len] = '\0';

    if (original_emit_log_hook) {
        original_emit_log_hook(edata);
    }
}

/*
 * Module Load Callback
 */
void
_PG_init(void)
{
	/* Define custom GUC variables */
	DefineCustomIntVariable("pg_log_trunc.field_max_lenght",
							"Max field lenght in chars",
							NULL,
							&pg_log_trunc_len,
							0,
							0, INT_MAX,
							PGC_USERSET,
							GUC_UNIT_MEMORY,
							NULL,
							NULL,
							NULL);

	MarkGUCPrefixReserved("pg_log_trunc");

	/* Install Hooks */
	original_emit_log_hook = emit_log_hook;
	emit_log_hook = pg_log_trunc_emit_log_hook;
}