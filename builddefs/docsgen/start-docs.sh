#!/usr/bin/env bash

cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
yarn install
DEBUG='vitepress:*,vite:*' yarn run docs:dev
