# graphite

Graphite is a generic programming-based library for working and processing graphs.

## Algorithms

Several algorithms have been implemented:

- DFS
- BFS
- Dijkstra
- A*
- Prim
- Kruskal
- Floyd-Warshall

## Compile and deploy

```bash
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
```

If you are developing:

```bash
ln -Sf build/compile_commands.json
```


