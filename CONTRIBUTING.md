# CONTRIBUTING

Welcome to the ZG project! Thank you for reading this document and
considering contributing.

Anyone is welcome to join our [Discord server](https://discord.gg/WaAaXS7).

The Discord rooms are for players, developers, and curiosity/adventure-seekers.

## Website Design

Documentation for designing the websites is in [WEBSITE_DESIGN.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/WEBSITE_DESIGN.md).

## Mods, tech trees, scenarios, tilesets, maps

Guidelines for submitting or letting us know about content you've
created can be found on the data repo at
[zetaglest-data#submitting-mods-tech-trees-tilesets-maps-scenarios](https://github.com/ZetaGlest/zetaglest-data#submitting-mods-tech-trees-tilesets-maps-scenarios)

Our goal with content contributed by artists are:

* help content creators promote their work
* make it more visible
* encourage testing by players
* have it available for testing and reviewing in a timely manner

## Issues

ZetaGlest Issues are filed on these repositories:

* [zetaglest-source Issues](https://github.com/ZetaGlest/zetaglest-source/issues)
* [zetaglest-data Issues](https://github.com/ZetaGlest/zetaglest-data/issues)
* [zetaglest-masterserver Issues](https://github.com/ZetaGlest/zetaglest-masterserver/issues)

This link will display a combined list of issues across every
repository in the ZetaGlest organization (hint: a good link to
bookmark).

[https://github.com/issues?q=is%3Aopen+is%3Aissue+org%3AZetaGlest](https://github.com/issues?q=is%3Aopen+is%3Aissue+org%3AZetaGlest)

If you find an issue that interests you, please leave a note asking about it
first. If you don't see that anyone has inquired about it, you can simply
leave a note saying you are going to work on it. If people work on an issue
without saying they are working on it, the result is sometimes three people
submit a PR for the same issue.

If you find a problem for which no ticket has yet been created, please don't
hesitate to open a new ticket, and let us know if you are going to work on
that issue.

If you would like to contribute something, it is advised to inquire
first, to be sure it's a patch that would get accepted. We don't want
anyone to spend their time and generosity working on something that we
would be unable to accept.

Please leave another note if you change your mind or if you get busy with other
things and are unable to finish it. That lets me and other people know the
ticket is available to be worked on by other people.

## Coding style
Please match the existing style

Sometimes a patch will be a single line in a single file; other times a single
patch will consist of changes to several files. Keep unrelated patches separate
from each other (i.e. a separate PR for each patch).

See the instructions in
[BUILD.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/BUILD.md)
for important information about how to clone your forks so you can
easily contribute patches, graphics, or other content to the ZetaGlest
repositories.

## Pull Requests
1. [Fork the repo](https://github.com/ZetaGlest/zetaglest-source/fork) (if you haven't already done so)
2. Clone it to your computer
3. When you're ready to work on an issue, be sure you're on the **develop** branch. From there,
[create a separate branch](https://github.com/Kunena/Kunena-Forum/wiki/Create-a-new-branch-with-git-and-manage-branches)
(e.g. issue_32)
4. Make your changes. If you're unsure of some details while you're making edits, you can
discuss them on the ticket.
5. Add yourself to the [AUTHORS.md](https://github.com/ZetaGlest/zetaglest-source/blob/develop/AUTHORS.md) file

6. Commit your changes. [git-cola](https://git-cola.github.io/) is a nice GUI front-end for adding files and entering commit messages (git-cola is probably available from your OS repository).

    * If you're updating only documention (or other files that don't
    affect a build) add [skip ci] to the commit message (automatic code
    integration tests will be skipped).

7. Push the working branch (e.g. issue_32) to your remote fork and make your
[pull request](https://help.github.com/articles/creating-a-pull-request-from-a-fork/)
    * Do not merge it with the **develop** branch on your fork. That would result in multiple, or
    unrelated patches being included in a single PR.
8. If any further changes need to be made, comments will be made on the pull request.

It's possible to work on two or more different patches (and therefore multiple branches) at
one time, but it's recommended that beginners only work on one patch at a time.

### Syncing ###
Periodically, especially before starting a new patch, you'll need the sync your
repo with the remote upstream. GitHub has instructions for doing this:

1. [Configuring a remote for a fork](https://help.github.com/articles/configuring-a-remote-for-a-fork/)
    * For step 3 on that page, use https://github.com/ZetaGlest/zetaglest-source for the URL.
2. [Syncing a Fork](https://help.github.com/articles/syncing-a-fork/)
    * On that page, it shows how to merge the **develop** branch (steps 4 & 5 of **Syncing a Fork**).

Follow these steps if you are contributing to the
[data](https://github.com/ZetaGlest/zetaglest-data) or
[masterserver](https://github.com/MegaGlest/megaglest-masterserver)
repository.
