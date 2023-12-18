import math
import sys

def parse_node(node_text: str) -> tuple[str, str, str]:
    head, left, right = node_text[0:3], node_text[7:10], node_text[12:15]

    return (head, left, right)

def main():
    if len(sys.argv) < 2:
        print("Error: No input file.")
        return

    with open(sys.argv[1], "r") as f:
        data = f.read().split("\n")

    directions = data[0]
    nodes_text = data[2:-1]
    curr_nodes = []
    nodes: dict[str, tuple[str, str]] = {}

    for node_text in nodes_text:
        node, left, right = parse_node(node_text)
        nodes[node] = (left, right)

        if node[-1] == "A":
            curr_nodes.append(node)

    max_count = len(directions) - 1
    cycles = []

    # Had to watch a YouTube video to understand this part. Credits: HyperNeutrino
    for node in curr_nodes:
        cycle = []
        first_z = None
        i = 0
        steps_count = 0

        while True:
            while steps_count == 0 or not node.endswith("Z"):
                node = nodes[node][0 if directions[i] == "L" else 1]
                steps_count += 1

                if i == max_count:
                    i = 0
                else:
                    i += 1

            cycle.append(steps_count)

            if first_z == None:
                first_z = node
                steps_count = 0
            else:
                break

        cycles.append(cycle)

    print(cycles)
    print(math.lcm(*(cycle[0] for cycle in cycles)))

if __name__ == "__main__":
    main()
