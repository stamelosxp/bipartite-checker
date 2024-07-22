# Bipartite Checker

This repository contains an implementation of a Bipartite Graph Checker using the LEDA (Library of Efficient Data types and Algorithms) C++ library. The project checks whether a given graph is bipartite by utilizing the Breadth-First Search (BFS) algorithm and compares the performance of this checker on three different types of graphs.

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [BFS Algorithm](#bfs-algorithm)
- [Graph Types Comparison](#graph-types-comparison)

## Introduction

A bipartite graph is a graph whose vertices can be divided into two disjoint and independent sets such that every edge connects a vertex in one set to a vertex in the other set. This project implements a checker to determine if a given graph is bipartite using the BFS algorithm.

## Installation

To use this project, you need to have the LEDA library installed on your system. Follow the instructions below to set up the project:

1. Clone the repository:
    ```sh
    git clone https://github.com/stamelosxp/bipartite-checker.git
    ```

2. Navigate to the `bin` directory:
    ```sh
    cd bipartite-checker/bin
    ```

3. Compile the project and build the `bipartite_checker` executable:
    ```sh
    make bipartite_checker

    ```

## Usage

Run the compiled `bipartite_checker` executable:
```sh
./bipartite_checker 
```

## BFS Algorithm

The BFS (Breadth-First Search) algorithm is used to determine if the graph is bipartite. The algorithm works as follows:

1. Initialize all vertices as unvisited.
2. Pick an unvisited vertex and color it with the first color.
3. Perform BFS traversal starting from this vertex:
    - For each adjacent vertex, if it is not colored, color it with the alternate color.
    - If it is already colored and has the same color as the current vertex, the graph is not bipartite.
4. Repeat the process for all disconnected components of the graph.

If no conflicts are found, the graph is bipartite.

## Graph Types Comparison

This project includes performance comparisons of the bipartite checker on three types of graphs:

1. **Nested Squares:** A series of nested square graphs where each square is connected to the next larger square.
    
2. **Ring with Odd Number of Nodes:** A circular graph structure with an odd number of nodes, forming a single cycle.
    
3. **Complex Graph:** A graph with 4 levels, where:
    
    - All edges from one level are connected to all edges of the next level.
    - One random edge from level i is connected to all edges of level i+1.
    - One random edge from level i is connected to one random edge from level i+2.
    - One random edge from level i+1 is connected to one random edge from level i+3.

The comparison measures the time complexity and performance of the bipartite checker algorithm on these different graph structures, demonstrating its efficiency and limitations.
