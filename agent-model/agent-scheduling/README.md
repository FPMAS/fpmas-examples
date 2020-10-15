# FPMAS Agent Group Example

The complete working example of the [Agent Group wiki
page](https://github.com/FPMAS/FPMAS/wiki/Agent-Group).

This example illustrates
[AgentGroup](https://fpmas.github.io/FPMAS/classfpmas_1_1api_1_1model_1_1AgentGroup.html)
definition.

# Build

```
mkdir build
cd build
cmake ..
make
```

# Run
```
mpiexec -n 2 ./fpmas-agent-group
```

## Output
```
Group 0 agents on process 0:
- ID: [0:0], Type: 6Agent1
- ID: [0:1], Type: 6Agent1
Group 0 agents on process 1:
- ID: [1:0], Type: 6Agent1
- ID: [1:1], Type: 6Agent1

Group 1 agents on process 0:
- ID: [0:2], Type: 6Agent1
- ID: [0:3], Type: 6Agent2
Group 1 agents on process 1:
- ID: [1:2], Type: 6Agent1
- ID: [1:3], Type: 6Agent2
```
