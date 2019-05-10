# RecoBTag-PerformanceMeasurements-BTagAnalyzerMacros
BTagAnalyzer macros for commissioning purposes

## Content  
[Installation](#installation)  
[Repository content](#repository-content)  
[Contributing to this repository](#contributing-to-this-repository)  

## Installation

Follow the general installation of BTagAnalyzer from [here](https://github.com/cms-btv-pog/RecoBTag-PerformanceMeasurements/), then download this repository and you are ready to go:

```
cd RecoBTag/PerformanceMeasurements/test/
git clone git@github.com:cms-btv-pog/RecoBTag-PerformanceMeasurements-BTagAnalyzerMacros.git BTagAnalyzerMacros
```

## Repository content

## Contributing to this repository

First of all check the current changes you applied by running:

```
git status
```

Which will show all the changed and new files that should be committed.
First you should add those file to the commit:

```
git add file_name.blah
```

Once all the files are added they should appear as "staged" from the ```git status``` command. Now you can commit:

```
git commit -m "Some MEANINGFUL commit message explaining what you did (and why)"
```

Now the files are committed **locally**, you still need to push the changes online for everyone to see. There are two options here:

### 1. Pull Request (preferred)

**N.B.:** This is also the only way to push to the repository if you do not have writing access

You first need to _fork_ the repository from the BTV organization to your account, this is done by clicking on the top-right fork button on the [repository webpage](https://github.com/cms-btv-pog/RecoBTag-PerformanceMeasurements-BTagAnalyzerMacros). Forking is a once-in-a-lifetime operation and is needed only once.

Go now to your fork and copy the clone address (as you were to clone) and add this repository as a remote one:

```
git remote add SOME_NAME git_repository_url
```

Now push your changes to your remote repository (named ```SOME_NAME```). This command assumes you are in the master branch. You can always use a different branch name if you need and you can check which repository you are on using ```git branch```

```
git push SOME_NAME master
```

Now go to **your** repository web page and click on the "New Pull Request" button and follow the instructions. The repository managers will be notified and check your changes and approve (_merge_) your changes.


### 2. Direct commit (a tad more dangerous)

If you have write rights to the repository you can directly push to it. This is more dangerous as you might do some serious damage to the commit history and you lack the protection of the scrutiny of the Pull Rrequest, where all the changes to be merged are shown.

If you still want to push it anyhow simply do:

```
git push origin master
```
