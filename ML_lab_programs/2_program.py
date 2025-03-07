import pandas as pd
from sys import exit

def candidate_elimination(data):
    # Initialize specific and general hypotheses
    specific_hypothesis = ['0'] * (data.shape[1] - 1)  # Assuming the last column is the target
    general_hypothesis = [['?'] * (data.shape[1] - 1)]  # Start with the most general hypothesis

    # Iterate through each training example
    for index, row in data.iterrows():
        if row['Play'] == 'Yes':  # Positive example
            for i in range(len(specific_hypothesis)):
                if specific_hypothesis[i] == '0':  # Initialize
                    specific_hypothesis[i] = row.iloc[i]
                elif specific_hypothesis[i] != row.iloc[i]:  # Generalize if mismatch
                    specific_hypothesis[i] = '?'

            # Remove inconsistent hypotheses from the general hypothesis
            general_hypothesis = [g for g in general_hypothesis if all(
                g[i] == '?' or g[i] == row.iloc[i] or specific_hypothesis[i] == '?'
                for i in range(len(g))
            )]

        else:  # Negative example
            new_general_hypotheses = []
            for i in range(len(specific_hypothesis)):
                if specific_hypothesis[i] == '?':
                    continue  # Cannot specialize further
                elif specific_hypothesis[i] != row.iloc[i]:
                    new_hypothesis = specific_hypothesis.copy()
                    new_hypothesis[i] = '?'
                    new_general_hypotheses.append(new_hypothesis)

            # Add only consistent hypotheses to the general hypothesis
            general_hypothesis.extend([h for h in new_general_hypotheses if all(
                h[j] == '?' or h[j] == row.iloc[j] or specific_hypothesis[j] == '?'
                for j in range(len(h))
            )])

    # Remove overly general hypotheses
    general_hypothesis = [g for g in general_hypothesis if not any(
        all(g[i] == '?' or g[i] == other[i] for i in range(len(g))) and g != other
        for other in general_hypothesis
    )]

    return specific_hypothesis, general_hypothesis

# Load the data
file_path = r'd:\CSEnotes\3-2_sem\ML_Lab\weather_forecast.csv'  # Update with your actual file path
try:
    data = pd.read_csv(file_path)
except FileNotFoundError:
    print(f"Error: File not found at {file_path}")
    exit()

# Check if the necessary columns exist
required_columns = ['Outlook', 'Temperature', 'Humidity', 'Wind', 'Play']
if not all(column in data.columns for column in required_columns):
    print("Error: The dataset must include the following columns:")
    print(required_columns)
    exit()

# Run the Candidate-Elimination algorithm
specific_hypothesis, general_hypothesis = candidate_elimination(data)

# Print the results
print("Specific Hypothesis:", specific_hypothesis)
print("General Hypotheses:", general_hypothesis)
