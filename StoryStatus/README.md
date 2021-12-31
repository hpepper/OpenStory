# Story status

## Introduction

### Overview

#### Process

1. Read series.xml
2. Get list of all seasons
3. loop read season.xml files
4. Get list of episode files in season
5. loop through each episode, go through sections
6. 

### Methods for updating the plotplan

Methods:

* Read the old plan, and read data from it and apply it to the new plan struct
* Generate the new plan and merge it into the old plan

Challenges:

* What if sequence length has changed?
* What if the Scene number has changed?
* What if there is already text in new elements? Like the 'Purpose' or 'Seed'

## Descriptions

The whole story consists of:

* One series.xml file
  * multiple season.xml files
    * multiple episode.xml files