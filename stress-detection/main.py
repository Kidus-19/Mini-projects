
import tkinter as tk
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn import tree
from tkinter import messagebox
from tkinter import ttk
from sklearn.metrics import accuracy_score
import pandas as pd
import matplotlib.pyplot as plt
import tkinter.font as font

data = pd.read_csv("Stress.csv")

X = data.drop('Stress Level', axis=1)  # Features
y = data['Stress Level']  # Target

X = pd.get_dummies(X)
#  Split the dataset into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

#  Initialize the Decision Tree Classifier
clf = tree.DecisionTreeClassifier()

#  Train the model using the training sets
clf.fit(X_train, y_train)

#  Make predictions on the testing set
y_pred = clf.predict(X_test)

#  To see the decision tree
tree.plot_tree(clf)
# plt.savefig('tree.png')

#  Function to predict stress level based on humidity, temperature, and step count
def predict_stress_level(humidity, temperature, step_count):
    # Create a new DataFrame from the input values
    input_data = pd.DataFrame({
        'Humidity': [humidity],
        'Temperature': [temperature],
        'Step count': [step_count]
    })

    # Use the trained model to predict the stress level
    predicted_stress_level = clf.predict(input_data)

    return predicted_stress_level

# Test the function
print(predict_stress_level(16.87,85.87,50))
print("Accuracy:", accuracy_score(y_test, y_pred))
def predict():
    humidity = float(humidity_entry.get())
    temperature = float(temperature_entry.get())
    step_count = int(step_count_entry.get())
    stress_level = predict_stress_level(humidity, temperature, step_count)
    actual_stress_level ="" # replace this with the actual stress level
    comparison_table.insert("", "end", values=(humidity, temperature, step_count, stress_level[0], actual_stress_level))

# Create the main window
root = tk.Tk()
root.title("Stress Level Predictor")

# Set a custom font
myFont = font.Font(family='Helvetica', size=12, weight='bold')

# Create entry fields for Humidity, Temperature, and Step count
for i, text in enumerate(["Humidity", "Temperature", "Step count"]):
    tk.Label(root, text=text, font=myFont).grid(row=i, padx=10, pady=10)
    entry = tk.Entry(root)
    entry.grid(row=i, column=1, padx=10, pady=10)
    if text == "Humidity":
        humidity_entry = entry
    elif text == "Temperature":
        temperature_entry = entry
    else:
        step_count_entry = entry

# Create a button that will call the predict function when clicked
predict_button = tk.Button(root, text="Predict Stress Level", command=predict, font=myFont, bg='light blue')
predict_button.grid(row=3, column=0, columnspan=2, padx=10, pady=10)

# Create a table to display the comparison of predicted and actual stress levels
comparison_table = ttk.Treeview(root, columns=("Humidity", "Temperature", "Step count", "Predicted", "Actual"), show="headings")
for column in comparison_table['columns']:
    comparison_table.heading(column, text=column)
comparison_table.grid(row=4, column=0, columnspan=2, padx=10, pady=10)

# Create a table to display the comparison of predicted and actual stress levels
comparison_table = ttk.Treeview(root, columns=("Humidity", "Temperature", "Step count", "Predicted", "Actual"), show="headings")
comparison_table.heading("Humidity", text="Humidity")
comparison_table.heading("Temperature", text="Temperature")
comparison_table.heading("Step count", text="Step count")
comparison_table.heading("Predicted", text="Predicted")
comparison_table.heading("Actual", text="Actual")
comparison_table.grid(row=4, column=0, columnspan=2)
def print_all_predictions():
    # Make predictions on the entire test set
    y_pred_all = clf.predict(X_test)

    # Insert each test case prediction and actual value into the comparison table
    for i in range(len(y_test)):
        # Determine the color based on the correctness of the prediction
        color = 'green' if y_pred_all[i] == y_test.iloc[i] else 'red'
        
        # Insert the row with the determined color
        comparison_table.insert("", "end", values=(X_test.iloc[i]['Humidity'], X_test.iloc[i]['Temperature'], X_test.iloc[i]['Step count'], y_pred_all[i], y_test.iloc[i]), tags=('correct' if color == 'green' else 'incorrect',))

    # Configure the tag to change the background color
    comparison_table.tag_configure('correct', background='lime')
    comparison_table.tag_configure('incorrect', background='red')

# Create a button that will call the print_all_predictions function when clicked
print_all_button = tk.Button(root, text="Print All Test Cases", command=print_all_predictions , font=myFont, bg='light blue')
print_all_button.grid(row=5, column=0, columnspan=2)
# Run the event loop
root.mainloop()
plt.show()