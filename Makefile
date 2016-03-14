build: paint-map
paint-map: paint-map.c
	gcc paint-map.c -lGL -lGL -lglut -lm -o paint-map
