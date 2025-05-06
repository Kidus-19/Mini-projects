import 'package:flutter/material.dart';
import 'screens/home_screen.dart';

void main() {
  runApp(FitnessTrackerApp());
}

class FitnessTrackerApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Fitness Tracker',
      theme: ThemeData(
        primarySwatch: Colors.green,
      ),
      home: HomeScreen(),
    );
  }
}
