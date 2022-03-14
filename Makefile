CXX = g++
RM = rm -rf
# While checking -Wpedantic is useful, it is unsupported by abseil
# and gives a lot of compilation noise.
# For default builds just use CXXFLAGS without -Wpedantic
# CXXFLAGS = -Wall -Wextra -Wpedantic -O3 -std=c++17 -I./ -I./lib/build/include -fopenmp -DSPDLOG_FMT_EXTERNAL=true
# For debug builds, use -fsanitize=address for memory diagnostics
# CXXFLAGS = -Wall -Wextra -O3 -std=c++17 -fsanitize=address -I./ -I./lib/build/include -fopenmp -DSPDLOG_FMT_EXTERNAL=true
# For most builds use this
CXXFLAGS = -Wall -Wextra -O3 -std=c++17 -I./ -I./lib/build/include -fopenmp -DSPDLOG_FMT_EXTERNAL=true
LDFLAGS = -L./lib/build/lib \
					-lspdlog \
					-lfmt \
					-labsl \
					-lgmock -lgtest \
					-lwigxjpf \
					-lntcl-algorithms-full -lntcl-tensor-full -lntcl-data-full -lntcl-util-full \
					-lgfortran \
					-fopenmp

LIBSOURCEDIR = imsrg
LIBBUILDDIR = build/lib
EXECSOURCEDIR	= exec
EXECBUILDDIR = build
TESTSOURCEDIR = tests/imsrg
TESTHELPERSDIR = tests/helpers
TESTBUILDDIR = tests/build/imsrg
TESTHELPERSBUILDDIR = tests/build/helpers

LIBHEADERS = $(shell find $(LIBSOURCEDIR) -name '*.h')
LIBSOURCES = $(shell find $(LIBSOURCEDIR) -name '*.cc')
LIBOBJECTS = $(addprefix $(LIBBUILDDIR)/,$(LIBSOURCES:%.cc=%.o))
EXECSOURCES	= $(shell find $(EXECSOURCEDIR) -name '*.cc')
EXECBINARIES = $(addprefix $(EXECBUILDDIR)/,$(EXECSOURCES:%.cc=%.out))
TESTSOURCES = $(shell find $(TESTSOURCEDIR) -name '*.cc')
TESTBINARIES = $(addprefix $(TESTBUILDDIR)/,$(TESTSOURCES:%.cc=%.out))
TESTHELPERSHEADERS = $(shell find $(TESTHELPERSDIR) -name '*.h')

CATCHSRC = tests/catch.hpp
CATCHMAIN = tests/catch_main.cc
CATCHMAINOBJECT = tests/build/catch_main.o

all: $(EXECBINARIES)

test_fail: test_bin
	for test in $(TESTBINARIES); do echo $$test "[!shouldfail]"; $$test "[!shouldfail]"; done

test: test_bin
	for test in $(TESTBINARIES); do echo $$test; $$test; done

$(CATCHMAINOBJECT): $(CATCHMAIN) $(CATCHSRC) 
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_bin: $(TESTBINARIES)

.SECONDARY:

$(TESTBUILDDIR)/%.out: %.cc $(CATCHMAINOBJECT) $(LIBOBJECTS) $(LIBHEADERS) $(TESTHELPERSHEADERS)
	@mkdir -p $(@D)
	$(CXX) $< $(LIBOBJECTS) $(CATCHMAINOBJECT) $(CXXFLAGS) $(LDFLAGS) -o $@

$(EXECBUILDDIR)/%.out: %.cc $(LIBOBJECTS) $(LIBHEADERS)
	@mkdir -p $(@D)
	$(CXX) $< $(LIBOBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $@

$(LIBBUILDDIR)/%.o: %.cc $(LIBHEADERS)
	@mkdir -p $(@D)
	$(CXX) -c $< $(CXXFLAGS) -o $@

clean:
	$(RM) -rf $(LIBBUILDDIR)
	$(RM) -rf $(TESTBUILDDIR)
	$(RM) -rf $(TESTHELPERSBUILDDIR)

very_clean:
	$(RM) -rf $(LIBBUILDDIR)
	$(RM) -rf tests/build

