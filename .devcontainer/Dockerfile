FROM mcr.microsoft.com/devcontainers/cpp:0-debian-11

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get autoremove -y && \
    apt-get clean -y && \
    rm -rf /var/lib/apt/lists/*; \
    curl -L -O https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1-linux-x86_64.tar.gz && \
    tar -xf cmake-3.20.1-linux-x86_64.tar.gz && \
    rm cmake-3.20.1-linux-x86_64.tar.gz;

ENV PATH "$PATH:/:/cmake-3.20.1-linux-x86_64/bin"
