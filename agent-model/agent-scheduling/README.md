# FPMAS Agent Group Example

The complete working example of the [Agent Scheduling wiki
page](https://github.com/FPMAS/FPMAS/wiki/Agent-Scheduling-And-Runtime).

This example illustrates the FPMAS
[Scheduler](https://fpmas.github.io/FPMAS/classfpmas_1_1api_1_1scheduler_1_1Scheduler.html)
usage.

# Build

```
mkdir build
cd build
cmake ..
make
```

# Run
```
mpiexec -n 2 ./fpmas-agent-scheduling
```

## Output
```

== TimeStep: 0
[Agent 1] Agent [1:0] acts.
[Agent 1] Agent [1:1] acts.
[Agent 1] Agent [0:0] acts.
[Agent 1] Agent [0:1] acts.
[Agent 2] Agent [1:3] acts.
[Agent 2] Agent [1:2] acts.
[Agent 2] Agent [0:3] acts.
[Agent 2] Agent [0:2] acts.

Group 0 agents on process 0:
- ID: [0:0], Type: 6Agent1
- ID: [0:1], Type: 6Agent1
Group 0 agents on process 1:
- ID: [1:0], Type: 6Agent1
- ID: [1:1], Type: 6Agent1

Group 1 agents on process 0:
- ID: [0:2], Type: 6Agent2
- ID: [0:3], Type: 6Agent2
Group 1 agents on process 1:
- ID: [1:2], Type: 6Agent2
- ID: [1:3], Type: 6Agent2

== TimeStep: 1

Group 0 agents on process 0:
- ID: [0:0], Type: 6Agent1
- ID: [0:1], Type: 6Agent1
Group 0 agents on process 1:
- ID: [1:0], Type: 6Agent1
- ID: [1:1], Type: 6Agent1

Group 1 agents on process 0:
- ID: [0:2], Type: 6Agent2
- ID: [0:3], Type: 6Agent2
Group 1 agents on process 1:
- ID: [1:2], Type: 6Agent2
- ID: [1:3], Type: 6Agent2

== TimeStep: 2
[Agent 1] Agent [0:0] acts.
[Agent 1] Agent [0:1] acts.
[Agent 1] Agent [1:0] acts.
[Agent 1] Agent [1:1] acts.
[Agent 2] Agent [0:2] acts.
[Agent 2] Agent [0:3] acts.
[Agent 2] Agent [1:2] acts.
[Agent 2] Agent [1:3] acts.

Group 0 agents on process 0:
- ID: [0:0], Type: 6Agent1
- ID: [0:1], Type: 6Agent1
Group 0 agents on process 1:
- ID: [1:0], Type: 6Agent1
- ID: [1:1], Type: 6Agent1

Group 1 agents on process 0:
- ID: [0:2], Type: 6Agent2
- ID: [0:3], Type: 6Agent2
Group 1 agents on process 1:
- ID: [1:2], Type: 6Agent2
- ID: [1:3], Type: 6Agent2

== TimeStep: 3
[Agent 1] Agent [1:1] acts.
[Agent 1] Agent [1:0] acts.
[Agent 1] Agent [0:1] acts.
[Agent 1] Agent [0:0] acts.

Group 0 agents on process 0:
- ID: [0:0], Type: 6Agent1
- ID: [0:1], Type: 6Agent1
Group 0 agents on process 1:
- ID: [1:0], Type: 6Agent1
- ID: [1:1], Type: 6Agent1

Group 1 agents on process 0:
- ID: [0:2], Type: 6Agent2
- ID: [0:3], Type: 6Agent2
Group 1 agents on process 1:
- ID: [1:2], Type: 6Agent2
- ID: [1:3], Type: 6Agent2
```

See the corresponding [wiki
page](https://github.com/FPMAS/FPMAS/wiki/Agent-Scheduling-And-Runtime) for
more details.
