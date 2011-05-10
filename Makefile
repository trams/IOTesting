include Makefile.inc 

EXAM_INC_DIR = -I$(COMPLEMENT_ROOT)/include -I$(STLPORT_INC)
EXAM_LIB_DIR = -L$(COMPLEMENT_ROOT)/lib/exam/obj/gcc/so -L$(COMPLEMENT_ROOT)/lib/mt/obj/gcc/so -L$(COMPLEMENT_ROOT)/lib/misc/obj/gcc/so -Wl,-rpath=$(COMPLEMENT_ROOT)/lib/exam/obj/gcc/so -Wl,-rpath=$(COMPLEMENT_ROOT)/lib/mt/obj/gcc/so -Wl,-rpath=$(COMPLEMENT_ROOT)/lib/misc/obj/gcc/so -Wl,-rpath=$(STLPORT_LIB)

EXAM_LIBS = -lexam -lxmt -lmisc

all: exam_perf

exam_perf:
	g++ -O2 write_perf.cc perf_suite.cc $(EXAM_INC_DIR) $(EXAM_LIB_DIR) $(EXAM_LIBS) -pthread -o perf -std=gnu++0x
