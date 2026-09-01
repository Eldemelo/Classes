import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() {
  runApp(const CurrencyConverterApp());
}

class CurrencyConverterApp extends StatelessWidget {
  const CurrencyConverterApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Ethan\'s Currency Converter'),
        ),
        body: const CurrencyConverter(),
      ),
    );
  }
}

class CurrencyConverter extends StatefulWidget {
  const CurrencyConverter({super.key});

  @override
  _CurrencyConverterState createState() => _CurrencyConverterState();
}

class _CurrencyConverterState extends State<CurrencyConverter> {
  final TextEditingController _amountController = TextEditingController();
  String _fromCurrency = 'USD';
  String _toCurrency = 'EUR';
  double _result = 0.0;

  final List<String> _currencies = ['USD', 'EUR', 'GBP', 'INR'];

  Future<void> _convertCurrency() async {
    final double amount = double.parse(_amountController.text);
    final response = await http.get(
        Uri.parse('https://api.exchangerate-api.com/v4/latest/$_fromCurrency'));
    if (response.statusCode == 200) {
      final rates = json.decode(response.body)['rates'];
      setState(() {
        _result = amount * rates[_toCurrency];
      });
    } else {
      throw Exception('Failed to load exchange rates');
    }
  }

  void _clearFields() {
    setState(() {
      _amountController.clear();
      _result = 0.0;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(16.0),
      child: Column(
        children: [
          TextField(
            controller: _amountController,
            decoration: const InputDecoration(
              labelText: 'Enter amount',
            ),
            keyboardType: TextInputType.number,
          ),
          const SizedBox(height: 20),
          const Text("From:"),
          const SizedBox(height: 20),
          DropdownButton<String>(
            value: _fromCurrency,
            onChanged: (String? newValue) {
              setState(() {
                _fromCurrency = newValue!;
              });
            },
            items: _currencies.map<DropdownMenuItem<String>>((String value) {
              return DropdownMenuItem<String>(
                value: value,
                child: Text(value),
              );
            }).toList(),
          ),
          const SizedBox(height: 20),
          const Text("To:"),
          const SizedBox(height: 20),
          DropdownButton<String>(
            value: _toCurrency,
            onChanged: (String? newValue) {
              setState(() {
                _toCurrency = newValue!;
              });
            },
            items: _currencies.map<DropdownMenuItem<String>>((String value) {
              return DropdownMenuItem<String>(
                value: value,
                child: Text(value),
              );
            }).toList(),
          ),
          const SizedBox(height: 20),
          ElevatedButton(
            onPressed: _convertCurrency,
            child: const Text('Convert'),
          ),
          const SizedBox(height: 20),
          ElevatedButton(
            onPressed: _clearFields,
            child: const Text('Clear'),
          ),
          const SizedBox(height: 20),
          Text('Result: $_result'),
        ],
      ),
    );
  }
}
