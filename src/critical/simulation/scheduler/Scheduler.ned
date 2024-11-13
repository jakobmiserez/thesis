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
        
        bool demoMode = default(false);

        string appDistribution @enum(
            "random", 
            "video40", "video60", "video80", "video100", 
            "db40", "db60", "db80", "db100", 
            "prod40", "prod60", "prod80", "prod100"
        ) = default("random");
        
        @class(critical::Scheduler);
        @signal[flowConfigured](type=critical::FlowRequirements);
        @statistic[flow](title="Flow"; source=flowConfigured; record=captureFlow);
}