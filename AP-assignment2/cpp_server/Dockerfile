# Base image
FROM gcc:latest

# Update and install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    dos2unix \
    make \
    g++

# Copy project files into the container
COPY . /mytest

# Set the working directory inside the container
WORKDIR /mytest

# Ensure all text files have Unix line endings
RUN find /mytest/data -type f -exec dos2unix {} \;

# Create build directory and set it as the working directory
RUN mkdir build
WORKDIR /mytest/build

# Build the project using CMake and Make
RUN cmake .. && make

# Set the entry point to run the compiled server executable
CMD ["./my_project"]
