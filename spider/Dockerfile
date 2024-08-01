FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    g++ \
    libcurl4-openssl-dev \
    build-essential \
    curl \
    make

WORKDIR /app

COPY . .

RUN make

CMD ["/bin/bash"]
