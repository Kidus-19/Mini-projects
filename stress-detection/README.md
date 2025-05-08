# Stress Level Predictor

This project implements a simple GUI application using Tkinter to predict stress levels based on humidity, temperature, and step count. The predictions are made using a Decision Tree Classifier trained on a dataset.

## Requirements

- Python 3.x
- Libraries:
  - `tkinter`
  - `pandas`
  - `sklearn`
  - `matplotlib`

## Setup

1. **Install Required Libraries**

   You can install the necessary libraries using pip:

   ```bash
   pip install pandas scikit-learn matplotlib
   ```

2. **Dataset**

   Ensure you have a CSV file named `Stress.csv` with the following columns:
   - `Humidity`
   - `Temperature`
   - `Step count`
   - `Stress Level`

3. **Run the Application**

   Save the provided code into a Python file, for example, `stress_predictor.py`, and run it:

   ```bash
   python stress_predictor.py
   ```

## Features

- **Input Fields**: Users can enter humidity, temperature, and step count.
- **Prediction**: Click the "Predict Stress Level" button to get the predicted stress level.
- **Comparison Table**: Displays a comparison of predicted and actual stress levels.
- **All Predictions**: The "Print All Test Cases" button will show predictions for the entire test set with color coding.

## Usage

1. Enter values for humidity, temperature, and step count.
2. Click on "Predict Stress Level" to see the predicted value.
3. Click "Print All Test Cases" to display predictions for all test cases.

## Example

```python
print(predict_stress_level(16.87, 85.87, 50))
```

