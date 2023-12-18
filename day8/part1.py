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
    nodes: dict[str, tuple[str, str]] = {}

    for node_text in nodes_text:
        node, left, right = parse_node(node_text)
        nodes[node] = (left, right)

    curr_node = "AAA"
    steps = 0
    i, max_count = 0, len(directions) - 1

    while curr_node != "ZZZ":
        curr_node = nodes[curr_node][0 if directions[i] == "L" else 1]
        steps += 1

        if i == max_count:
            i = 0
        else:
            i += 1

    print("Steps:", steps)

if __name__ == "__main__":
    main()
