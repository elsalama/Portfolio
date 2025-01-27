import numpy as np
from src import run
import os
import json


datasets = {
    x: os.path.join('data', x)
    for x in os.listdir('data') if x.endswith('.csv')
}


def test_predict_mode():
    goals = {
      'ivy-league.csv': {1.0: 0.5},
      'majority-rule.csv': {1.0: 0.6},
      'circles-easy.csv': {1.0: 0.6},
      'blobs.csv': {1.0: 0.55},
    }

    learner_type = 'predict_mode'
    for key in goals:
        for fraction, goal in goals[key].items():
            accuracy, learner = run(datasets.get(key), learner_type, fraction)
            message = f"On {key} dataset with fraction {fraction}, "
            message += f"expected {goal:.2f} but got {accuracy:.3f}"
            if accuracy < goal:
                print("Failed test with model:")
                learner.visualize()
                assert accuracy >= goal, message


def test_comparisons():

    evaluations = {
        "dt0.7": {
            "data_path": "majority-rule.csv", "fraction": 0.7, "method": "decision_tree"},
        "dt0.9": {
            "data_path": "majority-rule.csv", "fraction": 0.9, "method": "decision_tree"},
        "dt1.0": {
            "data_path": "majority-rule.csv", "fraction": 1.0, "method": "decision_tree"},
        "pm0.7": {
            "data_path": "majority-rule.csv", "fraction": 0.7, "method": "predict_mode"},
        "pm1.0": {
            "data_path": "majority-rule.csv", "fraction": 1.0, "method": "predict_mode"},

    }

    comparisons = [
        # Decision tree beats predict mode on majority rule when both are
        # trained and tested on the entire dataset.
        # Decision tree should be able to memorize the entire dataset.
        ("dt1.0", "pm1.0"),

        # Decision tree with 90/10 split beats decision tree on 70/30 split.
        # The algorithm is able to learn a tree from 90% that generalizes better
        # to the remaining 30%.
        ("dt0.9", "dt0.7"),

        # predict_mode with 70/30 split beats predict_mode trained and tested
        # on entire dataset.
        # This holds because of how the labels are arranged in the first 70%
        # versus the final 30%.
        ("pm0.7", "pm1.0"),
    ]

    for i, comparison in enumerate(comparisons):

        a = evaluations[comparison[0]]
        data_path_a = datasets.get(a["data_path"])
        method_a = a["method"]
        kwargs_a = a.get("kwargs", {})
        acc_a, learner_a = run(data_path_a, method_a, a["fraction"], **kwargs_a)

        b = evaluations[comparison[1]]
        data_path_b = datasets.get(b["data_path"])
        method_b = b["method"]
        kwargs_b = b.get("kwargs", {})
        acc_b, learner_b = run(data_path_b, method_b, b["fraction"], **kwargs_b)

        if method_a != method_b:
            a, b = method_a, method_b
        else:
            a, b = kwargs_a, kwargs_b

        if acc_a <= acc_b:
            print(f"{a} model visualization:")
            learner_a.visualize()
            print(f"{b} model visualization:")
            learner_b.visualize()
            message = f"{a} should beat {b} in comparion #{i + 1}"
            message += f", but {acc_a:.3f} <= {acc_b:.3f}."
            message += " See tests/test_experiment.py for details"
            assert acc_a > acc_b, message
