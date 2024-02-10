# 2023-2024-VRC_OverUnder-PCFresh
**The definitive Repository for the 2023-2024 VRC Over Under for the Pine Crest Upper School Freshman Robotics Team (#20144B)**<br>
There are 2 teams for the Pine Crest VEX Robotics competition. This is the Freshman Team for the 2023-2024 Season. The Code here will contain, but is not limited to, all driving and autonomous code.

## Set Up

### Git Installation
Our project is hosted on a platform called GitHub, where different users can edit and change the same code. The software that is widely used to connect the online repository to your computer is a software called _git_. We will need to install git to allow for easy access and changes to the latest, newest code on our repo.

Download & Install Git: [https://git-scm.com/book/en/v2/Getting-Started-Installing-Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)

**Recommended** Use Git with the built-in VS Code source control manager:

open Git Bash and type these following commands. These will let git know the name and the email of the person editing the code, so everyone can tie it back to you. Replace ```<text>``` (including the "<" ">") with your personal information.

```git config --global user.name "<first_name last_name>"```

```git config --global user.email "<your email>```

### Installation
**All instructions must be followed IN ORDER, as each depends on the last**<br>
Follow these instructions to download PROS (and VS Code, if necessary): [https://pros.cs.purdue.edu/v5/getting-started/](https://pros.cs.purdue.edu/v5/getting-started/)

Inside VS Code, download the "C/C++" extension.

We use a library called LemLib to handle all PID and robot movement control to have an easy api as well as robust tools at our disposal.

Install LemLib here (current release version: v0.4.7): [https://github.com/LemLib/LemLib/releases/](https://github.com/LemLib/LemLib/releases/)]

I would recommend connecting your GitHub account to the built-in VS Code source control manager, to make pushing and pulling faster:[ https://code.visualstudio.com/docs/sourcecontrol/github](https://code.visualstudio.com/docs/sourcecontrol/github)

## Contributing

**ALWAYS PULL BEFORE YOU START EDITING**

These are the docs for our library: [https://lemlib.github.io/LemLib/](https://lemlib.github.io/LemLib/) 


Remember to comment on anything that isn't immediately readable and understandable


Create a fork and make a pull request when it's ready to be merged into main.

1. Create a fork via GitHub
2. Make your modifications to that fork
3. Document your changes using detailed commits
4. Make a pull request back into the main repository
5. Send a text on the group chat letting everyone know what you did
