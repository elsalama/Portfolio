import numpy as np
# Note: do not import additional libraries to implement these functions


import numpy as np


def compute_confusion_matrix(actual, predictions):
    if not isinstance(predictions, np.ndarray):
        predictions = np.full_like(actual, predictions)
    if predictions.shape[0] != actual.shape[0]:
        raise ValueError("predictions and actual must be the same length!")

    true_neg = np.sum((actual == 0) & (predictions == 0))
    false_pos = np.sum((actual == 0) & (predictions == 1))
    false_neg = np.sum((actual == 1) & (predictions == 0))
    true_pos = np.sum((actual == 1) & (predictions == 1))

    return np.array([[true_neg, false_pos], [false_neg, true_pos]])


def compute_accuracy(actual, predictions):
    if not isinstance(predictions, np.ndarray):
        predictions = np.full_like(actual, predictions)
    if predictions.shape[0] != actual.shape[0]:
        raise ValueError("predictions and actual must be the same length!")

    confusion = compute_confusion_matrix(actual, predictions)
    return (confusion[0, 0] + confusion[1, 1]) / np.sum(confusion)


def compute_precision_and_recall(actual, predictions):
    if not isinstance(predictions, np.ndarray):
        predictions = np.full_like(actual, predictions)
    if predictions.shape[0] != actual.shape[0]:
        raise ValueError("predictions and actual must be the same length!")

    confusion = compute_confusion_matrix(actual, predictions)
    true_pos = confusion[1, 1]
    false_pos = confusion[0, 1]
    false_neg = confusion[1, 0]

    precision = true_pos / (true_pos + false_pos) if (true_pos + false_pos) > 0 else np.nan
    recall = true_pos / (true_pos + false_neg) if (true_pos + false_neg) > 0 else np.nan

    return precision, recall


def compute_f1_measure(actual, predictions):
    if not isinstance(predictions, np.ndarray):
        predictions = np.full_like(actual, predictions)
    if predictions.shape[0] != actual.shape[0]:
        raise ValueError("predictions and actual must be the same length!")

    precision, recall = compute_precision_and_recall(actual, predictions)

    if np.isnan(precision) or np.isnan(recall):
        return np.nan
    if precision == 0 and recall == 0:
        return np.nan

    return 2 * (precision * recall) / (precision + recall)
