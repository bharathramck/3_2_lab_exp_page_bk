import numpy as np
import matplotlib.pyplot as plt

def locally_weighted_regression(X, y, query_point, tau):
  """
  Performs locally weighted regression for a single query point.

  Args:
      X: A NumPy array of shape (m, n) representing the features of the data.
      y: A NumPy array of shape (m,) representing the target values.
      query_point: A NumPy array of shape (1, n) representing the query point.
      tau: The bandwidth parameter controlling the influence of nearby data points.

  Returns:
      A NumPy array of shape (n + 1,) representing the estimated coefficients for the local linear regression model.
  """

  m = X.shape[0]
  weights = np.exp(-np.sum((X - query_point) ** 2, axis=1) / (2 * tau**2))
  W = np.diag(weights)

  # Add a bias term to X
  X_b = np.hstack((np.ones((m, 1)), X))

  # Solve for theta using the weighted normal equation
  theta = np.linalg.inv(X_b.T @ W @ X_b) @ (X_b.T @ W @ y)
  return theta

def predict(X, y, query_points, tau):
  """
  Predicts target values for a set of query points using locally weighted regression.

  Args:
      X: A NumPy array of shape (m, n) representing the features of the data.
      y: A NumPy array of shape (m,) representing the target values.
      query_points: A NumPy array of shape (p, n) representing the query points.
      tau: The bandwidth parameter controlling the influence of nearby data points.

  Returns:
      A NumPy array of shape (p,) containing the predicted target values for the query points.
  """

  predictions = []
  for query_point in query_points:
    theta = locally_weighted_regression(X, y, query_point, tau)
    prediction = np.dot(np.array([1, query_point]), theta)
    predictions.append(prediction)
  return np.array(predictions)

# Generate synthetic data
np.random.seed(42)
X = np.sort(5 * np.random.rand(80, 1), axis=0)
y = np.sin(X) + np.random.normal(0, 0.1, X.shape)  # Non-linear relationship with noise

# Define query points
query_points = np.linspace(0, 5, 100)

# Perform locally weighted regression
tau = 0.5  # Bandwidth parameter
predictions = predict(X, y, query_points, tau)

# Plot the results
plt.figure(figsize=(10, 6))
plt.scatter(X, y, color='blue', label='Data Points')
plt.plot(query_points, predictions, color='red', label='Locally Weighted Regression', linewidth=2)
plt.title('Locally Weighted Regression (LWR)')
plt.xlabel('X')
plt.ylabel('y')
plt.legend()
plt.grid()
plt.show()