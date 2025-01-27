import numpy as np
import pandas as pd

def load_data(data_path):
    """
    Load data from a CSV file.

    Args:
        data_path (str): Path to the CSV file.

    Returns:
        features (np.array): NxK numpy array of features.
        labels (np.array): Nx1 numpy array of labels.
        attribute_names (list): List of feature names (headers).
    """
    if data_path.endswith('.gz'):
        df = pd.read_csv(data_path, compression='gzip')
    else:
        df = pd.read_csv(data_path)

    feature_columns = [col for col in df.columns if col != "class"]
    features = df[feature_columns].to_numpy()
    labels = df[["class"]].to_numpy()

    return features, labels, feature_columns

def train_test_split(features, labels, fraction):
    """
    Split the data into training and testing sets deterministically.

    Args:
        features (np.array): NxK numpy array of features.
        labels (np.array): Nx1 numpy array of labels.
        fraction (float): Fraction of data to use for training.

    Returns:
        train_features (np.array): Training features (MxK).
        train_labels (np.array): Training labels (Mx1).
        test_features (np.array): Testing features ((N-M)xK).
        test_labels (np.array): Testing labels ((N-M)x1).
    """
    if not (0.0 <= fraction <= 1.0):
        raise ValueError("Fraction must be between 0.0 and 1.0!")

    if fraction == 1.0:
        return features, labels, features, labels

    M = int(features.shape[0] * fraction)
    train_features, train_labels = features[:M], labels[:M]
    test_features, test_labels = features[M:], labels[M:]

    return train_features, train_labels, test_features, test_labels

def cross_validation(features, labels, n_folds):
    """
    Split the data into `n_folds` groups for cross-validation.

    Args:
        features (np.array): NxK numpy array of features.
        labels (np.array): Nx1 numpy array of labels.
        n_folds (int): Number of folds for cross-validation.

    Returns:
        cv_splits (list): List of tuples (train_features, train_labels, test_features, test_labels).
    """
    if n_folds < 1:
        raise ValueError("Number of folds must be at least 1!")

    if n_folds == 1:
        return [(features, labels, features, labels)]

    n_samples = features.shape[0]
    fold_size = n_samples // n_folds
    cv_splits = []

    for i in range(n_folds):
        start_idx = i * fold_size
        end_idx = start_idx + fold_size if i < n_folds - 1 else n_samples

        test_features = features[start_idx:end_idx]
        test_labels = labels[start_idx:end_idx]

        train_features = np.concatenate([features[:start_idx], features[end_idx:]])
        train_labels = np.concatenate([labels[:start_idx], labels[end_idx:]])

        cv_splits.append((train_features, train_labels, test_features, test_labels))

    return cv_splits

if __name__ == "__main__":
    print("Data handling functions.")
