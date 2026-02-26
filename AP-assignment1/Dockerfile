# Base image
FROM gcc:latest

# Update and install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    dos2unix

# Copy project files into the container
COPY . /mytest

# Set the working directory
WORKDIR /mytest

# Ensure all text files have Unix line endings
RUN find /mytest/data -type f -exec dos2unix {} \;

# Create build directory and set it as the working directory
RUN mkdir build
WORKDIR /mytest/build

# Build the project
RUN cmake .. && make

# Run tests by default
CMD ["./runTests"]
