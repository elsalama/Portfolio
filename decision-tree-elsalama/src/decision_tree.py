import numpy as np
from src.numpy_practice import find_mode
from src.metrics import compute_accuracy

class Node:
    def __init__(self, return_value=None, split_value=None,
                 attribute_name=None, attribute_index=None, branches=None):
        """
        Implements a tree structure with multiple branches at each node.

        Args:
            return_value (int or None): Class prediction for leaf nodes.
            split_value (float or None): Split value for non-leaf nodes.
            attribute_name (str or None): Attribute name for the split.
            attribute_index (int or None): Index of the attribute to split on.
            branches (list): List of child Node objects.
        """
        self.return_value = return_value
        self.split_value = split_value
        self.attribute_name = attribute_name
        self.attribute_index = attribute_index
        self.branches = branches or []

class DecisionTree:
    def __init__(self, attribute_names):
        """
        Decision tree implementation using the ID3 algorithm.

        Args:
            attribute_names (list): Names of attributes (features).
        """
        self.attribute_names = attribute_names
        self.tree = None

    def _check_input(self, features):
        if features.shape[1] != len(self.attribute_names):
            raise ValueError(
                f"Feature dimension mismatch: {features.shape[1]} features provided, but expected {len(self.attribute_names)} attribute names."
            )

    def visualize(self, branch=None, level=0):
        if branch is None:
            branch = self.tree
        self._visualize_helper(branch, level)

        if branch.branches:
            left, right = branch.branches
            if left is not None:
                self.visualize(left, level + 1)

            if left is not None and right is not None:
                print(f"{level}: {'  ' * level}else:")

            if right is not None:
                self.visualize(right, level + 1)

    def _visualize_helper(self, tree, level):
        indent = "  " * level
        if not tree.branches:
            print(f"{level}: {indent}Predict {tree.return_value}")
        else:
            print(f"{level}: {indent}if {tree.attribute_name} <= {tree.split_value:.1f}:")

    def fit(self, features, labels):
        self._check_input(features)
        self.tree = self._create_tree(features, labels, [], find_mode(labels))

    def _create_tree(self, features, labels, used_attributes, default):
        # Stop if no data remains
        if len(labels) == 0:
            return Node(return_value=default)

        # Stop if all labels are the same
        unique_labels = np.unique(labels)
        if len(unique_labels) == 1:
            return Node(return_value=unique_labels[0])

        # Stop if all attributes have been used
        if len(used_attributes) == len(self.attribute_names):
            return Node(return_value=find_mode(labels))

        # Select the best attribute
        best_gain, best_attribute = -1, None
        for attr in range(features.shape[1]):
            if attr in used_attributes:
                continue
            gain = information_gain(features, attr, labels)
            if gain > best_gain:
                best_gain, best_attribute = gain, attr

        # Check if no meaningful split is found
        if best_gain <= 0 and len(used_attributes) == len(self.attribute_names):
            # Stop only if no attributes are left to use
            return Node(return_value=find_mode(labels))

        # Partition data
        attribute_values = features[:, best_attribute]  # Values for the best attribute
        if np.all(np.isin(attribute_values, [0, 1])):  # Binary attribute
            split_value = 0.5
        else:  # Continuous attribute
            split_value = np.median(attribute_values)

        # Split features and labels
        left_mask = attribute_values <= split_value
        right_mask = attribute_values > split_value

        left_features, left_labels = features[left_mask], labels[left_mask]
        right_features, right_labels = features[right_mask], labels[right_mask]

        default_left = find_mode(left_labels) if len(left_labels) > 0 else default
        default_right = find_mode(right_labels) if len(right_labels) > 0 else default

        # Debug print statements
        print(f"Splitting on attribute '{self.attribute_names[best_attribute]}' with split value {split_value}")
        print(f"Left partition: {len(left_labels)} examples")
        print(f"Right partition: {len(right_labels)} examples")

        # Recurse on child nodes
        left_child = self._create_tree(
            left_features, left_labels, used_attributes + [best_attribute],
            default_left,
        )
        right_child = self._create_tree(
            right_features, right_labels, used_attributes + [best_attribute],
            default_right,
        )

        return Node(
            attribute_name=self.attribute_names[best_attribute],
            attribute_index=best_attribute,
            split_value=split_value,
            branches=[left_child, right_child]
        )




    """ def _find_best_split(self, feature_column, labels):
        unique_values = np.unique(feature_column)
        if len(unique_values) == 1:
            # No meaningful split possible if all feature values are the same
            return float('-inf'), None

        best_gain = float('-inf')
        best_split = None

        for split in unique_values:
            # Split the data
            left_mask = feature_column <= split
            right_mask = ~left_mask

            # If either side is empty, skip this split
            if not left_mask.any() or not right_mask.any():
                continue

            # Compute accuracy before and after the split
            accuracy_before_split = compute_accuracy(labels, find_mode(labels))
            left_accuracy = compute_accuracy(labels[left_mask], find_mode(labels[left_mask])) if left_mask.any() else 1.0
            right_accuracy = compute_accuracy(labels[right_mask], find_mode(labels[right_mask])) if right_mask.any() else 1.0

            # Compute weighted accuracy
            n = len(labels)
            n_left = np.sum(left_mask)
            n_right = np.sum(right_mask)
            weighted_accuracy = (n_left / n * left_accuracy) + (n_right / n * right_accuracy)

            # Calculate gain
            gain = weighted_accuracy - accuracy_before_split

            # Update best split if gain improves
            if gain > best_gain:
                best_gain = gain
                best_split = split 

        return best_gain, best_split """


    def predict(self, features):
        """
        Predict labels for the given features.

        Args:
            features (np.array): NxK numpy array of examples.

        Returns:
            np.array: Nx1 numpy array of predicted labels.
        """
        self._check_input(features)  # Ensure input is 2D
        predictions = []

        for i in range(features.shape[0]):
            node = self.tree
            while node.return_value is None:
                value = features[i, node.attribute_index]
                if value <= node.split_value:
                    node = node.branches[0]
                else:
                    node = node.branches[1]
            predictions.append(node.return_value)

        return np.vstack(predictions)  # Return Nx1 array


