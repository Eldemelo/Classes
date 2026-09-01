import 'package:flutter/material.dart';
import 'package:expressions/expressions.dart';
import 'dart:math';

void main() {
  runApp(CalculatorApp());
}

class CalculatorApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Ethan\'s Calculator',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: CalculatorScreen(),
    );
  }
}

class CalculatorScreen extends StatefulWidget {
  @override
  _CalculatorScreenState createState() => _CalculatorScreenState();
}

class _CalculatorScreenState extends State<CalculatorScreen> {
  final TextEditingController _controller = TextEditingController();
  String _expression = '';

  void _onPressed(String value) {
    setState(() {
      if (value == 'C') {
        _expression = '';
        _controller.clear();
      } else if (value == '=') {
        _calculate();
      } else if (value == '^2') {
        _expression += '^2';
        _controller.text = _expression;
      } else {
        _expression += value;
        _controller.text = _expression;
      }
    });
  }

  void _calculate() {
    try {
      String modifiedExpression = _expression.replaceAllMapped(
        RegExp(r'(\d+)\^2'),
        (match) => 'pow(${match.group(1)}, 2)',
      );

      // Custom evaluator for pow function
      final evaluator = const ExpressionEvaluator();
      final context = {
        'pow': (num base, num exponent) => pow(base, exponent),
      };

      final expression = Expression.parse(modifiedExpression);
      final result = evaluator.eval(expression, context);
      _controller.text = '$_expression = $result';
    } catch (e) {
      _controller.text = 'Error';
    }
  }

  void _clear() {
    setState(() {
      _expression = '';
      _controller.clear();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Ethan\'s Calculator'),
      ),
      body: Column(
        children: <Widget>[
          Expanded(
            child: Container(
              padding: EdgeInsets.all(16.0),
              alignment: Alignment.centerRight,
              child: TextField(
                controller: _controller,
                style: TextStyle(fontSize: 24),
                decoration: InputDecoration(border: InputBorder.none),
                readOnly: true,
              ),
            ),
          ),
          Expanded(
            flex: 2,
            child: GridView.count(
              crossAxisCount: 4,
              children: <String>[
                '7',
                '8',
                '9',
                '/',
                '4',
                '5',
                '6',
                '*',
                '1',
                '2',
                '3',
                '-',
                'C',
                '0',
                '=',
                '+',
                '^2',
                '%'
              ].map((value) {
                return GridTile(
                  child: ElevatedButton(
                    onPressed: () => _onPressed(value),
                    child: Text(
                      value,
                      style: TextStyle(fontSize: 24),
                    ),
                  ),
                );
              }).toList(),
            ),
          ),
        ],
      ),
    );
  }
}
