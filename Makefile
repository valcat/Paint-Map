build: paint-map
paint-map: paint-map.c
	gcc paint-map.c -lGL -lGL -lglut -lm -o paint-map
paint-map-darvin: paint-map.c
	gcc paint-map.c -framework carbon -framework OpenGL -framework GLUT -Wno-deprecated -o paint-map 