def information_gain(features, attribute_index, labels):
    """
    Compute the information gain (accuracy gain) for splitting on a given attribute index.

    Args:
        features (np.array): numpy array containing features (attributes) for each example.
        attribute_index (int): which column of features to use.
        labels (np.array): numpy array containing labels corresponding to each example.

    Returns:
        information_gain (float): Information (accuracy) gain if features are split on the attribute_index.
    """
    # Compute accuracy before the split
    accuracy_before = compute_accuracy(labels, find_mode(labels))
    print(f"Accuracy Before Split: {accuracy_before}")

    # Determine if the attribute is binary or continuous
    attribute_values = features[:, attribute_index]
    unique_values = np.unique(attribute_values)
    print(f"Attribute Values for Index {attribute_index}: {attribute_values}")
    print(f"Unique Values: {unique_values}")

    if len(unique_values) == 2 and set(unique_values).issubset({0, 1}):
        # Binary attribute: split by 0s and 1s
        print("Binary Attribute Detected")
        left_mask = attribute_values == 0
        right_mask = attribute_values == 1
    else:
        # Continuous attribute: split at median
        median = np.median(attribute_values)
        print(f"Continuous Attribute: Median = {median}")
        left_mask = attribute_values <= median
        right_mask = attribute_values > median

    # Split into subsets
    left_labels = labels[left_mask]
    right_labels = labels[right_mask]
    print(f"Subset Left: Values = {attribute_values[left_mask]}, Labels = {left_labels}")
    print(f"Subset Right: Values = {attribute_values[right_mask]}, Labels = {right_labels}")

    # Handle empty subsets
    accuracy_left = compute_accuracy(left_labels, find_mode(left_labels)) if len(left_labels) > 0 else 1.0
    accuracy_right = compute_accuracy(right_labels, find_mode(right_labels)) if len(right_labels) > 0 else 1.0
    print(f"Accuracy Left: {accuracy_left}, Accuracy Right: {accuracy_right}")

    # Compute weighted accuracy after the split
    size_left = len(left_labels)
    size_right = len(right_labels)
    total_size = size_left + size_right
    print(f"Sizes -> Left: {size_left}, Right: {size_right}, Total: {total_size}")

    accuracy_after = ((size_left / total_size) * accuracy_left +
                      (size_right / total_size) * accuracy_right)
    print(f"Accuracy After Split: {accuracy_after}")

    # Compute information gain
    gain = accuracy_after - accuracy_before
    print(f"Information Gain: {gain}")

    return gain



if __name__ == '__main__':
    print("Decision tree implementation.")
    # XOR-easy data
    features = np.array([[1, 1], [0, 0], [1, 0], [0, 1]])
    labels = np.array([0, 0, 1, 1])
    attribute_names = ["A", "B"]

    # Initialize the DecisionTree
    tree = DecisionTree(attribute_names)

    # Train the decision tree
    tree.fit(features, labels)

    # Visualize the decision tree
    print("\nVisualizing the Decision Tree for xor-easy.csv:")
    tree.visualize()
