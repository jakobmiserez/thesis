#
# OMNeT++/OMNEST Makefile for thesis
#
# This file was generated with the command:
#  opp_makemake -f --deep -KINET_PROJ=/root/models/inet -DINET_IMPORT -I/root/omnetpp/include -I$(INET_PROJ)/src -L$(INET_PROJ)/src -lINET$(D)
#

# Name of target to be created (-o option)
TARGET = thesis$(D)$(EXE_SUFFIX)
TARGET_DIR = .

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = -I/root/omnetpp/include -I$(INET_PROJ)/src

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = $(LDFLAG_LIBPATH)$(INET_PROJ)/src  -lINET$(D)

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/critical/CriticalProtocol.o \
    $O/critical/common/handler/base/MessageHandlerBase.o \
    $O/critical/common/handler/distributor/PacketDistributor.o \
    $O/critical/common/handler/distributor/TimerDistributor.o \
    $O/critical/common/handler/multiplex/FlowMultiplexer.o \
    $O/critical/common/handler/stateless/StatelessMessageHandler.o \
    $O/critical/common/handler/top/TopLevelMessageHandler.o \
    $O/critical/common/packet/PacketCreatorBase.o \
    $O/critical/common/routing/RouterBase.o \
    $O/critical/common/util/Parameterizable.o \
    $O/critical/flows/FlowTable.o \
    $O/critical/parameters/ParameterReader.o \
    $O/critical/protocols/ls/LsRouter.o \
    $O/critical/protocols/ls/handler/LsEmbedConfirmHandler.o \
    $O/critical/protocols/ls/handler/LsEmbedFailHandler.o \
    $O/critical/protocols/ls/handler/LsEmbedHandler.o \
    $O/critical/protocols/ls/handler/LsHelloHandler.o \
    $O/critical/protocols/ls/handler/LsLsaHandler.o \
    $O/critical/protocols/ls/handler/LsQosLsaHandler.o \
    $O/critical/protocols/ls/lsa/LsaDatabase.o \
    $O/critical/protocols/ls/lsa/QosLsaDatabase.o \
    $O/critical/protocols/ls/minimal/MinimalLsRouter.o \
    $O/critical/protocols/ls/packets/PacketCreator.o \
    $O/critical/protocols/ls/path/PathTable.o \
    $O/critical/protocols/ls/topology/NetworkTopology.o \
    $O/critical/protocols/ls/topology/QueueLevelTopology.o \
    $O/critical/protocols/ls/topology/Topology.o \
    $O/critical/protocols/probing/ProbingRouter.o \
    $O/critical/protocols/probing/common/FreeFailureHandler.o \
    $O/critical/protocols/probing/common/FreeHandler.o \
    $O/critical/protocols/probing/common/QueueAllocationStrategy.o \
    $O/critical/protocols/probing/packets/PacketCreator.o \
    $O/critical/protocols/probing/variants/bf/BfConfirmHandler.o \
    $O/critical/protocols/probing/variants/bf/BfProbeHandler.o \
    $O/critical/protocols/probing/variants/bf/BfPruneHandler.o \
    $O/critical/protocols/probing/variants/df/DfConfirmHandler.o \
    $O/critical/protocols/probing/variants/df/DfProbeHandler.o \
    $O/critical/protocols/probing/variants/df/DfPruneHandler.o \
    $O/critical/queueing/classifier/QosClassifier.o \
    $O/critical/queueing/dnc/PredictablePort.o \
    $O/critical/queueing/dnc/PredictableQueue.o \
    $O/critical/queueing/dnc/SimplePredictablePort.o \
    $O/critical/queueing/dnc/budget/ChameleonAllocator.o \
    $O/critical/queueing/dnc/budget/CustomAllocator.o \
    $O/critical/queueing/dnc/consumption/ConsumptionChecker.o \
    $O/critical/queueing/dnc/consumption/HybridConsumptionChecker.o \
    $O/critical/queueing/dnc/curves/AffineArrivalCurve.o \
    $O/critical/queueing/dnc/curves/DncCurve.o \
    $O/critical/queueing/dnc/curves/RateLatencyServiceCurve.o \
    $O/critical/simulation/applications/CriticalAppGenerator.o \
    $O/critical/simulation/applications/CriticalUdpApp.o \
    $O/critical/simulation/applications/server/FlowServerApp.o \
    $O/critical/simulation/lsaoptimizer/LSAOptimizer.o \
    $O/critical/simulation/recorder/ConsumptionManager.o \
    $O/critical/simulation/recorder/ConsumptionRecorder.o \
    $O/critical/simulation/recorder/FlowRecorderData.o \
    $O/critical/simulation/recorder/FlowRequestRecorder.o \
    $O/critical/simulation/recorder/FlowRequestResponseManager.o \
    $O/critical/simulation/recorder/FlowRequirementsRecorder.o \
    $O/critical/simulation/recorder/FlowRerouteRecorder.o \
    $O/critical/simulation/recorder/FlowResponseRecorder.o \
    $O/critical/simulation/recorder/FlowSignalingRecorder.o \
    $O/critical/simulation/recorder/QueueManager.o \
    $O/critical/simulation/recorder/QueueRecorder.o \
    $O/critical/simulation/recorder/ProbeReservationRecorder.o \
    $O/critical/simulation/scheduler/Scheduler.o \
    $O/critical/common/packet/CriticalPacketBase_m.o \
    $O/critical/common/packet/OriginalSourceTag_m.o \
    $O/critical/protocols/ls/packets/LsPackets_m.o \
    $O/critical/protocols/probing/packets/ProbingPackets_m.o \
    $O/critical/queueing/classifier/QosQueueReq_m.o \
    $O/critical/simulation/applications/server/FlowRequests_m.o

# Message files
MSGFILES = \
    critical/common/packet/CriticalPacketBase.msg \
    critical/common/packet/OriginalSourceTag.msg \
    critical/protocols/ls/packets/LsPackets.msg \
    critical/protocols/probing/packets/ProbingPackets.msg \
    critical/queueing/classifier/QosQueueReq.msg \
    critical/simulation/applications/server/FlowRequests.msg

# SM files
SMFILES =

# Other makefile variables (-K)
INET_PROJ=/root/models/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = $(OPPMAIN_LIB) $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)
ifneq ($(TOOLCHAIN_NAME),clangc2)
LIBS += -Wl,-rpath,$(abspath $(INET_PROJ)/src)
endif

COPTS = $(CFLAGS) $(IMPORT_DEFINES) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# inserted from file 'makefrag':
#
# Use the new message compiler introduced in OMNeT++ 5.3
#
MSGC:=$(MSGC) --msg6

INCLUDE_PATH:=$(INCLUDE_PATH) -I.

CXXFLAGS:= -std=c++2a -O3

# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/% :: $O/%
	@mkdir -p $(TARGET_DIR)
	$(Q)$(LN) $< $@
ifeq ($(TOOLCHAIN_NAME),clangc2)
	$(Q)-$(LN) $(<:%.dll=%.lib) $(@:%.dll=%.lib)
endif

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET) $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc -MD -MP -MF $O/$(basename $<)_m.h.d $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning $(TARGET)
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET)
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET:%.dll=%.lib)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall:
	$(Q)$(MAKE) -s clean MODE=release
	$(Q)$(MAKE) -s clean MODE=debug
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

# include all dependencies
-include $(OBJS:%=%.d) $(MSGFILES:%.msg=$O/%_m.h.d)
