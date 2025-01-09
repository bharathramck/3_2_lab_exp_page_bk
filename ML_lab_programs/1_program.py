import pandas as pd

def find_s(training_data):
    """
    Finds the most specific hypothesis from the given training data.

    Args:
        training_data: Pandas DataFrame containing the training data.
                        The last column is assumed to be the class label (0 or 1).

    Returns:
        A list representing the most specific hypothesis.
    """
    num_features = training_data.shape[1] - 1  # Exclude the class label
    specific_hypothesis = ['0'] * num_features

    for index, row in training_data.iterrows():
        if row.iloc[-1] == 1:  # Positive example
            for i in range(num_features):
                if row[i] != specific_hypothesis[i] and specific_hypothesis[i] == '0':
                    specific_hypothesis[i] = row[i]
                elif row[i] != specific_hypothesis[i]:
                    specific_hypothesis[i] = '?'

    return specific_hypothesis

def main():
    filename = input("Enter the path to the training data CSV file: ")

    try:
        training_data = pd.read_csv(filename, header=None)
    except FileNotFoundError:
        print("Error: File not found. Please check the file path and try again.")
        exit()
    except Exception as e:
        print("Error loading file:", e)
        exit()

    hypothesis = find_s(training_data)

    print("In Training Data:")
    print(training_data)

    print("In Most Specific Hypothesis:")
    print(hypothesis)

if __name__ == "__main__":
    main()