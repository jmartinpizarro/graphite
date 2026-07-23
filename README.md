# graphite

<p align="center">
  <img src="assets/logo.png" alt="Graphite Logo" width="500">
</p>

![C++2X](https://img.shields.io/badge/C%2B%2B-20-00599C?style=flat-square&logo=cplusplus&logoColor=white)
[![CI](https://img.shields.io/github/actions/workflow/status/jmartinpizarro/graphite/ci.yml?branch=main&style=flat-square&logo=github&label=build)](https://github.com/jmartinpizarro/graphite/actions)
[![License](https://img.shields.io/github/license/jmartinpizarro/graphite?style=flat-square&color=green)](LICENSE)
[![Release](https://img.shields.io/github/v/release/jmartinpizarro/graphite?style=flat-square&color=orange)](https://github.com/jmartinpizarro/graphite/releases)

Graphite is a generic programming-based library for working with and processing graphs.

>[!DANGER]
>Do not use this lib in profesional projects. If you do, its your fault, not mine :)

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


