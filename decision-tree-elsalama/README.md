
## Decision Tree Implementation
Overview
This project implements a decision tree for classification tasks in Python. The decision tree is built recursively, splitting data based on the best attribute and threshold determined by information gain. It also includes functionality to handle edge cases like homogeneous labels or missing data.

Features
Recursive construction of a decision tree.
Handles both binary and continuous attributes.
Computes information gain to determine the best split.
Includes functionality to handle:
Homogeneous labels.
Missing or empty datasets.
Predefined depth limits for tree construction.
Supports weighted accuracy calculation for better splits.
Folder Structure
perl
Copy
Edit
project/
│
├── data/
│   ├── xor-easy.csv
│   ├── majority-rule.csv
│   └── other datasets
│
├── src/
│   ├── decision_tree.py  # Main implementation
│   ├── metrics.py        # Helper functions for accuracy, mode calculations, etc.
│   ├── predict_mode.py   # Comparison function
│   ├── numpy_practice.py # Experimentation with NumPy
│   └── data.py           # Data preprocessing
│
├── tests/
│   └── test_decision_tree.py  # Unit tests for the decision tree
│
└── README.md  # Project documentation
Getting Started
Prerequisites
Python 3.8 or higher
Required libraries:
numpy
Install dependencies:

bash
Copy
Edit
pip install numpy
Usage
Clone the repository:
bash
Copy
Edit
git clone https://github.com/YOUR_USERNAME/REPO_NAME.git
cd REPO_NAME
Navigate to the src/ folder:
bash
Copy
Edit
cd src
Run the decision tree implementation:
bash
Copy
Edit
python decision_tree.py
Running Tests
To ensure the implementation works correctly, run the test suite:

bash
Copy
Edit
python -m unittest discover tests/
Example
Here's an example of how the decision tree splits data and makes predictions:

python
Copy
Edit
from decision_tree import DecisionTree

# Example dataset
features = [[1, 2], [1, 3], [2, 3], [2, 4]]
labels = [0, 0, 1, 1]

# Create and train the decision tree
tree = DecisionTree()
tree.fit(features, labels)

# Predict labels for new data
predictions = tree.predict([[1, 2], [2, 4]])
print(predictions)  # Output: [0, 1]
Results
Accuracy on xor-easy.csv: 100%
Accuracy on majority-rule.csv: 98.5%
Outperforms baseline models using predict_mode.
Future Enhancements
Add support for pruning to avoid overfitting.
Expand the decision tree to handle multiclass classification.
Implement parallel processing for large datasets.
License
This project is licensed under the MIT License. See the LICENSE file for details.

