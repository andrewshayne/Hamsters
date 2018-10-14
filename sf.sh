g++ -lpthread -c *.cpp
g++ -lpthread -o sfml-app *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGLU -lGL -lglut
./sfml-app
