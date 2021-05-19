# FPMAS Graph Based Spatial Model Example

The complete working example of the [Graph Based Spatial Model wiki page](https://github.com/FPMAS/FPMAS/wiki/Spatial-Graph).

A `SpatialModel` is defined, with a random uniform `GraphCell` network. Two
`SpatialAgents` are then initialized on the cell network, and randomly move for
5 iterations, updating their perceptions and mobility fields.

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
mpiexec -n 2 ./fpmas-spatial-graph
```

# Output

Example output on 2 processes:
<table>
<tr><th>Rank 0</th><th>Rank 1</th></tr>
<tr><td><pre><code>Agent [0:5]:
    Step: 0
    Location: [0:4]
    Perceptions: [ ]
Agent [0:5]:
    Step: 1
    Location: [1:1]
    Perceptions: [ ]
Agent [0:5]:
    Step: 2
    Location: [0:2]
    Perceptions: [ [1:5] ]
Agent [0:5]:
    Step: 3
    Location: [0:1]
    Perceptions: [ [1:5] ]
Agent [0:5]:
    Step: 4
    Location: [1:4]
    Perceptions: [ [1:5] ]</code></pre>
	</td>
	<td><pre><code>Agent [1:5]:
    Step: 0
    Location: [1:4]
    Perceptions: [ ]
Agent [1:5]:
    Step: 1
    Location: [0:1]
    Perceptions: [ ]
Agent [1:5]:
    Step: 2
    Location: [1:4]
    Perceptions: [ ]
Agent [1:5]:
    Step: 3
    Location: [0:1]
    Perceptions: [ [0:5] ]
Agent [1:5]:
    Step: 4
    Location: [1:4]
    Perceptions: [ [0:5] ]</code></pre>
	</td>
</tr>
</table>

See the [Graph Based Spatial Model wiki
page](https://github.com/FPMAS/FPMAS/wiki/Spatial-Graph) for explanations and
graph representations of the `SpatialModel` at each time step.
