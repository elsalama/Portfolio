# Resources for learning `git`

## Introduction

If you've never used `git` before, you will want to do a little bit of reading
and exploration before immediately jumping into the assignment. Please look at least one of these resources:

* [https://docs.github.com/en/get-started/quickstart/hello-world](https://docs.github.com/en/get-started/quickstart/hello-world)
* [https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository).
* [https://education.github.com/git-cheat-sheet-education.pdf](https://education.github.com/git-cheat-sheet-education.pdf)


## Changing your default editor

When you call `git pull` to merge the autograder's feedback into your local
repository, git will typically open its default editor, which is typically
`vim`, to make any edits to the merge message.

If you aren’t familiar with vim, it can be very annoying -- [the Stackoverflow
question](https://stackoverflow.com/questions/11828270/how-do-i-exit-vim) for
``how do I exit Vim?'' has over three millions views. I recommend changing
git’s default editor to something with which you're familiar.

To do so, you can use `git config --global core.editor <name of editor>`.

* If you’re on MacOS and want to use your default editor (often TextEdit), you can run `git config --global core.editor "open -e -W -n"`.
* If you’re on Windows and want to use Notepad as your editor, you can do: `git config core.editor notepad`.
* If you want to use Sublime Text as your default editor, see [this StackOverflow answer](https://stackoverflow.com/questions/8951275/how-can-i-make-sublime-text-the-default-editor-for-git).
* If you have a different editor you’d like to use, you should be able to search for something like ``How do I set my git default editor to `<your favorite editor>`?''.
