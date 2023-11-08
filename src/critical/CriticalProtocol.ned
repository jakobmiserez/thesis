package critical;

simple CriticalProtocol {
    parameters:
        // Generic parameters
        double startDelay @unit(s)  = uniform(0.5s, 1.5s); 
        string interfaceTableModule;
        string routingTableModule;
        string networkProtocolModule = default(absPath("^.ipv6.ipv6"));

        // QoS routing protocol 
        string routingProtocol @enum("probing", "ls") = default("probing");
        
        // Protocol-specific parameters 
        string probingVariant @enum("bf", "df") = default("bf");
        string probingQueueHeuristic @enum("greedy", "honest", "random") = default("greedy");
        bool probingFastPrune = default(false);

        string lsAlgorithm @enum("larac", "mindelay") = default("larac");
        string lsUpdateStrategy @enum("timed", "consumption", "hybrid") = default("consumption");
        double lsConsumptionThresh = default(0.1);
        double lsUpdateInterval @unit(s) = default(0.025s); 

        // budgetAllocator
        string budgetAllocator @enum("chameleon", "custom") = default("chameleon");
        
        // Protocol resource allocation
        double protocolBwUsage = default(0.05); 
        int protocolBurstUsage @unit(B) = default(1000B);
        int protocolQueue = default(0);

        // stats parameters
        bool recordMemoryFootprint = default(false);
        
        @class("critical::CriticalProtocol");
        @display("i=block/network");

        @signal[queueStateSignal](type=critical::QueueRecorderData);
        @signal[consumptionSignal](type=critical::ConsumptionRecorderData);
        @signal[routeSignal](type=long);
        @statistic[consumption](title="consumption"; source=consumptionSignal; record=recordConsumption);
        @statistic[queueState](title="queueStates"; source=queueStateSignal; record=recordQueueState);
        @statistic[routingTimes](title="routingTimes"; source=routeSignal; record=vector);
    gates:
        input ipIn;
        output ipOut;
}
