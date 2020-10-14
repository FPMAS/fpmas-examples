# FPMAS Agent Serialization example

The complete working example of the [Agent Serialization wiki
page](https://github.com/FPMAS/FPMAS/wiki/Agent-Serialization).

This example shows how JSON serialization rules can be easily defined for
`Agent1` in order to perform Agent migration across processes.

# Build

```
mkdir build
cd build
cmake ..
make
```

# Run

For example, on 2 processes, generating output of different processes to
separate files in the `out` directory :
```
mpiexec -n 2 --output-filename out ./fpmas-agent-serialization
```
