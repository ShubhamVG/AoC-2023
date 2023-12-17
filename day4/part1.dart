import 'dart:io';
import 'dart:math' as math;

int calculateScore(List<int> winnerNumbers, List<int> yourNumbers) {
  int count = 0;

  for (int num in yourNumbers) {
    if (winnerNumbers.contains(num)) {
      count++;
    }
  }

  return (count == 0) ? 0 : math.pow(2, count - 1) as int;
}

(List<int>, List<int>) splitIntsFromCard(String card) {
  int colonIndex = card.indexOf(':') + 1;
  card = card.substring(colonIndex);
  List<String> numbersStringList = card.split('|');

  String winnerNumbersString = numbersStringList[0];
  String yourNumbersString = numbersStringList[1];

  List<int> winnerNumbers = [
    for (String chars in winnerNumbersString.split(' '))
      if (chars.isNotEmpty) int.parse(chars)
  ];

  List<int> yourNumbers = [
    for (String chars in yourNumbersString.split(' '))
      if (chars.isNotEmpty) int.parse(chars)
  ];

  return (winnerNumbers, yourNumbers);
}

void main(List<String> args) {
  if (args.length < 1) {
    print("Error: No input file.");
    return;
  }

  File file = File(args[0]);
  List<String> cardStrings = file.readAsLinesSync();
  int sum = 0;

  for (String cardString in cardStrings) {
    List<int> winnerNumbers, yourNumbers;
    (winnerNumbers, yourNumbers) = splitIntsFromCard(cardString);
    sum += calculateScore(winnerNumbers, yourNumbers);
  }

  print("Sum is $sum");
}
