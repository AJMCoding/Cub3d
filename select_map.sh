#!/bin/bash

echo "Choose a map:"

map_files=()

for file in maps/*.cub; do
    map_files+=("$file")
done

select map_file in "${map_files[@]}"; do
    if [[ -n $map_file ]]; then
        break
    fi
done

./cub3D $map_file
