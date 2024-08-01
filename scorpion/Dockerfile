FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    g++ \
    libexiv2-dev \
    build-essential \
    make

WORKDIR /app

COPY . .

RUN make

ENTRYPOINT ["/bin/bash"]
