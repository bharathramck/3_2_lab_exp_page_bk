import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans, GaussianMixture
from matplotlib.pyplot import scatter, title, xlabel, ylabel, show
from sklearn.metrics import silhouette_score, adjusted_rand_score

# Load the dataset
data = pd.read_csv('heart_disease.csv')

# Display the first few rows of the data
print(data.head())

# Handle missing values (optional)
# This code replaces missing values with the mean of each column. You might want to consider other imputation techniques.
data.fillna(data.mean(), inplace=True)

# Normalize the data (optional, but often beneficial for clustering)
scaler = StandardScaler()
scaled_data = scaler.fit_transform(data)

# K-Means Clustering

# Choose the number of clusters (k)
k = 3  # Adjust this value based on your data and desired number of clusters

# Create a KMeans model with the specified number of clusters and a random state for reproducibility
kmeans = KMeans(n_clusters=k, random_state=42)

# Fit the model to the normalized data
kmeans.fit(scaled_data)

# Get the cluster labels for each data point
kmeans_labels = kmeans.labels_

# Visualize the clusters (assuming 2D features)
scatter(scaled_data[:, 0], scaled_data[:, 1], c=kmeans_labels, cmap='viridis')
title('K-Means Clustering')
xlabel('Feature 1')
ylabel('Feature 2')
show()

# Gaussian Mixture Model (GMM) Clustering

# Create a GMM model with the same number of clusters as KMeans
gmm = GaussianMixture(n_components=k, random_state=42)

# Fit the GMM model to the normalized data
gmm.fit(scaled_data)

# Get the cluster labels for each data point
gmm_labels = gmm.predict(scaled_data)

# Visualize the clusters (assuming 2D features)
scatter(scaled_data[:, 0], scaled_data[:, 1], c=gmm_labels, cmap='viridis')
title('EM (GMM) Clustering')
xlabel('Feature 1')
ylabel('Feature 2')
show()

# Evaluation

# Silhouette Score (measures how well data points are assigned to clusters)
kmeans_silhouette = silhouette_score(scaled_data, kmeans_labels)
gmm_silhouette = silhouette_score(scaled_data, gmm_labels)

# Adjusted Rand Index (compares clustering labels with ground truth, if available)
# Assuming you have a 'target' column with true labels in your data:
# true_labels = data['target']
# ari_kmeans = adjusted_rand_score(true_labels, kmeans_labels)
ari_gmm = adjusted_rand_score(true_labels, gmm_labels)  # Assuming 'true_labels' is available

print(f'K-Means Silhouette Score: {kmeans_silhouette}')
print(f'GMM Silhouette Score: {gmm_silhouette}')
# print(f'k-Means ARI: {ari_kmeans}')  # Print if 'true_labels' is available
print(f'GMM ARI: {ari_gmm}')