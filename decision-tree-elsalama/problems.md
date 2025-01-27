## Instructions

There are 18 points possible for this assignment. 2 points are for the setup,
11 points for the code, and 5 points for the free-response questions. The setup
portion is due earlier than the other pieces -- all deadlines are on Canvas.
Please carefully read this entire README before starting the assignment.

### Setup (2 points)

The setup for this assignment requires passing the `test_setup` cases:
`test_setup_netid` and `test_setup_password`.

To pass `test_setup_netid`, all you need to do is put your NetID in the `netid`
file.

To pass `test_setup_password`, please follow the instructions written in
`tests/test_a_setup.py` as documentation for the `test_setup_password()`
function.

The purpose of these test cases is to make sure we're able to automatically
aggregate and grade your work. The autograder isn't sentient and can't fix your
mistakes for you -- these two setup points reward you for making it easy for us
to grade your work. Your subsequent commits should also pass the `test_setup`
tests. If you delete your Net ID or if your code has syntax errors, the
autograder may give you a zero. If you make a mistake that requires us to
manually regrade your code or if we cannot download your PDFs from Canvas, you
may lose these setup points (and possibly other points).

### Coding (11 points)

You need to write code in every function in `src/` that raises a
`NotImplementedError` exception. Your code is graded automatically using the
test cases in `tests/`.  To see what your grade is going to be, you can run
`python -m pytest`; make sure you have installed the packages from
`requirements.txt` first. If the autograder says you get 100/100, it means you
get all 11 points.

For the numpy practice problems in `src/numpy_practice.py`, pay extra attention
to the docstring. The tests will make you implement it using certain numpy
functions, and will expect you to write each function in only one or two lines
of code. To enforce that you solve the test with the requisite number of lines
of code, we're checking to make sure that you haven't imported any additional
packages and that you haven't modified the docstrings we provide.

For this and all subsequent assignments, the test cases build on and sometimes
depend on each other. We **strongly recommend** that you implement them in the
order they appear in `tests/rubric.json`. That file also allows you to see how
many points each test is worth and which other tests it may depend on. 

### Free response (5 points)

You will upload your answers to free-response questions to Canvas.

There are four free response questions. Your answer to each should be in its
own PDF file, titled `qYYY.pdf` where `YYY` is the number of the question. So
your answer to question 1 should be in a file named `q1.pdf` and your answer to
question 2 should be in a separate file named `q2.pdf`. For questions with
multiple parts, put all parts in the single PDF and just clearly label where
each part begins.

*Do not identify yourself in these PDFs* -- we will grade your work anonymously
using only your netid in the filenames. We may deduct points if you include
your name or Net ID in the content of these PDFs.

When you upload a file multiple times to update your work, Canvas will
automatically rename your file by appending a version number. For example,
`q2.pdf` would get renamed to `q2-1.pdf`, `q2-2.pdf`, etc. Don't worry about
this. We'll download your answers automatically, looking at only the first
integer in the title. However, please don't name your files something like
`hw1_q2.pdf`; just `q2.pdf` is fine.

## Free response questions

### Question 1 (1 point)

The ID3 algorithm we implemented is relatively simple, in that it has
no hyperparameters (i.e., design choices about the algorithm that need to be
made before running it on a given dataset). Read the [scikit-learn
DecisionTreeClassifier documentation](
https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeClassifier.html#sklearn.tree.DecisionTreeClassifier)
and read through some of the hyperparameters that the model allows
you to adjust. Pick one of the following hyperparameters:

- `min_samples_split`
- `max_features`
- `max_leaf_nodes`
- `min_impurity_decrease`

For each hyperparameter you choose, give a one-sentence explanation of what
it does to affect the kinds of trees that the algorithm learns.
Then, describe whether a small or large value for this hyperparameter
is more likely to cause the tree to *overfit*.

An example answer to this question for the `max_depth` hyperparameter,
(which you aren't allowed to use), might look like:

> The `max_depth` argument controls the maximum depth (longest path from the
> root to any leaf) of the tree. Using a large value of `max_depth` is more
> likely to overfit, because if the tree gets so deep that each leaf only
> corresponds to a single training example, we wouldn't expect it to generalize
> well to new unseen test data.

### Question 2 (1 point)

Look at the formulas for the Equalized Odds and Demographic Parity metrics.
We discussed these in lecture, or you can refer to
[Wikipedia](https://en.wikipedia.org/wiki/Fairness_(machine_learning)#Definitions_based_on_predicted_outcome).
Note that on Wikipedia, these metrics are framed as equalities -- when a
classifier is not fair, such an equality will not hold.  Then, for each metric,
answer the following questions:

* What do the variables in the formula mean? 
* In your own words, what is the formula doing?

### Question 3 (2 points)

This winter, computer science faculty received over 1,600 requests for
permission to enroll in a class. These require manual approval to determine
whether a student meets the class's prerequisites.  Suppose I decide to train
two machine learning models to classify whether a given student should be given
permission to enroll in CS349, based on the information they provided in their
request. Imagine that space is not an issue and the classroom has infinitely
many seats.

We want to use a model that will be fair with respect to a students' major; we
don't want students from major A to be given preference over students from
major B.  Suppose model 1 and model 2 are both equally accurate (they agree with my
manual approval decisions 90% of the time). However, with respect to students' majors,
suppose model 1 is fairer than model 2 according to **Equalized Odds**, but
model 2 is fairer than model 1 according to **Demographic Parity**. 

* a. Explain in as simple terms as you can: Why is it possible that two models
can have the same accuracy but one can be more fair than the other?

* b. Explain in as simple terms as you can: Why is it possible that two fairness
metrics can disagree about which of two models is more fair?

* c. If you were trying to decide which classifier to use, what additional
questions might you ask about the dataset to decide whether we should choose
Equalized Odds or Demographic Parity?

* d. Suppose we have a third model (also 90% accurate) that is less fair than model
1 in terms of Equalized Odds and less fair than model 2 in terms of Demographic
Parity. Invent a situation where you still might prefer model 3 because neither
of these fairness metrics capture the aspects you think matter most. Try to be as
specific as you can in describing this situation.

### Question 4 (1 point)

In the ID3 algorithm, we recursively build a decision tree by choosing an
attribute to split that will maximize information gain. Suppose we wanted to
incorporate Equalized Odds or Demographic Parity into our decision tree
learning algorithm.

* a. How might this work? You don't need to write an entire algorithm,
but try to provide as many specific details as you can.

* b. What challenges might you encounter in implementing your approach?

## Citations

If you discussed the homework with other students in any way (except via
Piazza), please disclose those collaborations in the [`CITATIONS`
file](CITATIONS). If any online resources may have influenced your approach to
solving these questions (e.g., you saw a helpful guide to the ID3 algorithm),
please link to them. If you used a large language model (e.g., ChatGPT) in any
way, you must describe that use.
