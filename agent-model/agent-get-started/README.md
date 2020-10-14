# FPMAS Get Started example

The complete working example of the [Get Started wiki
page](https://github.com/FPMAS/FPMAS/wiki/Get-Started).

Two trivial types of Agents, `Agent1` and `Agent2`, are defined.
On each process, one instance of each agent is added to an AgentGroup and
executed for a given count of simulation steps.

# Build

```
mkdir build
cd build
cmake ..
cmake --build .
```

# Run

For example, on 2 processes :
```
mpiexec -n 2 ./fpmas-get-started
```
