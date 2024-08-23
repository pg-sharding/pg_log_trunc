# Copyright (c) 2024, PostgreSQL Global Development Group

pg_log_trunc_sources = files(
  'pg_log_trunc.c',
)

if host_system == 'windows'
  pg_log_trunc_sources += rc_lib_gen.process(win32ver_rc, extra_args: [
    '--NAME', 'pg_log_trunc',
    '--FILEDESC', 'pg_log_trunc - truncate error log fields to some len',])
endif

pg_log_trunc = shared_module('pg_log_trunc',
  pg_log_trunc_sources,
  kwargs: contrib_mod_args,
)
contrib_targets += pg_log_trunc
