import sys

import part1


def main():
    if len(sys.argv) < 2:
        print("Error: No input file.")
        return

    with open(sys.argv[1], "r") as f:
        game_infos = f.readlines()

    sum_ = 0

    for game_info in game_infos:
        cube_2dlist = part1.parse_game(game_info)
        red_count, green_count, blue_count = 0, 0, 0

        for cubes in cube_2dlist:
            for cube in cubes:
                if cube.color == part1.ColorEnum.RED:
                    if cube.quantity > red_count:
                        red_count = cube.quantity
                elif cube.color == part1.ColorEnum.GREEN:
                    if cube.quantity > green_count:
                        green_count = cube.quantity
                else:
                    if cube.quantity > blue_count:
                        blue_count = cube.quantity

        nums = 1
        
        for n in (red_count, green_count, blue_count):
            nums *= n if n != 0 else 1

        sum_ += nums

    print("The sum is:", sum_)


if __name__ == "__main__":
    main()
