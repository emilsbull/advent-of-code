#!/bin/bash

# Run this scipt to install the Buildifier which is required by the VS Code Bazel extension.

# Download buildifier binary.
wget https://github.com/bazelbuild/buildtools/releases/download/v6.4.0/buildifier-linux-amd64

# Set permissions to executable.
chmod +x buildifier-linux-amd64

# Rename to `buildifier` and move to `$HOME/.local/bin` so it can be executed by running `buildifier` on the command line.
mkdir -p $HOME/.local/bin
mv buildifier-linux-amd64 $HOME/.local/bin/buildifier

# Check if `$HOME/.local/bin` is in the PATH variable.
if [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
    echo "The directory \$HOME/.local/bin where buildifier is installed is not in your PATH."
    echo "You can add it by running the following command:"
    echo 'export PATH=$HOME/.local/bin:$PATH'
    echo "To make this change permanent, add the above line to your ~/.bashrc or ~/.profile file."
fi
