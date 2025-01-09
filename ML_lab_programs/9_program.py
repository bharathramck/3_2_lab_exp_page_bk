import numpy as np
import pandas as pd
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

# Load the Iris dataset
iris = load_iris()

# Separate features (X) and labels (y)
X = iris.data
y = iris.target

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create the K-NN classifier (k=3 neighbors by default)
k = 3  # You can adjust this value
knn = KNeighborsClassifier(n_neighbors=k)

# Train the classifier on the training data
knn.fit(X_train, y_train)

# Make predictions on the test set
y_pred = knn.predict(X_test)

# Evaluate the accuracy
accuracy = accuracy_score(y_test, y_pred)
print(f'Accuracy: {accuracy * 100:.2f}%')

# Print some correct and incorrect predictions (optional)
print("\nCorrect Predictions:")
for i in range(len(y_test)):
    if y_pred[i] == y_test[i]:
        print(f"Predicted: {iris.target_names[y_pred[i]]}, Actual: {iris.target_names[y_test[i]]}")

print("\nWrong Predictions:")
for i in range(len(y_test)):
    if y_pred[i] != y_test[i]:
        print(f"Predicted: {iris.target_names[y_pred[i]]}, Actual: {iris.target_names[y_test[i]]}")