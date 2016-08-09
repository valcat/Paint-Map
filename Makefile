build: paint-map

paint-map: paint-map.c
	gcc paint-map.c linked_list.c circle.c rectangle.c -lGL -lGLU -lglut -lm -o paint-map

paint-map-darvin: paint-map.c
	gcc paint-map.c linked_list.c -framework carbon -framework OpenGL -framework GLUT -Wno-deprecated -o paint-map 
