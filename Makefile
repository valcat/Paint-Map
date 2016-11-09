build: paint-map

paint-map: paint-map.c
	gcc paint-map.c linked_list.c circle.c rectangle.c line.c triangle.c graph.c find_path.c -lGL -lGLU -lglut -lm -o paint-map

paint-map-darvin: paint-map.c
	gcc paint-map.c linked_list.c circle.c rectangle.c line.c triangle.c  graph.c -framework carbon -framework OpenGL -framework GLUT -Wno-deprecated -o paint-map 
