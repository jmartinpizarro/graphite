# graphite

<p align="center">
  <img src="assets/graphite.png" alt="Graphite Logo" width="500">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-20-00599C?style=flat-square&logo=cplusplus&logoColor=white" alt="C++20">
  
  <a href="https://github.com/jmartinpizarro/graphite/actions/workflows/cmake-single-platform.yml">
    <img src="https://img.shields.io/github/actions/workflow/status/jmartinpizarro/graphite/cmake-single-platform.yml?branch=main&style=flat-square&logo=github&label=build" alt="CI Status">
  </a>

  <img src="https://img.shields.io/badge/type-header--only-purple?style=flat-square" alt="Header Only">

  <a href="https://github.com/jmartinpizarro/graphite/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/jmartinpizarro/graphite?style=flat-square&color=green" alt="License">
  </a>

  <a href="https://github.com/jmartinpizarro/graphite/releases">
    <img src="https://img.shields.io/github/v/release/jmartinpizarro/graphite?include_prereleases&style=flat-square&color=orange" alt="Release">
</a>
</p>

Graphite is a generic programming-based library for working with and processing graphs.

> [!CAUTION]
> Do not use this library in professional projects. If you do, it's your fault, not mine :)

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


