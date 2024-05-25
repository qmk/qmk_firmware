#!/usr/bin/env bash

cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
yarn install
ln -sf ../../docs docs
DEBUG='vitepress:*,vite:*' yarn run docs:build
