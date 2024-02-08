#!/bin/bash

# Választható térképek listájának megjelenítése
echo "Választható térképek:"
map_files=("maps/1.cub" "maps/space.cub")
select map_file in "${map_files[@]}"; do
    if [[ -n $map_file ]]; then
        break
    fi
done

# Választott térkép futtatása
./cub3D $map_file
