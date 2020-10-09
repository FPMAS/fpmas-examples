# FPMAS Basic Graph Distribution Example

The complete working example presented in the [Load Balancing wiki
page](https://github.com/FPMAS/FPMAS/wiki/Load-Balancing#graph-distribution-and-partition-map).

The example presents the principle of the
[`PartitionMap`](https://fpmas.github.io/FPMAS/namespacefpmas_1_1api_1_1graph.html#a3b8d45dcdede19e41beff03c30a0671d),
and how it can be used to manually distribute a `DistributedGraph` using the
[`DistributedGraph::distribute()`](https://fpmas.github.io/FPMAS/classfpmas_1_1api_1_1graph_1_1DistributedGraph.html#a63f19151be3a12d5cd4f996e161353ee)
method.

A simple "node ring" is created from process 0, and each node is assigned to a
process. For the purpose of the example, an extra node is also built on each
process, without specifying it in the partition.

# Build
The `fpmas-basic-distribution` target can be built with the following script :
```
mkdir build
cd build
cmake ..
make
```
The default synchronization mode is
[HardSyncMode](https://fpmas.github.io/FPMAS/classfpmas_1_1synchro_1_1hard_1_1HardSyncMode.html).
However, dynamic graph operations are available in **any** synchronization
mode. So, for the purpose of demonstration, the synchronization mode can be
chosen at compile time, replacing the third line of the previous script by
```
cmake -DSYNC_MODE=<sync_mode> ..
```
Example :
```
cmake -DSYNC_MODE=GhostMode ..
```

# Run

Example :
```
mpiexec -n 3 fpmas-basic-distribution
```

# Output

```
==========================
== Initial Distribution ==
==========================

== [Process 0] ==
== Local Nodes :
- [0:3] [LOCAL]
- [0:2] [LOCAL]
- [0:1] [LOCAL]
- [0:0] [LOCAL]
== Local edges :
- [0:2] : [0:2] -> [0:0] (DEFAULT_LAYER)
- [0:1] : [0:1] -> [0:2] (DEFAULT_LAYER)
- [0:0] : [0:0] -> [0:1] (DEFAULT_LAYER)

== [Process 1] ==
== Local Nodes :
- [1:0] [LOCAL]
== Local edges :

== [Process 2] ==
== Local Nodes :
- [2:0] [LOCAL]
== Local edges :

========================
== Final Distribution ==
========================

== [Process 0] ==
== Local Nodes :
- [0:3] [LOCAL]
- [0:2] [DISTANT]
- [0:1] [DISTANT]
- [0:0] [LOCAL]
== Local edges :
- [0:2] : [0:2] -> [0:0] (DEFAULT_LAYER)
- [0:0] : [0:0] -> [0:1] (DEFAULT_LAYER)

== [Process 1] ==
== Local Nodes :
- [0:2] [DISTANT]
- [0:0] [DISTANT]
- [0:1] [LOCAL]
- [1:0] [LOCAL]
== Local edges :
- [0:1] : [0:1] -> [0:2] (DEFAULT_LAYER)
- [0:0] : [0:0] -> [0:1] (DEFAULT_LAYER)

== [Process 2] ==
== Local Nodes :
- [0:0] [DISTANT]
- [0:1] [DISTANT]
- [0:2] [LOCAL]
- [2:0] [LOCAL]
== Local edges :
- [0:2] : [0:2] -> [0:0] (DEFAULT_LAYER)
- [0:1] : [0:1] -> [0:2] (DEFAULT_LAYER)
```

## Analysis

For each `i`, node `[0:i]` is imported on process `i`.
`DISTANT` nodes and edges are automatically created on each process to maintain
the `DistributedGraph` structure. Useless nodes and edges are also removed from
process 0.
