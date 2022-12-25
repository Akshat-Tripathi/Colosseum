#!/bin/bash

./colosseum $1 temp.ll 1>/dev/null
lli temp.ll