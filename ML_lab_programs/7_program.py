import numpy as np
import pandas as pd
from pgmpy.models import BayesianModel
from pgmpy.estimators import MaximumLikelihoodEstimator
from pgmpy.inference import VariableElimination

# Load the Heart Disease dataset
heart_disease = pd.read_csv('heart.csv')

# Handle missing values (replace '?' with NaN)
heart_disease = heart_disease.replace('?', np.nan)

# Display sample instances
print('Sample instances from the dataset:')
print(heart_disease.head())

# Display attributes and data types
print('\nAttributes and data types:')
print(heart_disease.dtypes)

# Define the structure of the Bayesian Network
model = BayesianModel([
    ('age', 'heartdisease'),
    ('sex', 'heartdisease'),
    ('exang', 'heartdisease'),
    ('cp', 'heartdisease'),
    ('heartdisease', 'restecg'),
    ('heartdisease', 'chol')
])

# Learn CPDs (Conditional Probability Distributions) using Maximum Likelihood Estimator
print('\nLearning CPDs using Maximum Likelihood Estimators...')
model.fit(heart_disease, estimator=MaximumLikelihoodEstimator)

# Inference with the Bayesian Network
print('\nInferencing with Bayesian Network:')
heart_disease_infer = VariableElimination(model)

# Query 1: Probability of Heart Disease given evidence (restecg = 1)
print('\n1. Probability of Heart Disease given evidence (restecg = 1):')
query1 = heart_disease_infer.query(variables=['heartdisease'], evidence={'restecg': 1})
print(query1)

# Query 2: Probability of Heart Disease given evidence (cp = 2)
print('\n2. Probability of Heart Disease given evidence (cp = 2):')
query2 = heart_disease_infer.query(variables=['heartdisease'], evidence={'cp': 2})
print(query2)