# AP-assignment

Part 2 of Netflix project

Made by:

Itay hoban, ID 211547153 Matan, ID 211458484 Oren, ID 209188689


Link to GitHub repository:
https://github.com/matan211/AP-assignment2

1. Docker Build:
   docker-compose build

2. Create network:
   docker network create my_network

3. Run server side:
   docker stop cpp-server
   docker rm cpp-server
   docker run -d --name cpp-server --network my_network ap-assignment2-cpp-server
   (After execution, server prints its ID container and terminal proceeds to next command. The server is running!)

4. Run client side:
   docker stop python-client
   docker rm python-client
   docker run -it --name python-client --network my_network ap-assignment2-python-client

Addressing the points:

1. Changing functions' names did not require touching the code, because we used command design pattern.
 
2. Adding new functions did not require touching the code, because we used command design pattern.

3. Changing functions' output required touching the code, we fix it so the next time we will not need to touch the code by putting the output in a variable.

4. Changing from console to sockets required touching the code, we fix it by changing the output from int to string so the next time we will not need to touch the code.
