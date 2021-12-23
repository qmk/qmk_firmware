#!/bin/sh
fswatch -0 ../flow.c ./test.c | xargs -0 -I {} ./test.sh "{}"
