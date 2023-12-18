import 'dart:io';

int getNextNum(Iterable<int> numbers) {
  if (Set<int>.from(numbers).length == 1) {
    return numbers.elementAt(0);
  }

  List<int> differences = <int>[];
  int loopCount = numbers.length - 1;

  for (int i = 0; i < loopCount; i++) {
    differences.add(numbers.elementAt(i + 1) - numbers.elementAt(i));
  }

  return numbers.last + getNextNum(differences);
}

int getPrevNum(Iterable<int> numbers) {
  numbers = numbers.toList().reversed;
  return getNextNum(numbers);
}

void main(List<String> args) {
  if (args.length < 1) {
    print("Error: No input file.");
    return;
  }

  int sumOfNexts = 0;
  int sumOfPrevs = 0;
  final List<String> numbersStringList = File(args[0]).readAsLinesSync();

  for (String numbersString in numbersStringList) {
    Iterable<int> numbers = numbersString.split(" ").map((e) => int.parse(e));
    sumOfNexts += getNextNum(numbers);
    sumOfPrevs += getPrevNum(numbers);
  }

  print("Sum of nexts: $sumOfNexts.");
  print("Sum of prevs: $sumOfPrevs.");
}
