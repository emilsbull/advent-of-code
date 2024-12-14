#!/bin/bash

# Download bazelisk binary.
wget https://github.com/bazelbuild/bazelisk/releases/download/v1.8.1/bazelisk-linux-amd64

# Set permissions to executable.
chmod +x bazelisk-linux-amd64

# Rename to `bazel` and move to `$HOME/.local/bin` so it can be executed by running `bazel` on the command line.
mkdir -p $HOME/.local/bin
mv bazelisk-linux-amd64 $HOME/.local/bin/bazel

# Check if `$HOME/.local/bin` is in the PATH variable.
if [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
    echo "The directory \$HOME/.local/bin where bazel is installed is not in your PATH."
    echo "You can add it by running the following command:"
    echo 'export PATH=$HOME/.local/bin:$PATH'
    echo "To make this change permanent, add the above line to your ~/.bashrc or ~/.profile file."
fi
