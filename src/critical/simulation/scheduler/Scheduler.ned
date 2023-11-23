package critical.simulation.scheduler;

simple Scheduler {
  
    parameters:
        double startTime @unit(s) = default(10s); 
        double duration @unit(s) = default(0s);
        int maxScheduledFlows = default(-1);

        double interval @unit(s) = default(0.5s);
        int flowsPerInterval = default(5);

        bool noTraffic = default(false);
        double noTrafficStop @unit(s) = default(0s);

        int packetBurst = default(-1);
        
        @class(critical::Scheduler);
        @signal[flowConfigured](type=critical::FlowRequirements);
        @statistic[flow](title="Flow"; source=flowConfigured; record=captureFlow);
}