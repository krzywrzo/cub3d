#!/bin/bash

# Change this if your maps are in a different folder
MAP_DIR="maps"
EXEC="./cub3D"

# Colors for terminal output
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}       CUB3D PARSER TEST SCRIPT         ${NC}"
echo -e "${GREEN}========================================${NC}"

# Check if the executable exists
if [ ! -f "$EXEC" ]; then
    echo "Error: $EXEC not found. Please run 'make' first."
    exit 1
fi

# Check if the map directory exists
if [ ! -d "$MAP_DIR" ]; then
    echo "Error: Directory '$MAP_DIR' not found."
    exit 1
fi

# Loop through every .cub file in the directory
for map in "$MAP_DIR"/*.cub; do
    # Check if the glob didn't match anything
    if [ ! -e "$map" ]; then
        echo "No .cub files found in $MAP_DIR."
        break
    fi

    echo -e "${CYAN}>>> Testing: ${YELLOW}$map${NC}"
    
    # Run the program
    $EXEC "$map"
    
    # Print a divider line
    echo "----------------------------------------"
done

echo -e "${GREEN}Testing Complete!${NC}"