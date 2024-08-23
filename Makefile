# contrib/pg_log_trunc/Makefile

MODULES = pg_log_trunc
PGFILEDESC = "pg_log_trunc - truncate error log fields to some len"

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/pg_log_trunc
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
