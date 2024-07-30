FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    curl \
    libcurl4-openssl-dev \
    libexiv2-dev \
    cmake \
    git


RUN mkdir -p /app/spyder /app/scorpion


COPY ./spyder /app/spyder
COPY ./scorpion /app/scorpion
COPY ./utils.cpp /app/utils.cpp
COPY ./utils.hpp /app/utils.hpp

WORKDIR /app/spyder

RUN make clean
RUN make

WORKDIR /app/scorpion

RUN make clean
RUN make

CMD ["/bin/bash"]
