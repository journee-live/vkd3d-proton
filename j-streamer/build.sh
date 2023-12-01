#!/usr/bin/env bash

set -e


winegcc -shared -o ProtonStreamer.dll main.c main.spec
