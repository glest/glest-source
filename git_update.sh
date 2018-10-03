#!/bin/bash
#
# git_update.sh: update the ZetaGlest source and data repos. Use this
# script if you've cloned from the master repositories, not if you're
# a fork.

export LANG=C

master_repo="https://github.com/ZetaGlest/zetaglest-source"
data_repo="https://github.com/ZetaGlest/zetaglest-data"
data_dir="../zetaglest-data"
remote=$(git remote get-url origin)

# Exit if there is no remote configured
if [ -z "$remote" ]; then
	exit 1;
fi

# Exit if it's a fork instead of a clone from the master repo
if [ "$remote" != "$master_repo" ]; then
	exit 2;
fi

cd "$(dirname $(readlink -f $0))" &&

echo $PWD

git pull &&

echo $PWD

# If the data path doesn't exist, clone the repo
if [ ! -d "$data_dir" ]; then
	git clone "$data_repo" "$data_dir"
fi

cd ../zetaglest-data &&
git pull &&

exit 0
