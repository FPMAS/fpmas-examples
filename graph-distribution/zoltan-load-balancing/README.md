# FPMAS Zoltan Load Balancing Example

This example, introduced in the [Load Balancing wiki page](), presents how the
`ZoltanLoadBalancing` algorithm can be used to balance and distribute a graph
across processors.

A "node ring" is built on process 0, with an additional extra node on each
processor.

The global graph is then distributed using the `ZoltanLoadBalancing` algorithm.

# Build

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
```
mpiexec -n 3 ./zoltan-load-balancing
```

# Output

Example output for 3 processes :
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
- [0:2] [LOCAL]
- [0:1] [LOCAL]
- [0:0] [DISTANT]
== Local edges :
- [0:2] : [0:2] -> [0:0] (DEFAULT_LAYER)
- [0:1] : [0:1] -> [0:2] (DEFAULT_LAYER)
- [0:0] : [0:0] -> [0:1] (DEFAULT_LAYER)

== [Process 1] ==
== Local Nodes :
- [0:2] [DISTANT]
- [0:1] [DISTANT]
- [0:0] [LOCAL]
- [1:0] [LOCAL]
== Local edges :
- [0:2] : [0:2] -> [0:0] (DEFAULT_LAYER)
- [0:0] : [0:0] -> [0:1] (DEFAULT_LAYER)

== [Process 2] ==
== Local Nodes :
- [0:3] [LOCAL]
- [2:0] [LOCAL]
== Local edges :

```

## Analysis

The `ZoltanLoadBalancing` algorithm as automatically computed a partition that
assign 2 nodes to each process, and the graph has been automatically
distributed accordingly.

Moreover, 2 unconnected nodes has been assigned to process 2, and the "ring" is
distributed only on process 0 and 1, in order to minimize edges across
processors, and so communication volumes.
