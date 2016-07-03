
global tcc_run, resolve_sym, tcc_set_num_callers
tcc_run:
resolve_sym:
tcc_set_num_callers:
	ret

global dlopen, dlclose
dlopen:
dlclose:
	ret

global __divdi3, __moddi3, __udivdi3, __umoddi3

__divdi3:
__moddi3:
__udivdi3:
__umoddi3:
	ret
	
global gettimeofday
gettimeofday:
	ret

global getcwd
getcwd:
	ret
