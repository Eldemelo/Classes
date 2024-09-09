import 'dart:io';
void main(){
  stdout.write("Enter a string: ");
  String userString = stdin.readLineSync()!;
  String reversed = reverseString(userString);
  print("");
  print("Reversed String: $reversed");
  isPalindrome(userString, reversed);
}

String reverseString(String input){
  int length = input.length;
  String reversed = "";
  for (int i = length - 1; i >= 0; i--) {
    reversed = reversed + input[i];
  }
  return reversed;
}

void isPalindrome(String original, String reversed){
  if(original == reversed){
    print("Is Palindrome: Yes");
  }
  else{
    print("Is Palindrome: No");
  }
}