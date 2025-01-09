import pandas as pd
import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import plot_tree
from matplotlib.pyplot import plt

# Load the Iris dataset
iris = load_iris()
X = iris.data  # Features
y = iris.target  # Target labels

# Create a DataFrame for better visualization
df = pd.DataFrame(data=np.c_[X, y], columns=iris.feature_names + ['target'])
print("Iris Dataset:")
print(df.head())  # Print the first few rows

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create a Decision Tree Classifier using the entropy criterion
clf = DecisionTreeClassifier(criterion='entropy', random_state=42)

# Train the model on the training data
clf.fit(X_train, y_train)

# Visualize the decision tree
plt.figure(figsize=(12, 8))
plot_tree(clf, filled=True, feature_names=iris.feature_names, class_names=iris.target_names)
plt.title("Decision Tree using ID3 Algorithm")
plt.show()

# Evaluate the model accuracy on the testing data
accuracy = clf.score(X_test, y_test)
print(f"Accuracy of the model: {accuracy:.2f}")

# Classify a new sample
new_sample = np.array([[5.0, 3.5, 1.5, 0.2]])
predicted_class = clf.predict(new_sample)
predicted_class_name = iris.target_names[predicted_class][0]
print(f"The predicted class for the new sample {new_sample.flatten()} is: {predicted_class_name}")