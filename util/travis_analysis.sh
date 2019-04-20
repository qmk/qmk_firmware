#!/bin/bash

# Lint markdown - output is only warnings till code base is up to scratch
echo "Linting markdown..."
markdownlint **/*.md --ignore='tmk_core/*' | true

# Maybe some C static analysis too???
