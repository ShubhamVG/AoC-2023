from __future__ import annotations
from dataclasses import dataclass
import sys


class ColorEnum:
    RED = 0
    GREEN = 1
    BLUE = 2


@dataclass
class Cube:
    quantity: int
    color: int  # From ColorEnum

    def is_comparable(self, other: Cube) -> bool:
        if self.color == other.color:
            return True

        return False

    def __lt__(self, other: Cube) -> bool:
        return self.quantity < other.quantity

    def __gt__(self, other: Cube) -> bool:
        return self.quantity > other.quantity


def parse_game(game_info: str) -> list[list[Cube]]:
    """Return list of cubes (2D list)."""

    colon_index = game_info.index(":")
    game_info = game_info[colon_index + 1 :]
    handfuls = game_info.split(";")
    cube_2dlist = []

    for handful in handfuls:
        cube_strings = handful.split(",")
        cubes = []

        for cube_string in cube_strings:
            quantity, color = cube_string.strip().split(" ")
            color = "rgb".index(color[0])
            cube = Cube(int(quantity), color)
            cubes.append(cube)

        cube_2dlist.append(cubes)

    return cube_2dlist


def main():
    if len(sys.argv) < 2:
        print("Error: No input file.")
        return

    with open(sys.argv[1], "r") as f:
        game_infos = f.readlines()

    present_cubes = (
        Cube(12, ColorEnum.RED),
        Cube(13, ColorEnum.GREEN),
        Cube(14, ColorEnum.BLUE),
    )

    i, sum_ = 1, 0

    for game_info in game_infos:
        cube_2dlist = parse_game(game_info)
        to_add = True

        for cubes in cube_2dlist:
            for cube in cubes:
                if cube > present_cubes[cube.color]:
                    to_add = False
                    break

            if not to_add:
                break

        if to_add:
            sum_ += i

        i += 1

    print("Sum is: ", sum_)


if __name__ == "__main__":
    main()
