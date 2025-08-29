#!/bin/python3

import sys
import subprocess

def main(file):
    nodes = {}
    out = subprocess.getoutput(f'cat {file} | grep ": CriticalAreaRouter {"{"}" | sed "s/^.* \\([a-zA-Z0-9]*\\): CriticalAreaRouter.*$/\\1/g"')
    for node in out.splitlines():
        nodes[node] = 0
    
    out = subprocess.getoutput(f'cat {file} | grep "<--> fiberline .* <-->" | sed "s/^ *\([a-zA-Z0-9]*\)\.pppg++ .* \([a-zA-Z0-9]*\)\.pppg++;.*$/\\1 \\2/g"')
    for edge in out.splitlines():
        [src, dest] = edge.split(" ")
        nodes[src] += 1
        nodes[dest] += 1

    #print(nodes)
    compute_density(nodes)
    


def compute_density(nodes):
    n = len(nodes)
    possible_degrees = 0
    total_degrees = 0
    for node, degree in nodes.items():
        total_degrees += degree
        possible_degrees += n - 1

    assert possible_degrees == n * (n-1)
    
    print(f"n: {n}")
    print(f"Total unidirected edges: {total_degrees}")
    print(f"Total possible edges: {possible_degrees}")
    print(f"Density: {total_degrees / possible_degrees}")


if __name__ == "__main__":
    main(sys.argv[1])