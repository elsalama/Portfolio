import numpy as np
from src import run
import os
import json


datasets = {
    x: os.path.join('data', x)
    for x in os.listdir('data') if x.endswith('.csv')
}


def test_decision_tree_binary_predict():
    from src.decision_tree import DecisionTree, Node
    attribute_names = ['Outlook', 'Temp', 'Wind']
    decision_tree = DecisionTree(attribute_names=attribute_names)
    root = Node(
        attribute_name="Outlook", attribute_index=0,
        split_value=0.5, branches=[])

    left = Node(
        attribute_name="Temp", attribute_index=1,
        split_value=0.5, branches=[])

    left_left = Node(
        attribute_name=None, attribute_index=None,
        return_value=1, branches=[])

    left_right = Node(
        attribute_name=None, attribute_index=None,
        return_value=0, branches=[])

    right = Node(
        attribute_name=None, attribute_index=None,
        return_value=1, branches=[])

    left.branches = [left_left, left_right]
    root.branches = [left, right]
    decision_tree.tree = root
    examples = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 1, 1], [0, 1, 1]])
    predictions = decision_tree.predict(examples)
    ground_truth = np.array([[1], [0], [1], [1], [0]])

    np.testing.assert_allclose(predictions, ground_truth)


def test_decision_tree_continuous_predict():
    from src.decision_tree import DecisionTree, Node
    attribute_names = ['Wind', 'Temp', 'Outlook']
    examples = np.array([[1, 79.21, 1], [2, 90.56, 0], [7, 88.36, 1], [5, 84.02, 0], [1, 43.77, 0]])
    decision_tree = DecisionTree(attribute_names=attribute_names)
    root = Node(
        attribute_name="Wind", attribute_index=0,
        split_value=np.median(examples[:, 0]), branches=[])

    left = Node(
        attribute_name="Temp", attribute_index=1,
        split_value=np.median(examples[:, 1]), branches=[])

    left_left = Node(
        attribute_name=None, attribute_index=None,
        return_value=1, branches=[])

    left_right = Node(
        attribute_name=None, attribute_index=None,
        return_value=0, branches=[])

    right = Node(
        attribute_name=None, attribute_index=None,
        return_value=0, branches=[])

    left.branches = [left_left, left_right]
    root.branches = [left, right]
    decision_tree.tree = root

    predictions = decision_tree.predict(examples)
    ground_truth = np.array([[1], [0], [0], [0], [1]])

    np.testing.assert_allclose(predictions, ground_truth)


def test_information_gain_discrete():
    from src import load_data
    from src import information_gain

    _features, _targets, _attribute_names = load_data('data/play-tennis.csv')
# focus to fix the first problem the split is not correctly done it is missing the outlook in the feature. 
# fix train test split you are not giving the outlook feature
    good = []
    for feature in ["Humidity", "Outlook"]:
        idx = _attribute_names.index(feature)
        good.append(round(information_gain(_features, idx, _targets), 3))

    bad = []
    for feature in ["Wind", "Temperature"]:
        idx = _attribute_names.index(feature)
        bad.append(round(information_gain(_features, idx, _targets), 3))

    assert good[0] >= good[1] > bad[0] >= bad[1], good + bad

    good = np.array(good).reshape(2, 1)
    bad = np.array(bad).reshape(1, 2)
    assert np.all(good > bad), (good - bad)


def test_information_gain_continuous():
    from src import load_data
    from src import information_gain

    _features, _targets, _attribute_names = load_data('data/circles-easy.csv')
    iGX1 = information_gain(_features, 0, _targets)
    iGX2 = information_gain(_features, 1, _targets)

    assert iGX1 > iGX2, f"Expected iGX1={iGX1:.3f} > iGX2={iGX2:.3f}"

    _features, _targets, _attribute_names = load_data('data/noisy.csv')
    iGX1 = information_gain(_features, 0, _targets)
    iGX2 = information_gain(_features, 1, _targets)
    assert iGX1 < iGX2, f"Expected iGX1={iGX1:.3f} < iGX2={iGX2:.3f}"

    _features, _targets, _attribute_names = load_data('data/circles-hard.csv')
    iGX1 = information_gain(_features, 0, _targets)
    iGX2 = information_gain(_features, 1, _targets)

    msg = f"Expected iGX1={iGX1:.3f} and iGX2={iGX2:.3f} to be very small"
    assert iGX2 < 0.01 and iGX1 < 0.01, msg


def help_decision_tree_run(order):
    goals = {
        'xor-easy.csv': {1.0: 1.0},
        'xor-hard.csv': {1.0: 0.8, 0.8: 1.0},
        'xor-noise.csv': {1.0: 1.0, 0.8: 0.75, 0.9: 0.5},
        'ivy-league.csv': {1.0: 1.0, 0.8: 0.6,},
        'majority-rule.csv': {1.0: 1.0, 0.8: 0.7,},
        'circles-hard.csv': {1.0: 0.7,},
        'circles-easy.csv': {1.0: 0.8,},
        'blobs.csv': {1.0: 0.8, 0.8: 0.9,},
    }

    learner_type = 'decision_tree'
    for key in order:
        for fraction, goal in goals[key].items():
            accuracy, learner = run(datasets.get(key), learner_type, fraction)
            message = f"On {key} dataset with fraction {fraction}, "
            message += f"expected {goal:.2f} but got {accuracy:.3f}"
            print(message)
            if accuracy < goal:
                print("Failed test with model:")
                learner.visualize()
                assert accuracy >= goal, message


def test_decision_tree_run1():
    order = [
        'xor-easy.csv',
        'ivy-league.csv',
        'blobs.csv',
        'circles-easy.csv',
    ]

    help_decision_tree_run(order)


def test_decision_tree_run2():
    order = [
        'majority-rule.csv',
        'xor-hard.csv',
        'xor-noise.csv',
        'circles-hard.csv',
    ]

    help_decision_tree_run(order)
