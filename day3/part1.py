import sys

Pos = tuple[int, int]


def locate_fancy_symbols(engine_schematic: list[str]) -> list[Pos]:
    positions = []

    for string_index in range(len(engine_schematic)):
        for char_index in range(len(engine_schematic[string_index])):
            char = engine_schematic[string_index][char_index]

            if char != "." and not char.isdigit():
                positions.append((string_index, char_index))

    return positions


def get_adjacent_numbers(engine_schematic: list[str], symbol_pos: Pos) -> list[int]:
    def extract_num_and_change_str(starting_pos: Pos) -> int:
        x, y = starting_pos
        num_string = ""
        text = engine_schematic[x]

        # Go left
        offset_left = 1  # 1 cuz I did the maths

        while y - offset_left >= 0 and (digit_str := text[y - offset_left]).isdigit():
            num_string = digit_str + num_string
            offset_left += 1

        # Go right
        offset_right = 0

        while (
            y + offset_right < len(text)
            and (digit_str := text[y + offset_right]).isdigit()
        ):
            num_string = num_string + digit_str
            offset_right += 1

        engine_schematic[x] = (
            text[0 : y - offset_left]
            + "." * (offset_left + offset_right)
            + text[y + offset_right :]
        )

        return int(num_string)

    x, y = symbol_pos
    adjacent_nums = []

    directions = (
        (0, -1),  # Left
        (0, 1),  # Right
        (-1, 0),  # Up
        (1, 0),  # Down
        (-1, -1),  # Upper-left
        (-1, 1),  # Upper-right
        (1, -1),  # Lower-left
        (1, 1),  # Lower-right
    )

    for offset_x, offset_y in directions:
        new_x, new_y = x + offset_x, y + offset_y

        if (
            new_x < 0
            or new_y < 0
            or new_x >= len(engine_schematic)
            or new_y >= len(engine_schematic[x])
        ):
            continue

        if engine_schematic[new_x][new_y].isdigit():
            num = extract_num_and_change_str((new_x, new_y))
            adjacent_nums.append(num)

    return adjacent_nums


def main():
    if len(sys.argv) < 2:
        print("Error: No input file.")
        return

    with open(sys.argv[1], "r") as f:
        engine_schematic = f.read().splitlines()

    fancy_symbol_positions = locate_fancy_symbols(engine_schematic)
    sum_ = 0

    for position in fancy_symbol_positions:
        sum_ += sum(get_adjacent_numbers(engine_schematic, position))

    print("Sum is:", sum_)


if __name__ == "__main__":
    main()
