# HW 1: Decision Trees and Foundations

There are 18 points possible for this assignment. 2 points are for the setup,
11 points for the code, and 5 points for the free-response questions. The setup
portion is due earlier than the other pieces -- all deadlines are on Canvas.
Please carefully read this entire README before starting the assignment.

## Walkthrough

For a walkthrough of how to get started with this assignment, [please watch
this video](
https://northwestern.hosted.panopto.com/Panopto/Pages/Viewer.aspx?id=755e4f22-b215-4b08-98a8-b260005cba5a).
Two notes about this walkthrough:
- A few small things have changed with this assignment since I recorded this
walkthrough in a past quarter. When in doubt, listen to this README over the
video, or ask on Piazza if you're confused. The main change is that you can
create the conda environment in one step; see Environment Setup below.
- While I use `vim` as an editor in this walkthrough, you absolutely
**do not** need to use it. Read [git_intro.md](git_intro.md) to see how to
change git's default editor on your computer; you should use whichever editor
you find most convenient. 

## Academic integrity

Your work must be your own. You may not work with others. Do not submit other
people's work as your own, and do not allow others to submit your work as
theirs. 

You may *talk* with other students about the concepts covered by the homework,
but you may not share code or answers with others in any way.  If you do meet
with other students to discuss the assignments, **you may not work from notes
taken during collaborative sessions**. If you write anything while working
collaboratively, you must erase/destroy/archive that writing or any recording
thereof before coding or writing the solution that you turn in. You don't
literally have to burn papers or delete files, but you must pretend that those
papers or files do not exist for the purposes of writing your solution.
Collaborative sessions are for you to learn the material in whatever way is
best for you; coding or writing the solutions is an individual assessment of
your ability to convey your mastery of that knowledge.

If you discussed the homework with other students in any way (except via
Piazza), please disclose those collaborations in the [`CITATIONS`
file](CITATIONS). If any online resources may have influenced your approach to
solving these questions (e.g., you saw a helpful guide to the ID3 algorithm),
please link to them. If you used a large language model (e.g., ChatGPT) in any
way, please describe that use.

If you need help debugging your code, make a *private* post on Piazza or come
to office hours. You may not show your code (including pseudocode) to other
students under any circumstances.

We will use a combination of automated and manual methods for comparing your
code and free-response answers to that of other students. If we find
sufficiently suspicious similarities between your answers and those of another
student, you will both be reported for a suspected violation. If you're unsure
of the academic integrity policies, ask for help; we can help you avoid
breaking the rules, but we can't un-report a suspected violation.

You are required to completely understand any homework solution that you
submit, and, in case of any doubt, you must be prepared to orally explain your
solution. If you have submitted a solution that you cannot verbally explain,
then you have violated this policy.

By pushing your code to GitHub, you agree to these rules, and understand that
there may be severe consequences for violating them.

## Important instructions

Your work will be graded and aggregated using an autograder that will download
the code and free response questions from each student's repository. If you
don't follow the instructions, you run the risk of getting *zero points*. The
`test_setup` test cases gives you points for following these instructions 
and will make it possible to grade your work easily.

The essential instructions:
- Your code and written answers must be *pushed* to GitHub for us to grade them!
  We will only grade the latest version of your code that was pushed to GitHub
  before the deadline (accounting for late days; see below).
- Your NetID must be in the `netid` file; replace `NETID_GOES_HERE` with your
  netid.
- Your answer to each free response question should be upload to Canvas in *its
  own PDF* with the filename `qYYY.pdf`, where `YYY` is the question number. So
  your answer to free response question 2 should be in a PDF file with the
  filename `q2.pdf`.
- Do not include your name or Net ID in the content of your free response PDFs
  -- we will grade these anonymously. 

## Late Work

In general, late work is not accepted. The autograder will only download work
from your repository that was pushed to GitHub before the deadline. However:

- Each student gets four late days to use across the entire quarter. If you
  want to use late days, use the [late day assignment
  ](https://canvas.northwestern.edu/courses/225627/assignments/1526025) on
  Canvas.
- You can use at most two late days per assignment.
- If you have a personal emergency, please ask for help. You do not have to
  share any personal information with me, but I will ask you to get in touch
  with the dean who oversees your student services to coordinate
  accommodations.

## Clone this repository

To get started with the assignment, you need to clone this repository to your
local machine. If you haven't used `git` before, please look at the resources
in the [`git_intro.md` file](git_intro.md) in this repository.

Once you have `git` installed on your computer, you'll need the link to this
repository (find it on the github.com under "Clone or Download"), which might
look something like `git@github.com:cs349/hw1-decision-tree-yourname.git`.
Then run:

``git clone YOUR-LINK``

As soon as you've downloaded it, go ahead and add your NetID to the `netid` file,
run `git add netid`, then `git commit -m "added netid"`, and `git push origin main`.
If you've successfully run those commands, you're almost done with the `test_setup`
test case.

## Environment setup

This course uses **Python 3**. Python 2 will not work for these assignments and
all assignments will be graded with Python 3 on our end.

If you used Python before, you've probably installed packages (e.g. `numpy`). To
avoid having to uninstall old packages in order to reinstall the correct ones,
you are strongly encouraged to create a "virtual environment" using 
[**miniconda**](https://docs.conda.io/en/latest/miniconda.html). Virtual
environments are a simple way to isolate all the dependencies for a particular
project, making it easy to work on multiple projects at once without them
interfering with each other (e.g. conflicting versions of libraries between
projects). To make sure your environment matches the testing environment that
we use for grading exactly, it's best to make a new environment for each
assignment in this course.

Install the latest version of [miniconda for your operating
system](https://docs.conda.io/en/latest/miniconda.html#latest-miniconda-installer-links).
After installing you should be able to run `conda` from your terminal. If you can't,
you may need to run `source ~/.bash_profile` or restart your terminal.
If you for some reason cannot use miniconda, try [python's venv
module](https://docs.python.org/3/library/venv.html).
Once you have `conda` set up, you can create a virtual environment by running:

``conda env create -f environment.yml``

Once it's created, you can *activate* it with:

``conda activate cs349``

Here, `cs349` is the name for the environment. If you name it something
else and forget what you named it, you can call `conda env list` to list
all your conda environments. After activating it, you'll likely see that your
terminal prompt has changed to include `(cs349)`.

You're all set up to do the homework! You'll use this environment for each
homework in this class, and you'll have to re-activate the environment when you
open a new terminal. If you want to deactivate your environment in a given
terminal, you can simply call `conda deactivate`.

Note: in the walkthrough video linked above, the README is slightly different,
and it will tell you to run `conda create -n cs349 python=3.9` and then run a
separate command to install the requirements. The new way is faster, but if you
choose the old way you should at least switch to python 3.13.  If you used
`venv` instead of conda, you will need to run `pip install -r requirements.txt`
after creating and activating your environment.

## What to do for this assignment

The detailed instructions for the work you need to do are in [`problems.md`](problems.md).

For the coding portion of the assignment, you will:
- Solve some numpy practice problems
- Implement a train test split and cross validation
- Implement some classification and fairness metrics
- Implement a simple model that just predicts the mode (most common class)
- Compute information gain
- Implement a decision tree with the ID3 algorithm

You will also write up answers to a few free response questions.

In every function where you need to write code, there is a `raise
NotImplementeError` which you will replace with your implementation. The test
cases will guide you through the work you need to do and tell you how many
points you've earned. The test cases can be run from the root directory of this
repository with:

``python -m pytest -s``

To run a single test, you can specify it with `-k`, e.g., `python -m pytest -s
-k test_setup_netid`.  To run a group of tests, you can use `-k` with a prefix, e.g.,
`python -m pytest -s -k test_decision` will run all tests that begin with
`test_decision`.  The `-s` means that any print statements you include will in
fact be printed; the default behavior (`python -m pytest`) will suppress
everything but the pytest output.

We will use these test cases to grade your work! Even if you change the test
cases such that you pass the tests on your computer, we're still going to use
the original test cases to grade your assignment.

## Questions? Problems? Issues?

Ask a question on Piazza, and we'll help you there.

## Helpful Material
- [Let’s Write a Decision Tree Classifier from Scratch - Machine Learning Recipes #8](https://www.youtube.com/watch?v=LDRbO9a6XPU)

- [Decision Tree Lecture Series](https://www.youtube.com/playlist?list=PLBv09BD7ez_4temBw7vLA19p3tdQH6FYO)
  1. [How it works](https://www.youtube.com/watch?v=eKD5gxPPeY0&list=PLBv09BD7ez_4temBw7vLA19p3tdQH6FYO&index=1)
  2. [ID3 Algorithm](https://www.youtube.com/watch?v=_XhOdSLlE5c&list=PLBv09BD7ez_4temBw7vLA19p3tdQH6FYO&index=2)
  3. [Which attribute to split on](https://www.youtube.com/watch?v=AmCV4g7_-QM&list=PLBv09BD7ez_4temBw7vLA19p3tdQH6FYO&index=3)
  4. [Information Gain and Entropy](https://www.youtube.com/watch?v=nodQ2s0CUbI&list=PLBv09BD7ez_4temBw7vLA19p3tdQH6FYO&index=4)

- [ID3-Algorithm: Explanation](https://www.youtube.com/watch?v=UdTKxGQvYdc)

### Entropy
- [What is entropy in Data Science (very nice explanaton)](https://www.youtube.com/watch?v=IPkRVpXtbdY)
- [Entropy as concept in Physics/Chemistry (only if you're interested)](https://www.youtube.com/watch?v=YM-uykVfq_E)

### Recursion
- [Python: Recursion Explained](https://www.youtube.com/watch?v=wMNrSM5RFMc)
- [Recursion example](https://www.youtube.com/watch?v=8lhxIOAfDss)
