import 'dart:io';

import 'part1.dart' as part1;

void changeFrequency(List<int> winnerNumbers, List<int> yourNumbers,
    Map<int, int> freq, int start) {
  int count = 0;

  for (int num in yourNumbers) {
    if (winnerNumbers.contains(num)) {
      count++;
    }
  }

  for (int i = count; i > 0; i--) {
    if (start + i <= freq.length) {
      freq[start + i] = freq[start + i]! + freq[start]!;
    }
  }
}

void main(List<String> args) {
  if (args.length < 1) {
    print("Error: No input file.");
    return;
  }

  File file = File(args[0]);
  List<String> cardStrings = file.readAsLinesSync();
  Map<int, int> freq = {};

  for (int i = 1; i <= cardStrings.length; i++) {
    freq[i] = 1;
  }

  int i = 1;
  for (String cardString in cardStrings) {
    List<int> winnerNumbers, yourNumbers;
    (winnerNumbers, yourNumbers) = part1.splitIntsFromCard(cardString);
    changeFrequency(winnerNumbers, yourNumbers, freq, i);
    i++;
  }

  int sum = 0;
  for (int x in freq.values) sum += x;
  print("Sum is $sum");
}
