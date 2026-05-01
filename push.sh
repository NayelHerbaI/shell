#!/bin/bash

# This script must be launched from the parent folder containing:
# - ft_shell
# - my_shell
#
# It copies modifications from ft_shell to my_shell,
# asks for confirmation,
# then optionally commits and pushes:
# - ft_shell -> nayel
# - my_shell -> main

FT_DIR="ft_shell"
MY_DIR="my_shell"

FT_BRANCH="nayel"
MY_BRANCH="main"

echo "================================"
echo " Sync ft_shell -> my_shell"
echo "================================"
echo

# Security checks
if [ ! -d "$FT_DIR" ]; then
	echo "Error: ft_shell directory not found."
	echo "Run this script from the parent folder containing ft_shell and my_shell."
	exit 1
fi

if [ ! -d "$MY_DIR" ]; then
	echo "Error: my_shell directory not found."
	echo "Run this script from the parent folder containing ft_shell and my_shell."
	exit 1
fi

if [ ! -d "$FT_DIR/.git" ]; then
	echo "Error: ft_shell is not a Git repository."
	exit 1
fi

if [ ! -d "$MY_DIR/.git" ]; then
	echo "Error: my_shell is not a Git repository."
	exit 1
fi

echo "Source:      $FT_DIR/"
echo "Destination: $MY_DIR/"
echo

echo "The following changes would be copied to my_shell:"
echo

rsync -avun --delete \
	--exclude=".git" \
	--exclude="sync_and_push.sh" \
	"$FT_DIR/" "$MY_DIR/"

echo
read -p "Do you confirm copying ft_shell into my_shell? (y/n): " CONFIRM_COPY

if [ "$CONFIRM_COPY" != "y" ]; then
	echo "Copy cancelled."
	exit 0
fi

echo
echo "Copying files..."
echo

rsync -avu --delete \
	--exclude=".git" \
	--exclude="sync_and_push.sh" \
	"$FT_DIR/" "$MY_DIR/"

echo
echo "Copy done."
echo

read -p "Do you want to push all modifications? (y/n): " CONFIRM_PUSH

if [ "$CONFIRM_PUSH" != "y" ]; then
	echo "Push cancelled. Files were copied, but nothing was committed or pushed."
	exit 0
fi

echo
read -p "Commit message: " MSG

if [ -z "$MSG" ]; then
	echo "Error: commit message cannot be empty."
	exit 1
fi

echo
echo "================================"
echo " Pushing ft_shell on branch $FT_BRANCH"
echo "================================"
echo

cd "$FT_DIR" || exit 1

git add .

if git diff --cached --quiet; then
	echo "Nothing to commit in ft_shell."
else
	git commit -m "$MSG"
fi

git push origin "$FT_BRANCH"

cd ..

echo
echo "================================"
echo " Pushing my_shell on branch $MY_BRANCH"
echo "================================"
echo

cd "$MY_DIR" || exit 1

git add .

if git diff --cached --quiet; then
	echo "Nothing to commit in my_shell."
else
	git commit -m "$MSG"
fi

git push origin "$MY_BRANCH"

cd ..

echo
echo "Done."