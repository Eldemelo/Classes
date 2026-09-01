
import 'dart:io';

void main(){
  print("Enter the first integer: ");
  int firstNum = int.parse(stdin.readLineSync()!);
  print("Enter the second integer: ");
  int? secondNum = int.parse(stdin.readLineSync()!);

  print("Addition: ${firstNum + secondNum}");
  print("Subtraction: ${firstNum - secondNum}");
  print("Multiplication: ${firstNum * secondNum}");
  print("Division: ${firstNum ~/ secondNum}");
  print("Modulus: ${firstNum % secondNum}");
  if(firstNum > secondNum){
    print("$firstNum is greater than $secondNum");
  }
  else{
    print("$secondNum is greater than $firstNum");
  }
}