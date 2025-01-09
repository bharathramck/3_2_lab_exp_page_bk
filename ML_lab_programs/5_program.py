import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score

# Load the dataset from a CSV file
data = pd.read_csv('data.csv')

# Separate features and labels
X = data[['feature1', 'feature2']]  # Assuming 'feature1' and 'feature2' are your feature columns
y = data['label']  # Assuming 'label' is your target column

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create a Gaussian Naive Bayes classifier
model = GaussianNB()

# Train the model on the training data
model.fit(X_train, y_train)

# Make predictions on the test data
y_pred = model.predict(X_test)

# Evaluate the model accuracy using accuracy_score
accuracy = accuracy_score(y_test, y_pred)
print(f'Accuracy: {accuracy * 100:.2f}%')

# Example of predicting on new data
new_data = pd.DataFrame({
    'feature1': [1, 0],
    'feature2': [0, 1]
})

predictions = model.predict(new_data)
print("Predictions for new data:", predictions)