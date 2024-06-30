SRC += saesh.c

ifneq ($(strip $(NO_SECRETS)), yes)
    SRC += secrets.c
endif

DEFERRED_EXEC_ENABLE = yes
