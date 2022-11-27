package critical.simulation.applications;

import inet.applications.contract.IApp;

simple CriticalUdpApp like IApp {
  parameters:
    @class(critical::CriticalUdpApp);
    
    string srcAddress;
    string destAddress;
    string flowServerAddress;
    int port;
    int destPort = default(port);
    double startTime @unit(s) = default(12s);
    
    // A value of zero denotes an infinite duration
    double duration @unit(s) = default(0s);

    int maxPacketsToSend = default(-1);

    // If this is enabled, the application will only send the packets for the flow 
    // request, but it will not send real traffic if the flow is established. 
    bool noTraffic = default(false);
    double noTrafficStop @unit(s) = default(0s);

    int delay;
    int bandwidth @unit(bps);
    int burst @unit(B);
    int label = default(1);
    int packetBurst = default(1);

    @signal[flowResponseSignal](type=critical::FlowResponseData);
    @signal[flowRequestSignal](type=critical::FlowRequestData);
    @signal[flowRerouteSignal](type=critical::FlowRerouteData);
    @statistic[flowResponse](title="flowResponse"; source=flowResponseSignal; record=recordFlowResponse);
    @statistic[flowRequest](title="flowRequest"; source=flowRequestSignal; record=recordFlowRequest);
    @statistic[flowReroute](title="flowReroute"; source=flowRerouteSignal; record=recordFlowReroute);

  gates:
    input socketIn @labels(UdpControlInfo/up);
    output socketOut @labels(UdpControlInfo/down); 
}