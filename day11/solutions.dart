import 'dart:io';

void appendColAtIndex(List<String> image, int colIdx) {
  int width = image.length;

  for (int rowIdx = 0; rowIdx < width; rowIdx++) {
    String row = image[rowIdx];
    image[rowIdx] = row.substring(0, colIdx) + "." + row.substring(colIdx);
  }
}

void appendRowAtIndex(List<String> image, int rowIdx) {
  image.insert(rowIdx, "." * image[0].length);
}

List<int> findEmptyCols(List<String> image) {
  List<int> emptyColIndices = <int>[];
  int width = image.length;
  int length = image[0].length;

  for (int colIdx = 0; colIdx < length; colIdx++) {
    bool isEmpty = true;

    for (int rowIdx = 0; rowIdx < width; rowIdx++) {
      if (image[rowIdx][colIdx] != ".") {
        isEmpty = false;
        break;
      }
    }

    if (isEmpty) {
      emptyColIndices.add(colIdx);
    }
  }

  return emptyColIndices;
}

List<int> findEmptyRows(List<String> image) {
  List<int> emptyRowIndices = <int>[];

  for (int rowIdx = 0; rowIdx < image.length; rowIdx++) {
    if (!image[rowIdx].contains("#")) {
      emptyRowIndices.add(rowIdx);
    }
  }

  return emptyRowIndices;
}

int mhDistance((int, int) a, (int, int) b) {
  return (a.$1 - b.$1).abs() + (a.$2 - b.$2).abs();
}

int moddedMhDistance((int, int) a, (int, int) b, List<int> emptyColIndices,
    List<int> emptyRowIndices) {
  int distance = 0;
  int dy = (a.$1 < b.$1) ? 1 : -1;
  int dx = (a.$2 < b.$2) ? 1 : -1;
  int offset = 1000000;

  while (a.$1 != b.$1) {
    a = (a.$1 + dy, a.$2);
    int deltaY = emptyRowIndices.contains(a.$1) ? offset : 1;
    distance += deltaY;
  }

  while (a.$2 != b.$2) {
    a = (a.$1, a.$2 + dx);
    int deltaX = emptyColIndices.contains(a.$2) ? offset : 1;
    distance += deltaX;
  }

  return distance;
}

void part1(
    List<String> image, List<int> emptyColIndices, List<int> emptyRowIndices) {
  int shift = 0;

  for (int colIdx in emptyColIndices) {
    appendColAtIndex(image, colIdx + shift);
    shift++;
  }

  shift = 0;

  for (int rowIdx in emptyRowIndices) {
    appendRowAtIndex(image, rowIdx + shift);
    shift++;
  }

  Set<(int, int)> galaxyLocations = Set<(int, int)>();

  for (int rowIdx = 0; rowIdx < image.length; rowIdx++) {
    for (int colIdx = 0; colIdx < image[rowIdx].length; colIdx++) {
      if (image[rowIdx][colIdx] == "#") {
        galaxyLocations.add((rowIdx, colIdx));
      }
    }
  }

  int distSum = 0;

  do {
    (int, int) galaxyLoc = galaxyLocations.first;
    galaxyLocations.remove(galaxyLoc);

    for ((int, int) loc in galaxyLocations) {
      distSum += mhDistance(galaxyLoc, loc);
    }
  } while (galaxyLocations.isNotEmpty);

  print("Distance is $distSum.");
}

void part2(
    List<String> image, List<int> emptyColIndices, List<int> emptyRowIndices) {
  Set<(int, int)> galaxyLocations = Set<(int, int)>();

  for (int rowIdx = 0; rowIdx < image.length; rowIdx++) {
    for (int colIdx = 0; colIdx < image[rowIdx].length; colIdx++) {
      if (image[rowIdx][colIdx] == "#") {
        galaxyLocations.add((rowIdx, colIdx));
      }
    }
  }

  int distSum = 0;

  do {
    (int, int) galaxyLoc = galaxyLocations.first;
    galaxyLocations.remove(galaxyLoc);

    for ((int, int) loc in galaxyLocations) {
      distSum +=
          moddedMhDistance(galaxyLoc, loc, emptyColIndices, emptyRowIndices);
    }
  } while (galaxyLocations.isNotEmpty);

  print("Distance is $distSum.");
}

void main(List<String> args) {
  if (args.length < 1) {
    throw Exception("No input file.");
  }

  final List<String> image = File(args[0]).readAsLinesSync();
  final List<int> emptyColIndices = findEmptyCols(image)..sort();
  final List<int> emptyRowIndices = findEmptyRows(image)..sort();

  part1(List<String>.from(image), List<int>.from(emptyColIndices),
      List<int>.from(emptyRowIndices));
  part2(List<String>.from(image), List<int>.from(emptyColIndices),
      List<int>.from(emptyRowIndices));
}
