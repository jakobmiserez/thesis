package critical.simulation.lsaoptimizer;

simple LsaOptimizer {
    parameters:
        @class(critical::LsaOptimizer);
        double startTime @unit(s) = default(4.0s);
        bool enabled = default(false);
}
