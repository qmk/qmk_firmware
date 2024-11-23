#!/usr/bin/env bash

cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
yarn install
[[ -e docs ]] || ln -sf ../../docs docs
DEBUG='vitepress:*,vite:*' yarn run docs:build
