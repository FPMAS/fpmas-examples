# FPMAS Agent Interactions Example

The complete working example of the [Agent Interactions wiki
page](https://github.com/FPMAS/FPMAS/wiki/Agent-Interactions).

This example illustrates how to build links between `Agents` and how each agent
can read and modify their neighbors' data.

# Build

The model can be compile and run using `HardSyncMode` or `GhostMode`. To do so,
the `SYNC_MODE` parameter must be provided to CMake.

```
mkdir build
cd build
cmake -DSYNC_MODE=[HardSyncMode/GhostMode] ..
make
```

# Run
```
mpiexec -n 2 ./fpmas-agent-interactions
```

## Output

Example outputs and explanations are available in the corresponding [wiki
page](https://github.com/FPMAS/FPMAS/wiki/Agent-Interactions).
