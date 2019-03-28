# CONTRIBUTING

Welcome to the Glest project! Thank you for reading this document and
considering contributing.

Anyone is welcome to join our [Discord server](https://discord.gg/WaAaXS7).

The Discord rooms are for players, developers, and curiosity/adventure-seekers.

Please remember to "star" this project.

## Website Design

Documentation for designing the websites is in [WEBSITE_DESIGN.md](https://github.com/Glest/glest-source/blob/master/WEBSITE_DESIGN.md).

## Mods, tech trees, scenarios, tilesets, maps

Guidelines for submitting or letting us know about content you've
created can be found on the data repo at
[glest-data#submitting-mods-tech-trees-tilesets-maps-scenarios](https://github.com/Glest/glest-data#submitting-mods-tech-trees-tilesets-maps-scenarios)

Our goal with content contributed by artists are:

* help content creators promote their work
* make it more visible
* encourage testing by players
* have it available for testing and reviewing in a timely manner

## Issues

Glest Issues are filed on these repositories:

* [glest-source Issues](https://github.com/Glest/glest-source/issues)
* [glest-data Issues](https://github.com/Glest/glest-data/issues)
* [glest-masterserver Issues](https://github.com/Glest/glest-masterserver/issues)
* [Glest web site](https://github.com/Glest/glest.github.io)

Don't worry about focusing on every repo in the above list. Each repo is separated by
category. For example, glest-source is for source code, glest-data is for game data.
We don't expect contributors to keep track of issues in every repository. If you stay
with the project for a while, you will not have any problem finding your way around.

For new users, it's recommended to focus on only one repository. However,
if you are curious to get an overview of every issue filed from the repo list above, this
link will display a combined list of issues across every repository in the Glest
organization.

[https://github.com/issues?q=is%3Aopen+is%3Aissue+org%3AGlest](https://github.com/issues?q=is%3Aopen+is%3Aissue+org%3AGlest)

If you find an issue that interests you, please leave a note asking about it
first. If you don't see that anyone has inquired about it, you can simply
leave a note saying you are going to work on it. If people work on an issue
without saying they are working on it, the result is sometimes three people
submit a PR for the same issue.

If you find a problem for which no ticket has yet been created, please don't
hesitate to open a new ticket, and let us know if you are going to work on
that issue.

If you would like to contribute something, you will need to ask first if it's a desired
patch, to be sure it will get accepted. We don't want anyone to spend their time and
generosity working on something that would get rejected. Sometimes you may think a feature
would be a good addition or desired by the development team, but there may be a reason why
it's not. If you don't see a ticket for it, open a ticket and ask.

Please leave another note if you change your mind or if you get busy with other
things and are unable to finish it. That lets me and other people know the
ticket is available to be worked on by other people.

## Coding style

As we are working on code forked from another project, you may see some inconsistency; however, our goal is:

[The JAVA variant of K&R](https://en.wikipedia.org/wiki/Indentation_style#Variant:_Java)

Use *camelCase* for variables and function names, *CapitalCase* for classes and namespaces, and CAPS_LOCK for macros and compile-time constants.
Use *tabs* for indenting. Curly braces should be at the side and parameters and
conditions should be next to each other, not under each other (unless line length
exceeds 80-120 characters).

Sometimes a patch will be a single line in a single file; other times a single
patch will consist of changes to several files. Keep unrelated patches separate
from each other (i.e. a separate pull request for each patch).

Problems arise when multiple patches are included in a single pull request:

 * It makes the pull request more difficult to review
 * It makes reading the commit log more difficult
 * If there's a problem with one patch, it holds up other patches within that pull request
 from being merged 

See the instructions in
[BUILD.md](https://github.com/Glest/glest-source/blob/master/BUILD.md)
for important information about how to clone your forks so you can
easily contribute patches, graphics, or other content to the Glest
repositories.

## Pull Requests

(If you have no experience making pull requests and are confused about the process,
you can practice at the repository [Practice Git](https://github.com/grayghostvisuals/Practice-Git).
(Note: It is not part of this project.))

Follow the steps below if you are contributing to any of these repositories:

* [source](https://github.com/Glest/glest-source)
* [data](https://github.com/Glest/glest-data)
* [masterserver](https://github.com/Glest/glest-masterserver)
* [website](https://github.com/Glest/glest.github.io)

Below, *glest-source* is used for the example, but if you are working on another repository,
be sure to replace **glest-source** with the appropriate repo url, using the URL of
your fork.

1. [Fork the repo](https://github.com/Glest/glest-source/fork) (if you haven't already done so)
2. Clone it to your computer
3. When you're ready to work on an issue, be sure you're on the **master** branch. From there,
[create a separate branch](https://github.com/Kunena/Kunena-Forum/wiki/Create-a-new-branch-with-git-and-manage-branches)
(e.g. issue_32)
4. Make your changes. If you're unsure of some details while you're making edits, you can
discuss them on the ticket.
5. Add yourself to the [AUTHORS.md](https://github.com/Glest/glest-source/blob/master/AUTHORS.md) file

6. Commit your changes. [git-cola](https://git-cola.github.io/) is a nice GUI front-end for adding files and entering commit messages (git-cola is probably available from your OS repository).

    * If you're updating only documention (or other files that don't
    affect a build) add [skip ci] to the commit message (automatic code
    integration tests will be skipped).

7. Push the working branch (e.g. issue_32) to your remote fork and make your
[pull request](https://help.github.com/articles/creating-a-pull-request-from-a-fork/)
    * Do not merge it with the **master** branch on your fork. That would result in multiple, or
    unrelated patches being included in a single PR.
8. If any further changes need to be made, comments will be made on the pull request.

It's possible to work on two or more different patches (and therefore multiple branches) at
one time, but it's recommended that beginners only work on one patch at a time.

### Syncing ###
Periodically, especially before starting a new patch, you'll need to sync your
repo with the remote upstream. GitHub has instructions for doing this:

1. [Configuring a remote for a fork](https://help.github.com/articles/configuring-a-remote-for-a-fork/)
    * For step 3 on that page, use https://github.com/Glest/glest-source for the URL.
2. [Syncing a Fork](https://help.github.com/articles/syncing-a-fork/)
    * On that page, it shows how to merge the **master** branch (steps 4 & 5 of **Syncing a Fork**).
