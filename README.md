# Dijkstra's Algorithm with a Working-Set Heap

This project is a C implementation of Dijkstra's shortest path algorithm using a specialized "Working-Set Heap" data structure.

The `WorkingSetHeap` is a conceptual implementation of the "beyond-worst-case" heap described in the FOCS 2024 paper, *Universal Optimality of Dijkstra Via Beyond-Worst-Case Heaps*. This data structure is designed to be exceptionally fast for the types of operations common in Dijkstra's algorithm, specifically when recently added items are extracted quickly.

The main `dijkstra.c` file runs a benchmark comparing a classic (but flawed) Dijkstra implementation against the version using the `WorkingSetHeap` to demonstrate the new structure in action.

## How to Run

1.  Compile the code using the Makefile.

    ```bash
    make dijkstra
    ```

2. Run the executable.

    ```bash
    bin/dijkstra
    ```

Sample output:

```text
$ bin/dijkstra 
--- Running Classic Dijkstra ---

Shortest distance from vertex 0:
0 -> 0 = 0
0 -> 1 = 8
0 -> 2 = 9
0 -> 3 = 5
0 -> 4 = 7
Dijkstra (Classic) Time taken: 31.000000 us


--- Running Dijkstra with Working-Set Heap ---

Dijkstra's results starting from 0:
0 -> 0 = 0
0 -> 1 = 8
0 -> 2 = 9
0 -> 3 = 5
0 -> 4 = 7
Dijkstra (WS Heap) Time taken: 22.000000 us
```

## Core Data Structures

*   **`inc/minheap.h`**: A standard binary min-heap used as the building block for the `WorkingSetHeap`.

*   **`inc/workingset_heap.h`**: The core of the paper's idea. This is a "heap of heaps," organized into buckets of doubly-exponentially increasing size (`2, 4, 16, 256, ...`). New items are inserted into the smallest heap, and a "ripple-carry" mechanism promotes heaps to larger buckets upon overflow. This gives `delete-min` a cost relative to the item's "working set" (how many items were inserted after it) rather than the total heap size.

## Citation
This implementation is based on the data structure described in the following paper.

```bibtex
@INPROCEEDINGS{focs2024-haeupler,
  author={Haeupler, Bernhard and Hladík, Richard and Rozhoň, Václav and Tarjan, Robert E. and Tetĕk, Jakub},
  booktitle={2024 IEEE 65th Annual Symposium on Foundations of Computer Science (FOCS)}, 
  title={Universal Optimality of Dijkstra Via Beyond-Worst-Case Heaps}, 
  year={2024},
  volume={},
  number={},
  pages={2099-2130},
  keywords={Computer science;Costs;Data structures;Topology;Periodic structures;dijkstras algorithm;universal optimality;beyond worst-case;shortest paths},
  doi={10.1109/FOCS61266.2024.00125}
}
```