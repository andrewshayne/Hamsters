g++ -lpthread -c *.cpp
g++ -lpthread -o sfml-app *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGLU -lGL -lglut -lboost_system -lboost_filesystem -lboost_serialization
./sfml-app
