# ---  root Makefile  -------------------------------------------------
#  Detects host OS and includes the matching per-platform makefile
# --------------------------------------------------------------------

ifeq ($(OS),Windows_NT)
    include Makefile.windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        include Makefile.linux
    else
        $(error Unsupported platform: $(UNAME_S))
    endif
endif

# ----- generic phony targets ----------------------------------------
.PHONY: help clean install-deps

help:
	@echo "Solar System Simulator – Build System"
	@echo "====================================="
	@echo "Targets:"
	@echo "  make            build"
	@echo "  make run        build & run"
	@echo "  make clean      remove objects & binary"
	@echo "  make install-deps   (Linux only) install system packages"
	@echo ""
	@echo "Active platform rules: $(MAKEFILE_LIST)"
